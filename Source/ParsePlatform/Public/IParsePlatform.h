// Parse Platform Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2016 gameDNA studio. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class IParsePlatform : public IModuleInterface
{
public:
	static inline IParsePlatform& Get()
	{
		return FModuleManager::LoadModuleChecked< IParsePlatform >("ParsePlatform");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ParsePlatform");
	}
};
