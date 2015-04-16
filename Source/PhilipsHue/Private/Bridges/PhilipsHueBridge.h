// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueBridge.generated.h"


/**
 * A Philips Hue bridge.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class UPhilipsHueBridge
	: public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** Unique identifier. */
	UPROPERTY()
	FString Id;

	/** Bridge's internal IP address. */
	UPROPERTY()
	FString InternalIpAddress;

	/** User name for accessing the bridge. */
	UPROPERTY()
	FString UserName;

private:

	/** Handles the completion of HTTP requests. */
	void HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	/** Handles the light discovery timer. */
	void HandleTimer(float DeltaTime);
};
