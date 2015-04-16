// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueLight.generated.h"


/**
 * Structure for setting the state of a Philips Hue light.
 */
USTRUCT()
struct FPhilipsHueLightSetState
{
	GENERATED_USTRUCT_BODY()

	/** Whether the light is on. */
	UPROPERTY()
	bool On;

	/** Brightness. */
	UPROPERTY()
	uint8 Bri;

	/** Hue. */
	UPROPERTY()
	uint8 Hue;

	/** Saturation. */
	UPROPERTY()
	uint8 Sat;

	/** Color's X and Y coordinate in CIE space. */
	UPROPERTY()
	float Xy[2];

	/** Mired Color temperature between 153 (6500K) and 500 (2000K). */
	UPROPERTY()
	uint16 Ct;

	/** Alert effect name, i.e. "none", "select" or "lselect". */
	UPROPERTY()
	FString Alert;

	/** Dynamic effect name, i.e. "none" or "colorloop". */
	UPROPERTY()
	FString Effect;

	/** Duration of the state transition (multiple of 100ms). */
	UPROPERTY()
	uint16 TransitionTime;

	/** Brightness increment/decrement (-254 to 254). */
	UPROPERTY()
	int16 BriInc;

	/** Saturation increment/decrement (-254 to 254). */
	UPROPERTY()
	int16 SatInc;

	/** Hue increment/decrement (-65534 to 65534). */
	UPROPERTY()
	int32 HueInc;

	/** Color temperature increment/decrement (-65534 to 65534). */
	UPROPERTY()
	int32 CtInc;

	/** XY increment/decrement (-0.5 to 0.5). */
	UPROPERTY()
	float XyInc;
};


/**
 * The current state of a Philips Hue light.
 */
USTRUCT()
struct FPhilipsHueLightState
{
	GENERATED_USTRUCT_BODY()

	/** Whether the light is on. */
	UPROPERTY()
	bool On;

	/** Brightness. */
	UPROPERTY()
	uint8 Bri;

	/** Hue. */
	UPROPERTY()
	uint8 Hue;

	/** Saturation. */
	UPROPERTY()
	uint8 Sat;

	/** Color's X and Y coordinate in CIE space. */
	UPROPERTY()
	float Xy[2];

	/** Mired Color temperature between 153 (6500K) and 500 (2000K). */
	UPROPERTY()
	uint16 Ct;

	/** Alert effect name, i.e. "none", "select" or "lselect". */
	UPROPERTY()
	FString Alert;

	/** Dynamic effect name, i.e. "none" or "colorloop". */
	UPROPERTY()
	FString Effect;

	/** Active color mode, i.e. "xy" or "ct". */
	UPROPERTY()
	FString ColorMode;

	/** Whether the light is reachable by the bridge. */
	UPROPERTY()
	bool Reachable;
};


USTRUCT()
struct FPhilipsHueLightInfo
{
	GENERATED_USTRUCT_BODY()

	/** State of the light. */
	UPROPERTY()
	FPhilipsHueLightState State;

	/** Light type, i.e. "Extended color light". */
	UPROPERTY()
	FString Type;

	/** Unique name of the light. */
	UPROPERTY()
	FString Name;

	/** Hardware model identifier. */
	UPROPERTY()
	FString ModelId;

	/** Unique device identifier (MAC address). */
	UPROPERTY()
	FString UniqueId;

	/** Manufacturer's name. */
	UPROPERTY()
	FString ManufacturerName;

	/** Software version number. */
	UPROPERTY()
	FString SwVersion;
};


/**
 * Represents a Philips Hue light.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class UPhilipsHueLight
	: public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** Holds the light's data. */
	FPhilipsHueLightInfo LightInfo;
};
