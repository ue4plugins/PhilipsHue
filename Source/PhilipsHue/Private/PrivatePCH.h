// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once


/* Dependencies
 *****************************************************************************/

#include "Core.h"
#include "CoreUObject.h"
#include "Http.h"
#include "Json.h"


/* Private macros
 *****************************************************************************/

DECLARE_LOG_CATEGORY_EXTERN(LogPhilipsHue, Log, All);


/* Private includes
 *****************************************************************************/

// shared
#include "PhilipsHueSettings.h"

// bridges
#include "PhilipsHueBridge.h"
#include "PhilipsHueDiscovery.h"

// lights
#include "PhilipsHueLight.h"
