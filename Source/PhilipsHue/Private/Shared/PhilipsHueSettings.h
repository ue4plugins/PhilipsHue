// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueSettings.generated.h"


UCLASS(config=Engine)
class UPhilipsHueSettings
	: public UObject
{
	GENERATED_UCLASS_BODY()

	/** Number of seconds between querying for new lines. */
	UPROPERTY(config, EditAnywhere, Category=General)
	float DiscoverySeconds;

	FString BridgeUrl;
};
