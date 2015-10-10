// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueBridgeMessages.generated.h"


/**
 * A Hue error message.
 */
USTRUCT()
struct FPhilipsHueError
{
	GENERATED_BODY()

	/**
	 * The type of error.
	 *
	 * This value could be a key (i.e. the name of the resource, method,
	 * parameter or value being accessed), or a generic error number.
	 * See http://www.developers.meethue.com/documentation/error-messages
	 * for details.
	 */
	UPROPERTY()
	FString Type;

	/** Link to the error message page, if any. */
	UPROPERTY()
	FString Address;

	/** Description of the error. */
	UPROPERTY()
	FString Description;
};


/* Configuration API (/config)
 *****************************************************************************/

/**
 * Software update states.
 */
UENUM()
enum class EPhilipsHueSoftwareUpdateState : uint8
{
	/** No update available. */
	NoUpdate,

	/** Downloading updates. */
	Downloading,

	/** Updates are ready to be installed. */
	ReadyForInstall,

	/** Installing updates. */
	Installing
};


/**
 * Device types info for software updates.
 */
USTRUCT()
struct FPhilipsHueDeviceTypes
{
	GENERATED_BODY()

public: // API 1.4

	UPROPERTY()
	bool Bridge;

	/** List of lights to be updated or empty if no update available. */
	UPROPERTY()
	TArray<FString> Lights;

public: // API 1.7

	/** List of sensors to be updated or empty if no update available. */
	UPROPERTY()
	TArray<FString> Sensors;
};


/**
 * Information related to software updates.
 */
USTRUCT()
struct FPhilipsHueSoftwareUpdate
{
	GENERATED_BODY()

	// API 1.0

	/**
	 * The notify flag is set to true when software has been successfully installed.
	 * This can be used to notify the user upon installation and should be reset to
	 * false when the user has seen this information.
	 */
	UPROPERTY()
	bool Notify;

	/** Brief release note. */
	UPROPERTY()
	FString Text;

	UPROPERTY()
	EPhilipsHueSoftwareUpdateState UpdateState;

	/** URL to release notes. */
	UPROPERTY()
	FString Url;

	// API 1.4

	/**
	 * Setting this flag to true lets the bridge search for software update in the
	 * Hue portal. After the search attempt, this flag is reset to false. Requires
	 * portal connection to update the software.
	 */
	UPROPERTY()
	bool CheckForUpdate;

	/** Details types of updates available.  Only present in update state 2 and 3. */
	UPROPERTY()
	FPhilipsHueDeviceTypes DeviceTypes;
};


/**
 * A user account.
 */
USTRUCT()
struct FPhilipsHueUserAccount
{
	GENERATED_BODY()

	/** Date and time the user account was created. */
	UPROPERTY()
	FString CreateDate;

	/** Date and time the user account was last used. */
	UPROPERTY()
	FString LastUseDate;

	/** Name of the user account. */
	UPROPERTY()
	FString Name;
};


/**
 * Bridge configuration information.
 */
USTRUCT()
struct FPhilipsHueConfiguration
{
	GENERATED_BODY()

public: // API 1.0

	/** Whether the bridge uses DHCP to acquire an IP address. */
	UPROPERTY()
	bool Dhcp;

	/** The IP address of the network gateway. */
	UPROPERTY()
	FString Gateway;

	/** The bridge's current IP address. */
	UPROPERTY()
	FString IpAddress;

	/** Indicates whether the link button has been pressed within the last 30 seconds. */
	UPROPERTY()
	bool LinkButton;

	/** MAC address of the bridge, i.e. "00:17:88:20:01:0a". */
	UPROPERTY()
	FString Mac;

	/** Name of the bridge, i.e. "Philips hue". */
	UPROPERTY()
	FString Name;

	/** The bridge's subnet mask. */
	UPROPERTY()
	FString NetMask;

	/** This indicates whether the bridge is registered to synchronize data with a portal account. */
	UPROPERTY()
	bool PortalServices;

	/** Network proxy address, if any. */
	UPROPERTY()
	FString ProxyAddress;

	/** network proxy port number, if any. */
	UPROPERTY()
	int32 ProxyPort;

	/** Contains information related to software updates. */
	UPROPERTY()
	FPhilipsHueSoftwareUpdate SwUpdate;

	/** Software version, i.e. "01028090". */
	UPROPERTY()
	FString SwVersion;

	/** The bridge's UTC date and time. */
	UPROPERTY()
	FString Utc;

	/** A list of white-listed user IDs. */
	UPROPERTY()
	TMap<FString, FPhilipsHueUserAccount> Whitelist;

public:	// API 1.2.1

	/** The version of the hue API in the format <major>.<minor>.<patch>, for example "1.2.1" */
	UPROPERTY()
	FString ApiVersion;

	/** The bridge's local date and time. */
	UPROPERTY()
	FString LocalTime;

	/* Indicates whether the bridge is signed on to the Hue portal. */
	UPROPERTY()
	TMap<FString, FString> PortalState;

	/** The bridge's time zone. */
	UPROPERTY()
	FString Timezone;

	// API 1.3

	/** The current wireless frequency channel used by the bridge. It can take values of 11, 15, 20,25 or 0 if undefined (factory new). */
	UPROPERTY()
	int32 ZigBeeChannel;

public: // API 1.9

	/**
	 * Perform a touchlink action if set to true, setting to false is ignored.
	 *
	 * When set to true a touchlink procedure starts which adds the closet lamp
	 * (within range) to the ZigBee network.  You can then search for new lights
	 * and lamp will show up in the bridge.
	 */
	UPROPERTY()
	bool TouchLink;

	// API 1.10

	/** Whether the bridge settings are factory new. */
	UPROPERTY()
	bool FactoryNew;

	/** Identifier of the old bridge where the settings were transferred from. */
	UPROPERTY()
	FString ReplacesBridgeId;


	/** Unique bridge identifier, i.e. "001788FFFE20010A". */
	UPROPERTY()
	FString BridgeId;

public:

	/** Default constructor. */
	FPhilipsHueConfiguration()
		: ApiVersion(TEXT("1.0"))
	{ }
};
