// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"


/* UPhilipsHueLights structors
 *****************************************************************************/

UPhilipsHueBridge::UPhilipsHueBridge( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{ }


/* UPhilipsHueLights event handlers
 *****************************************************************************/

void UPhilipsHueBridge::HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!bSucceeded)
	{
		return;
	}

	FString ResponseStr = HttpResponse->GetContentAsString();
}


void UPhilipsHueBridge::HandleTimer(float DeltaTime)
{
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UPhilipsHueBridge::HandleHttpRequestComplete);
		HttpRequest->SetURL(FString(TEXT("http://")) + InternalIpAddress + TEXT("/api/") + UserName + TEXT("/lights"));
		HttpRequest->SetVerb(TEXT("GET"));
		HttpRequest->ProcessRequest();
	}
}
