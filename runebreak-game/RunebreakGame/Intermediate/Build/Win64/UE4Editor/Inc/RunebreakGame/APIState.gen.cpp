// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RunebreakGame/Public/RunebreakAPI/Models/APIState.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAPIState() {}
// Cross Module References
	RUNEBREAKGAME_API UEnum* Z_Construct_UEnum_RunebreakGame_EConnectionStatus();
	UPackage* Z_Construct_UPackage__Script_RunebreakGame();
	RUNEBREAKGAME_API UScriptStruct* Z_Construct_UScriptStruct_FApiState();
// End Cross Module References
	static UEnum* EConnectionStatus_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_RunebreakGame_EConnectionStatus, Z_Construct_UPackage__Script_RunebreakGame(), TEXT("EConnectionStatus"));
		}
		return Singleton;
	}
	template<> RUNEBREAKGAME_API UEnum* StaticEnum<EConnectionStatus>()
	{
		return EConnectionStatus_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EConnectionStatus(EConnectionStatus_StaticEnum, TEXT("/Script/RunebreakGame"), TEXT("EConnectionStatus"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_RunebreakGame_EConnectionStatus_Hash() { return 4171519673U; }
	UEnum* Z_Construct_UEnum_RunebreakGame_EConnectionStatus()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_RunebreakGame();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EConnectionStatus"), 0, Get_Z_Construct_UEnum_RunebreakGame_EConnectionStatus_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EConnectionStatus::Uninitialized", (int64)EConnectionStatus::Uninitialized },
				{ "EConnectionStatus::Connecting", (int64)EConnectionStatus::Connecting },
				{ "EConnectionStatus::Connected", (int64)EConnectionStatus::Connected },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Connected.Name", "EConnectionStatus::Connected" },
				{ "Connecting.Name", "EConnectionStatus::Connecting" },
				{ "ModuleRelativePath", "Public/RunebreakAPI/Models/APIState.h" },
				{ "Uninitialized.Name", "EConnectionStatus::Uninitialized" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_RunebreakGame,
				nullptr,
				"EConnectionStatus",
				"EConnectionStatus",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FApiState::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RUNEBREAKGAME_API uint32 Get_Z_Construct_UScriptStruct_FApiState_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FApiState, Z_Construct_UPackage__Script_RunebreakGame(), TEXT("ApiState"), sizeof(FApiState), Get_Z_Construct_UScriptStruct_FApiState_Hash());
	}
	return Singleton;
}
template<> RUNEBREAKGAME_API UScriptStruct* StaticStruct<FApiState>()
{
	return FApiState::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FApiState(FApiState::StaticStruct, TEXT("/Script/RunebreakGame"), TEXT("ApiState"), false, nullptr, nullptr);
static struct FScriptStruct_RunebreakGame_StaticRegisterNativesFApiState
{
	FScriptStruct_RunebreakGame_StaticRegisterNativesFApiState()
	{
		UScriptStruct::DeferCppStructOps<FApiState>(FName(TEXT("ApiState")));
	}
} ScriptStruct_RunebreakGame_StaticRegisterNativesFApiState;
	struct Z_Construct_UScriptStruct_FApiState_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_authToken_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_authToken;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_connectionStatus_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_connectionStatus_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_connectionStatus;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FApiState_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/Models/APIState.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FApiState_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FApiState>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FApiState_Statics::NewProp_authToken_MetaData[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/Models/APIState.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FApiState_Statics::NewProp_authToken = { "authToken", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FApiState, authToken), METADATA_PARAMS(Z_Construct_UScriptStruct_FApiState_Statics::NewProp_authToken_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FApiState_Statics::NewProp_authToken_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus_MetaData[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/Models/APIState.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus = { "connectionStatus", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FApiState, connectionStatus), Z_Construct_UEnum_RunebreakGame_EConnectionStatus, METADATA_PARAMS(Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FApiState_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FApiState_Statics::NewProp_authToken,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FApiState_Statics::NewProp_connectionStatus,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FApiState_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RunebreakGame,
		nullptr,
		&NewStructOps,
		"ApiState",
		sizeof(FApiState),
		alignof(FApiState),
		Z_Construct_UScriptStruct_FApiState_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FApiState_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FApiState_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FApiState_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FApiState()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FApiState_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RunebreakGame();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ApiState"), sizeof(FApiState), Get_Z_Construct_UScriptStruct_FApiState_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FApiState_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FApiState_Hash() { return 3572848083U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
