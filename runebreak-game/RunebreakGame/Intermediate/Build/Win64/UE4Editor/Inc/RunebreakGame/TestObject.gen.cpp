// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RunebreakGame/Public/TestObject/TestObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestObject() {}
// Cross Module References
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_UTestObject_NoRegister();
	RUNEBREAKGAME_API UClass* Z_Construct_UClass_UTestObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_RunebreakGame();
// End Cross Module References
	DEFINE_FUNCTION(UTestObject::execDoThing)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DoThing();
		P_NATIVE_END;
	}
	void UTestObject::StaticRegisterNativesUTestObject()
	{
		UClass* Class = UTestObject::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DoThing", &UTestObject::execDoThing },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UTestObject_DoThing_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTestObject_DoThing_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TestObject/TestObject.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UTestObject_DoThing_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTestObject, nullptr, "DoThing", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UTestObject_DoThing_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestObject_DoThing_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UTestObject_DoThing()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UTestObject_DoThing_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UTestObject_NoRegister()
	{
		return UTestObject::StaticClass();
	}
	struct Z_Construct_UClass_UTestObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTestObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RunebreakGame,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UTestObject_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UTestObject_DoThing, "DoThing" }, // 225212847
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestObject_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "TestObject/TestObject.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/TestObject/TestObject.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTestObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTestObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UTestObject_Statics::ClassParams = {
		&UTestObject::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UTestObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTestObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTestObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UTestObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UTestObject, 168822692);
	template<> RUNEBREAKGAME_API UClass* StaticClass<UTestObject>()
	{
		return UTestObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UTestObject(Z_Construct_UClass_UTestObject, &UTestObject::StaticClass, TEXT("/Script/RunebreakGame"), TEXT("UTestObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTestObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
