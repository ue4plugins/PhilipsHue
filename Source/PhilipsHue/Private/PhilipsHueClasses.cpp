// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"


/* Constructors
 *****************************************************************************/

UPhilipsHueSettings::UPhilipsHueSettings( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
	, BridgeUrl()
	, DiscoverySeconds(10.0f)
{ }
