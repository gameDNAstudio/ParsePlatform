// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2016 gameDNA studio. All Rights Reserved.

#include "ParsePlatformPrivatePCH.h"
#include "ParsePlatformSettings.h"
#include "ISettingsModule.h"
#include "ParsePlatformBlueprintLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

#if PLATFORM_IOS
	#import <Parse/Parse.h>
	#import "IOSAppDelegate.h"
#endif

DEFINE_LOG_CATEGORY(LogParsePlatform);

#define LOCTEXT_NAMESPACE "ParsePlatform"

class FParsePlatform : public IParsePlatform
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token);
	void ApplicationReceivedRemoteNotification_Handler(FString Json);
};

IMPLEMENT_MODULE( FParsePlatform, ParsePlatform )

// Startup Module
void FParsePlatform::StartupModule()
{
	const UParsePlatformSettings* DefaultSettings = GetDefault<UParsePlatformSettings>();
	
	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "ParsePlatform",
			LOCTEXT("RuntimeSettingsName", "Parse Platform"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the Parse Platform plugin"),
			GetMutableDefault<UParsePlatformSettings>()
			);
	}

#if PLATFORM_IOS
	IOSAppDelegate* appDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];

	if (!DefaultSettings->ApplicationId.IsEmpty() && !DefaultSettings->ClientKey.IsEmpty())
	{
		[Parse setApplicationId : DefaultSettings->ApplicationId.GetNSString()
			clientKey : DefaultSettings->ClientKey.GetNSString()];

		[PFAnalytics trackAppOpenedWithLaunchOptions : appDelegate.launchOptions];
	}
#endif

	// Delegates
	FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddRaw(this, &FParsePlatform::ApplicationRegisteredForRemoteNotifications_Handler);
	FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddRaw(this, &FParsePlatform::ApplicationReceivedRemoteNotification_Handler);

	// Register Remote Notifications
	UKismetSystemLibrary::RegisterForRemoteNotifications();
}

// Shutdown Module
void FParsePlatform::ShutdownModule()
{
	FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.RemoveAll(this);
	FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.RemoveAll(this);
}

// Registered Remote Notifications
void FParsePlatform::ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token)
{
#if PLATFORM_IOS
	NSData* TokenData = [NSData dataWithBytes : Token.GetData() length : Token.Num()];
	PFInstallation* Installation = [PFInstallation currentInstallation];
	[Installation setDeviceTokenFromData : TokenData];
	[Installation saveInBackground];
#endif
}

// Received Remote Notification
void FParsePlatform::ApplicationReceivedRemoteNotification_Handler(FString Json)
{
}

#undef LOCTEXT_NAMESPACE
