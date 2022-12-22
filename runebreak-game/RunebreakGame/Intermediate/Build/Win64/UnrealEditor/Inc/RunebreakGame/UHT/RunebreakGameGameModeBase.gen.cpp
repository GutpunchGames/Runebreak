// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RunebreakGame/RunebreakGameGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRunebreakGameGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_ARunebreakGameGameModeBase();
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_ARunebreakGameGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_RunebreakGame();
// End Cross Module References
	void ARunebreakGameGameModeBase::StaticRegisterNativesARunebreakGameGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARunebreakGameGameModeBase);
	UClass* Z_Construct_UClass_ARunebreakGameGameModeBase_NoRegister()
	{
		return ARunebreakGameGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ARunebreakGameGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_RunebreakGame,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "RunebreakGameGameModeBase.h" },
		{ "ModuleRelativePath", "RunebreakGameGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARunebreakGameGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::ClassParams = {
		&ARunebreakGameGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ARunebreakGameGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ARunebreakGameGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARunebreakGameGameModeBase.OuterSingleton, Z_Construct_UClass_ARunebreakGameGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ARunebreakGameGameModeBase.OuterSingleton;
	}
	template<> RUNEBREAKGAME_API UClass* StaticClass<ARunebreakGameGameModeBase>()
	{
		return ARunebreakGameGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARunebreakGameGameModeBase);
	ARunebreakGameGameModeBase::~ARunebreakGameGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_Users_Andy_Development_Runebreak_runebreak_game_RunebreakGame_Source_RunebreakGame_RunebreakGameGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Andy_Development_Runebreak_runebreak_game_RunebreakGame_Source_RunebreakGame_RunebreakGameGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ARunebreakGameGameModeBase, ARunebreakGameGameModeBase::StaticClass, TEXT("ARunebreakGameGameModeBase"), &Z_Registration_Info_UClass_ARunebreakGameGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARunebreakGameGameModeBase), 1810089960U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Andy_Development_Runebreak_runebreak_game_RunebreakGame_Source_RunebreakGame_RunebreakGameGameModeBase_h_2156165437(TEXT("/Script/RunebreakGame"),
		Z_CompiledInDeferFile_FID_Users_Andy_Development_Runebreak_runebreak_game_RunebreakGame_Source_RunebreakGame_RunebreakGameGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Andy_Development_Runebreak_runebreak_game_RunebreakGame_Source_RunebreakGame_RunebreakGameGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
