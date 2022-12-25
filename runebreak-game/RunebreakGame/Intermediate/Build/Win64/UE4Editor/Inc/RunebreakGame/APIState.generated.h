// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RUNEBREAKGAME_APIState_generated_h
#error "APIState.generated.h already included, missing '#pragma once' in APIState.h"
#endif
#define RUNEBREAKGAME_APIState_generated_h

#define RunebreakGame_Source_RunebreakGame_Public_RunebreakAPI_Models_APIState_h_21_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FApiState_Statics; \
	RUNEBREAKGAME_API static class UScriptStruct* StaticStruct();


template<> RUNEBREAKGAME_API UScriptStruct* StaticStruct<struct FApiState>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID RunebreakGame_Source_RunebreakGame_Public_RunebreakAPI_Models_APIState_h


#define FOREACH_ENUM_ECONNECTIONSTATUS(op) \
	op(EConnectionStatus::Uninitialized) \
	op(EConnectionStatus::Connecting) \
	op(EConnectionStatus::Connected) 

enum class EConnectionStatus : uint8;
template<> RUNEBREAKGAME_API UEnum* StaticEnum<EConnectionStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
