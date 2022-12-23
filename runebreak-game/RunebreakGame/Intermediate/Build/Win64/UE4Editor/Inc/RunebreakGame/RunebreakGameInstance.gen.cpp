// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RunebreakGame/Public/GameInstance/RunebreakGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRunebreakGameInstance() {}
// Cross Module References
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_URunebreakGameInstance_NoRegister();
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_URunebreakGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_RunebreakGame();
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_URunebreakAPI_NoRegister();
// End Cross Module References
	void URunebreakGameInstance::StaticRegisterNativesURunebreakGameInstance()
	{
	}
	UClass* Z_Construct_UClass_URunebreakGameInstance_NoRegister()
	{
		return URunebreakGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_URunebreakGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_api_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_api;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URunebreakGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_RunebreakGame,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URunebreakGameInstance_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameInstance/RunebreakGameInstance.h" },
		{ "ModuleRelativePath", "Public/GameInstance/RunebreakGameInstance.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URunebreakGameInstance_Statics::NewProp_api_MetaData[] = {
		{ "Category", "RunebreakGameInstance" },
		{ "ModuleRelativePath", "Public/GameInstance/RunebreakGameInstance.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URunebreakGameInstance_Statics::NewProp_api = { "api", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URunebreakGameInstance, api), Z_Construct_UClass_URunebreakAPI_NoRegister, METADATA_PARAMS(Z_Construct_UClass_URunebreakGameInstance_Statics::NewProp_api_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URunebreakGameInstance_Statics::NewProp_api_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URunebreakGameInstance_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URunebreakGameInstance_Statics::NewProp_api,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URunebreakGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URunebreakGameInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_URunebreakGameInstance_Statics::ClassParams = {
		&URunebreakGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_URunebreakGameInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_URunebreakGameInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_URunebreakGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_URunebreakGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_URunebreakGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_URunebreakGameInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(URunebreakGameInstance, 3115020376);
	template<> RUNEBREAKGAME_API UClass* StaticClass<URunebreakGameInstance>()
	{
		return URunebreakGameInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_URunebreakGameInstance(Z_Construct_UClass_URunebreakGameInstance, &URunebreakGameInstance::StaticClass, TEXT("/Script/RunebreakGame"), TEXT("URunebreakGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(URunebreakGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
