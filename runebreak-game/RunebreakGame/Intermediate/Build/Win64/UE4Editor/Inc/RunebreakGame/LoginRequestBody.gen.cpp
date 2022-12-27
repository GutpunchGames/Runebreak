// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RunebreakGame/Public/RunebreakAPI/REST/LoginRequestBody.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLoginRequestBody() {}
// Cross Module References
	RUNEBREAKGAME_API UScriptStruct* Z_Construct_UScriptStruct_FLoginRequestBody();
	UPackage* Z_Construct_UPackage__Script_RunebreakGame();
// End Cross Module References
class UScriptStruct* FLoginRequestBody::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RUNEBREAKGAME_API uint32 Get_Z_Construct_UScriptStruct_FLoginRequestBody_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLoginRequestBody, Z_Construct_UPackage__Script_RunebreakGame(), TEXT("LoginRequestBody"), sizeof(FLoginRequestBody), Get_Z_Construct_UScriptStruct_FLoginRequestBody_Hash());
	}
	return Singleton;
}
template<> RUNEBREAKGAME_API UScriptStruct* StaticStruct<FLoginRequestBody>()
{
	return FLoginRequestBody::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLoginRequestBody(FLoginRequestBody::StaticStruct, TEXT("/Script/RunebreakGame"), TEXT("LoginRequestBody"), false, nullptr, nullptr);
static struct FScriptStruct_RunebreakGame_StaticRegisterNativesFLoginRequestBody
{
	FScriptStruct_RunebreakGame_StaticRegisterNativesFLoginRequestBody()
	{
		UScriptStruct::DeferCppStructOps<FLoginRequestBody>(FName(TEXT("LoginRequestBody")));
	}
} ScriptStruct_RunebreakGame_StaticRegisterNativesFLoginRequestBody;
	struct Z_Construct_UScriptStruct_FLoginRequestBody_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_username_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_username;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_password_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_password;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLoginRequestBody_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/REST/LoginRequestBody.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLoginRequestBody>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_username_MetaData[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/REST/LoginRequestBody.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_username = { "username", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLoginRequestBody, username), METADATA_PARAMS(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_username_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_username_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_password_MetaData[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/REST/LoginRequestBody.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_password = { "password", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLoginRequestBody, password), METADATA_PARAMS(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_password_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_password_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLoginRequestBody_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_username,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLoginRequestBody_Statics::NewProp_password,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLoginRequestBody_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RunebreakGame,
		nullptr,
		&NewStructOps,
		"LoginRequestBody",
		sizeof(FLoginRequestBody),
		alignof(FLoginRequestBody),
		Z_Construct_UScriptStruct_FLoginRequestBody_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLoginRequestBody_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLoginRequestBody()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLoginRequestBody_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RunebreakGame();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LoginRequestBody"), sizeof(FLoginRequestBody), Get_Z_Construct_UScriptStruct_FLoginRequestBody_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLoginRequestBody_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLoginRequestBody_Hash() { return 1674361324U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
