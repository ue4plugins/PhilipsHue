// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PrivatePCH.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
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
	FPhilipsHueModule()	{ }

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

		// register settings
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "PhilipsHue",
				LOCTEXT("PhilipsHueSettingsName", "Philips Hue"),
				LOCTEXT("PhilipsHueSettingsDescription", "Configure the Philips Hue plug-in."),
				GetMutableDefault<UPhilipsHueSettings>()
			);

			if (SettingsSection.IsValid())
			{
				SettingsSection->OnModified().BindRaw(this, &FPhilipsHueModule::HandleSettingsSaved);
			}
		}
	}

	virtual void ShutdownModule() override
	{
		// unregister settings
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "PhilipsHue");
		}

	}

	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}

private:

	/** Callback for when the settings were saved. */
	bool HandleSettingsSaved()
	{
		return true;
	}
};


IMPLEMENT_MODULE(FPhilipsHueModule, PhilipsHue);


#undef LOCTEXT_NAMESPACE
