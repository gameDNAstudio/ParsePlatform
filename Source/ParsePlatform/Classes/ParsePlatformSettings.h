// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2016 gameDNA studio. All Rights Reserved.

#pragma once

#include "ParsePlatformSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UParsePlatformSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UParsePlatformSettings(const FObjectInitializer& ObjectInitializer);
	
	// Application ID
	UPROPERTY(Config, EditAnywhere, Category = "Parse Platform Configuration", meta = (DisplayName = "Application ID"))
	FString ApplicationId;

	// Client Key
	UPROPERTY(Config, EditAnywhere, Category = "Parse Platform Configuration", meta = (DisplayName = "Client Key"))
	FString ClientKey;
};
