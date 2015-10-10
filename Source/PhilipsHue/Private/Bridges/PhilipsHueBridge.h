// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueBridgeMessages.h"
#include "PhilipsHueBridge.generated.h"


/** Multicast delegate that is invoked when a bridge has been connected. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhilipsHueBridgeConnected, FString, BridgeId);

/** Multicast delegate that is invoked when a bridge has been disconnected. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhilipsHueBridgeDisconnected, FString, BridgeId);


/**
 * A Philips Hue bridge.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class UPhilipsHueBridge
	: public UObject
{
	GENERATED_BODY()

	/** Default constructor. */
	UPhilipsHueBridge();

	/** Destructor. */
	~UPhilipsHueBridge();

public:

	/** Bridge configuration. */
	UPROPERTY(BlueprintReadOnly, Category="PhilipsHue|Bridge")
	FPhilipsHueConfiguration Configuration;

	/** Unique bridge identifier. */
	UPROPERTY(BlueprintReadOnly, Category="PhilipsHue|Bridge")
	FString Id;

public:

	/**
	 * Connect the bridge.
	 *
	 * @param User The user account identifier to authenticate with.
	 */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Bridge")
	void Connect(const FString& User);

	/** Disconnect the bridge. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Bridge")
	void Disconnect();

public:

	/** A delegate that is invoked when a bridge has been connected. */
	UPROPERTY(BlueprintAssignable, Category="PhilipsHue|Bridge")
	FOnPhilipsHueBridgeConnected OnConnected;

	/** A delegate that is invoked when a bridge has been disconnected. */
	UPROPERTY(BlueprintAssignable, Category="PhilipsHue|Bridge")
	FOnPhilipsHueBridgeDisconnected OnDisconnected;

private:

	/** Handles the completion of HTTP requests. */
	void HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	/** Handles the ticker. */
	bool HandleTicker(float DeltaTime);

private:

	/** Whether the bridge is connected. */
	bool Connected;

	/** The identifier of the connect user account. */
	FString ConnectedUser;

	/** Handle to the registered ticker. */
	FDelegateHandle TickerHandle;
};
