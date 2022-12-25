// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RunebreakGame/Public/RunebreakAPI/RunebreakAPI.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRunebreakAPI() {}
// Cross Module References
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_URunebreakAPI_NoRegister();
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_URunebreakAPI();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_RunebreakGame();
// End Cross Module References
	DEFINE_FUNCTION(URunebreakAPI::execTestJsonSerialization)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->TestJsonSerialization();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URunebreakAPI::execLogin)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Login();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URunebreakAPI::execDoThing)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DoThing();
		P_NATIVE_END;
	}
	void URunebreakAPI::StaticRegisterNativesURunebreakAPI()
	{
		UClass* Class = URunebreakAPI::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DoThing", &URunebreakAPI::execDoThing },
			{ "Login", &URunebreakAPI::execLogin },
			{ "TestJsonSerialization", &URunebreakAPI::execTestJsonSerialization },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_URunebreakAPI_DoThing_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URunebreakAPI_DoThing_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/RunebreakAPI.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URunebreakAPI_DoThing_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URunebreakAPI, nullptr, "DoThing", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URunebreakAPI_DoThing_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URunebreakAPI_DoThing_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URunebreakAPI_DoThing()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URunebreakAPI_DoThing_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URunebreakAPI_Login_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URunebreakAPI_Login_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/RunebreakAPI.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URunebreakAPI_Login_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URunebreakAPI, nullptr, "Login", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URunebreakAPI_Login_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URunebreakAPI_Login_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URunebreakAPI_Login()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URunebreakAPI_Login_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RunebreakAPI/RunebreakAPI.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URunebreakAPI, nullptr, "TestJsonSerialization", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_URunebreakAPI_NoRegister()
	{
		return URunebreakAPI::StaticClass();
	}
	struct Z_Construct_UClass_URunebreakAPI_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URunebreakAPI_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RunebreakGame,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_URunebreakAPI_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_URunebreakAPI_DoThing, "DoThing" }, // 145054829
		{ &Z_Construct_UFunction_URunebreakAPI_Login, "Login" }, // 379618836
		{ &Z_Construct_UFunction_URunebreakAPI_TestJsonSerialization, "TestJsonSerialization" }, // 3930589029
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URunebreakAPI_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "RunebreakAPI/RunebreakAPI.h" },
		{ "ModuleRelativePath", "Public/RunebreakAPI/RunebreakAPI.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_URunebreakAPI_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URunebreakAPI>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_URunebreakAPI_Statics::ClassParams = {
		&URunebreakAPI::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_URunebreakAPI_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_URunebreakAPI_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_URunebreakAPI()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_URunebreakAPI_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(URunebreakAPI, 2103794156);
	template<> RUNEBREAKGAME_API UClass* StaticClass<URunebreakAPI>()
	{
		return URunebreakAPI::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_URunebreakAPI(Z_Construct_UClass_URunebreakAPI, &URunebreakAPI::StaticClass, TEXT("/Script/RunebreakGame"), TEXT("URunebreakAPI"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(URunebreakAPI);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
