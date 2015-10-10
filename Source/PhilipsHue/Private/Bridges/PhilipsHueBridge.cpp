// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"
#include "Ticker.h"


/* UPhilipsHueBridge structors
 *****************************************************************************/

UPhilipsHueBridge::UPhilipsHueBridge()
	: Connected(false)
{ }


UPhilipsHueBridge::~UPhilipsHueBridge()
{
	Disconnect();
}


/* UPhilipsHueBridge interface
 *****************************************************************************/

void UPhilipsHueBridge::Connect(const FString& User)
{
	ConnectedUser = User;
	TickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UPhilipsHueBridge::HandleTicker), 10.0f);
}


void UPhilipsHueBridge::Disconnect()
{
	ConnectedUser.Empty();
	OnDisconnected.Broadcast(Id);
	FTicker::GetCoreTicker().RemoveTicker(TickerHandle);
}


/* UPhilipsHueBridge event handlers
 *****************************************************************************/

void UPhilipsHueBridge::HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!bSucceeded)
	{
		Disconnect();

		return;
	}

	if (!Connected)
	{
		Connected = true;
		OnConnected.Broadcast(Id);
	}

//	FString ResponseStr = HttpResponse->GetContentAsString();
}


bool UPhilipsHueBridge::HandleTicker(float DeltaTime)
{
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UPhilipsHueBridge::HandleHttpRequestComplete);
		HttpRequest->SetURL(FString(TEXT("http://")) + Configuration.IpAddress + TEXT("/api/") + ConnectedUser + TEXT("/lights"));
		HttpRequest->SetVerb(TEXT("GET"));
		HttpRequest->ProcessRequest();
	}

	return !ConnectedUser.IsEmpty();
}
