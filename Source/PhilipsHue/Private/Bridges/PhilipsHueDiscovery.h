// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueBridge.h"
#include "PhilipsHueDiscovery.generated.h"


UENUM(BlueprintType)
enum class EPhilipsHueDiscoveryResult : uint8
{
	/** Bridge discovery succeeded. */
	Success,

	/** Failed to get response. */
	NoResponse,

	/** Failed to serialize response. */
	SerializationFailure
};


UENUM(BlueprintType)
enum class EPhilipsHueDiscoveryState : uint8
{
	/** No discovery in progress. */
	Idle,

	/** Discovery using meethue.com in progress. */
	MeetHue,

	/** Discovery using UPNP in progress. */
	Upnp,
};


/** Multicast delegate that is invoked when bridge discovery has finished. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhilipsHueDiscoveryCompleted, EPhilipsHueDiscoveryResult, Result);


/**
 * A Philips Hue bridge discovery.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class UPhilipsHueDiscovery
	: public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** Discover Philips Hue bridges on the network. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Discovery")
	void DiscoverBridges();

	/** Forget all bridges on the network. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Discovery")
	void ForgetBridges();

	/** Gets the current discovery state. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Discovery")
	EPhilipsHueDiscoveryState GetState()
	{
		return State;
	}

public:

	/** A delegate that is invoked when bridge discovery finished. */
	UPROPERTY(BlueprintAssignable, Category="PhilipsHue|Discover")
	FOnPhilipsHueDiscoveryCompleted OnDiscoveryCompleted;

protected:

	/**
	 * Process a HTTP response.
	 *
	 * @param HttpResponse The response to process.
	 */
	void ProcessHttpResponse(FHttpResponsePtr HttpResponse, bool Succeeded);

private:

	/** Handles the completion of HTTP requests. */
	void HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

private:

	/** Collection of discovered bridges. */
	UPROPERTY(transient)
	TMap<FString, UPhilipsHueBridge*> BridgesById;

	/** Current discovery state. */
	UPROPERTY(transient)
	EPhilipsHueDiscoveryState State;
};
