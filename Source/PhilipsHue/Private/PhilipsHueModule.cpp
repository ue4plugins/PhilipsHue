// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"
#include "ModuleInterface.h"
#include "ModuleManager.h"


DEFINE_LOG_CATEGORY(LogPhilipsHue);

#define LOCTEXT_NAMESPACE "FPhilipsHueModule"


/**
 * Implements the PhilipsHue module.
 */
class FPhilipsHueModule
	: public IModuleInterface
{
public:

	/** Default constructor. */
	FPhilipsHueModule()
		: Initialized(false)
	{ }

public:

	// IModuleInterface interface

	virtual void StartupModule() override
	{
		// load required libraries
		FHttpModule* HttpModule = FModuleManager::LoadModulePtr<FHttpModule>("Http");

		if (HttpModule == nullptr)
		{
			UE_LOG(LogPhilipsHue, Log, TEXT("Failed to load Http module"));

			return;
		}

		Initialized = true;
	}

	virtual void ShutdownModule() override
	{
		if (!Initialized)
		{
			return;
		}

		Initialized = false;
	}

private:

	/** Whether the module has been initialized. */
	bool Initialized;
};


IMPLEMENT_MODULE(FPhilipsHueModule, PhilipsHue);


#undef LOCTEXT_NAMESPACE
