// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueDiscoveryMessages.generated.h"


/**
 * Details about a discovered bridge.
 */
USTRUCT()
struct FPhilipsHueBridgeInfo
{
	GENERATED_BODY()

	/** Unique identifier of the bridge. */
	UPROPERTY()
	FString Id;

	/** Bridge IP address. */
	UPROPERTY()
	FString InternalIpAddress;

	/** Bridge MAC address. */
	UPROPERTY()
	FString MacAddress;

	/** Name of the bridge. */
	UPROPERTY()
	FString Name;
};


/**
 * Response for a bridge discovery request.
 */
USTRUCT()
struct FPhilipsHueDiscoveryResponse
{
	GENERATED_BODY()

	/** List of discovered bridges. */
	UPROPERTY()
	TArray<FPhilipsHueBridgeInfo> BridgeInfos;
};
