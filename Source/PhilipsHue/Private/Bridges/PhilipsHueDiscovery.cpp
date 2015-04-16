// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"


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
	KnownBridges.Empty();
}


void UPhilipsHueDiscovery::ProcessHttpResponse(FHttpResponsePtr HttpResponse, bool Succeeded)
{
	if (Succeeded)
	{
		FString ResponseStr = FString(TEXT("{\"bridges\":")) + HttpResponse->GetContentAsString() + TEXT("}");
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

		TSharedPtr<FJsonObject> JsonObject;
		{
			if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
			{
				return;
			}
		}

		TArray<TSharedPtr<FJsonValue>> Bridges = JsonObject->GetArrayField(TEXT("bridges"));
		{
			TArray<UPhilipsHueBridge*> DiscoveredBridges;

			for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(Bridges); It; ++It)
			{
				TSharedPtr<FJsonObject> DiscoveredBridge = (*It)->AsObject();

				if (!DiscoveredBridge.IsValid() ||
					!DiscoveredBridge->HasField(TEXT("id")) ||
					!DiscoveredBridge->HasField(TEXT("internalipaddress")))
				{
					continue;
				}

				FString DiscoveredId = DiscoveredBridge->GetStringField(TEXT("id"));
				FString DiscoveredAddr = DiscoveredBridge->GetStringField(TEXT("internalipaddress"));

				for (UPhilipsHueBridge* KnownBridge : KnownBridges)
				{
					if (DiscoveredId == KnownBridge->Id)
					{
						DiscoveredBridges.Add(KnownBridge);
					}
					else
					{
						//DiscoveredBridges.Add()
					}
				}
			}

			KnownBridges = DiscoveredBridges;
		}
	}

	State = EPhilipsHueDiscoveryState::Idle;
}


/* UPhilipsHueLights event handlers
 *****************************************************************************/

void UPhilipsHueDiscovery::HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	FFunctionGraphTask::CreateAndDispatchWhenReady([=]() {
		ProcessHttpResponse(HttpResponse, bSucceeded);
	}, TStatId(), nullptr, ENamedThreads::GameThread);
}
