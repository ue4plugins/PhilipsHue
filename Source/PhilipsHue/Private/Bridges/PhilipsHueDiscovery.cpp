// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"
#include "PhilipsHueDiscoveryMessages.h"


/* UPhilipsHueDiscovery structors
 *****************************************************************************/

UPhilipsHueDiscovery::UPhilipsHueDiscovery( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{ }


/* UPhilipsHueDiscovery interface
 *****************************************************************************/

void UPhilipsHueDiscovery::DiscoverBridges()
{
	if (State != EPhilipsHueDiscoveryState::Idle)
	{
		return;
	}

	State = EPhilipsHueDiscoveryState::MeetHue;

	auto HttpRequest = FHttpModule::Get().CreateRequest();
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UPhilipsHueDiscovery::HandleHttpRequestComplete);
		HttpRequest->SetURL(TEXT("https://www.meethue.com/api/nupnp"));
		HttpRequest->SetVerb(TEXT("GET"));
		HttpRequest->ProcessRequest();
	}
}

void UPhilipsHueDiscovery::ForgetBridges()
{
	BridgesById.Empty();
}


void UPhilipsHueDiscovery::ProcessHttpResponse(FHttpResponsePtr HttpResponse, bool Succeeded)
{
	State = EPhilipsHueDiscoveryState::Idle;

	if (!Succeeded)
	{
		OnDiscoveryCompleted.Broadcast(EPhilipsHueDiscoveryResult::NoResponse);
		UE_LOG(LogPhilipsHue, Verbose, TEXT("Failed to get bridge discovery response."));

		return;
	}

	// deserialize response
	FString ResponseStr = FString(TEXT("{\"BridgeInfos\":")) + HttpResponse->GetContentAsString() + TEXT("}");
	FBufferReader ResponseReader((void*)*ResponseStr, ResponseStr.Len() * sizeof(TCHAR), false);
	FJsonStructDeserializerBackend Backend(ResponseReader);
	FPhilipsHueDiscoveryResponse Response;

	if (!FStructDeserializer::Deserialize(Response, Backend))
	{
		OnDiscoveryCompleted.Broadcast(EPhilipsHueDiscoveryResult::SerializationFailure);
		UE_LOG(LogPhilipsHue, Verbose, TEXT("Failed to deserialize bridge discovery response."));

		return;
	}

	// add or update discovered bridge
	for (const auto& BridgeInfo : Response.BridgeInfos)
	{
		if (BridgeInfo.Id.IsEmpty())
		{
			continue;;
		}

		UPhilipsHueBridge*& Bridge = BridgesById.FindOrAdd(BridgeInfo.Id);

		if (Bridge == nullptr)
		{
			Bridge = NewObject<UPhilipsHueBridge>(this, NAME_None);
		}

		Bridge->Id = BridgeInfo.Id;
		Bridge->Configuration.IpAddress = BridgeInfo.InternalIpAddress;
	}

	OnDiscoveryCompleted.Broadcast(EPhilipsHueDiscoveryResult::Success);
}


/* UPhilipsHueLights event handlers
 *****************************************************************************/

void UPhilipsHueDiscovery::HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	// process response on game thread
	FFunctionGraphTask::CreateAndDispatchWhenReady([=]() {
		ProcessHttpResponse(HttpResponse, bSucceeded);
	}, TStatId(), nullptr, ENamedThreads::GameThread);
}
