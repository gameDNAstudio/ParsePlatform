// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2016 gameDNA studio. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ParsePlatformBlueprintLibrary.generated.h"

UCLASS()
class PARSEPLATFORM_API UParsePlatformBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Get Parse Installation ID
	UFUNCTION(BlueprintCallable, Category = "Parse Platform", DisplayName = "Get Parse Installation ID")
	static FString GetParseInstallationId();

	// Subscribe To Channel
	UFUNCTION(BlueprintCallable, Category = "Parse Platform", DisplayName = "Subscribe To Channel")
	static void SubscribeToChannel(FString ChannelName);

	// Unsubscribe From Channel
	UFUNCTION(BlueprintCallable, Category = "Parse Platform", DisplayName = "Unsubscribe From Channel")
	static void UnsubscribeFromChannel(FString ChannelName);
};
