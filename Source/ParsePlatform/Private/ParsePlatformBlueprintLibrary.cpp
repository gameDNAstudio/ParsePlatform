// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2016 gameDNA studio. All Rights Reserved.

#include "ParsePlatformPrivatePCH.h"
#include "ParsePlatformBlueprintLibrary.h"

#if PLATFORM_IOS
#import <Parse/Parse.h>
#import "IOSAppDelegate.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif

#if PLATFORM_ANDROID
FString AndroidThunkCpp_GetParseInstallationId()
{
	FString ParseInstallationId = FString("");
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetParseInstallationId", "()Ljava/lang/String;", false);
		jstring ParseInstallationIdString = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
		const char *nativeParseInstallationIdString = Env->GetStringUTFChars(ParseInstallationIdString, 0);
		ParseInstallationId = FString(nativeParseInstallationIdString);
		Env->ReleaseStringUTFChars(ParseInstallationIdString, nativeParseInstallationIdString);
		Env->DeleteLocalRef(ParseInstallationIdString);
	}
	return ParseInstallationId;
}

void AndroidThunkCpp_ParseSubscribeToChannel(FString& ChannelName)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring ChannelNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*ChannelName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ParseSubscribeToChannel", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, ChannelNameFinal);
		Env->DeleteLocalRef(ChannelNameFinal);
	}
}

void AndroidThunkCpp_ParseUnsubscribeFromChannel(FString& ChannelName)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring ChannelNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*ChannelName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ParseUnsubscribeFromChannel", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, ChannelNameFinal);
		Env->DeleteLocalRef(ChannelNameFinal);
	}
}
#endif

UParsePlatformBlueprintLibrary::UParsePlatformBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get Parse Installation ID
FString UParsePlatformBlueprintLibrary::GetParseInstallationId() {
#if PLATFORM_IOS
	PFInstallation* Installation = [PFInstallation currentInstallation];
	return FString([Installation installationId]);
#elif PLATFORM_ANDROID
	return AndroidThunkCpp_GetParseInstallationId();
#endif

	return FString("");
}

// Subscribe To Channel
void UParsePlatformBlueprintLibrary::SubscribeToChannel(FString ChannelName) {
	if (ChannelName.Len() > 0) {
#if PLATFORM_IOS
		[PFPush subscribeToChannelInBackground : ChannelName.GetNSString()];
#elif PLATFORM_ANDROID
		AndroidThunkCpp_ParseSubscribeToChannel(ChannelName);
#endif
	}
}

// Unsubscribe From Channel
void UParsePlatformBlueprintLibrary::UnsubscribeFromChannel(FString ChannelName) {
	if (ChannelName.Len() > 0) {
#if PLATFORM_IOS
		[PFPush unsubscribeFromChannelInBackground : ChannelName.GetNSString()];
#elif PLATFORM_ANDROID
		AndroidThunkCpp_ParseUnsubscribeFromChannel(ChannelName);
#endif
	}
}
