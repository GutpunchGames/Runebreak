// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RUNEBREAKGAME_MyInterface_generated_h
#error "MyInterface.generated.h already included, missing '#pragma once' in MyInterface.h"
#endif
#define RUNEBREAKGAME_MyInterface_generated_h

#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_SPARSE_DATA
#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_RPC_WRAPPERS
#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	RUNEBREAKGAME_API UMyInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyInterface) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(RUNEBREAKGAME_API, UMyInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyInterface); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	RUNEBREAKGAME_API UMyInterface(UMyInterface&&); \
	RUNEBREAKGAME_API UMyInterface(const UMyInterface&); \
public:


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	RUNEBREAKGAME_API UMyInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	RUNEBREAKGAME_API UMyInterface(UMyInterface&&); \
	RUNEBREAKGAME_API UMyInterface(const UMyInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(RUNEBREAKGAME_API, UMyInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyInterface)


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUMyInterface(); \
	friend struct Z_Construct_UClass_UMyInterface_Statics; \
public: \
	DECLARE_CLASS(UMyInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/RunebreakGame"), RUNEBREAKGAME_API) \
	DECLARE_SERIALIZER(UMyInterface)


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_GENERATED_UINTERFACE_BODY() \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_GENERATED_UINTERFACE_BODY() \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IMyInterface() {} \
public: \
	typedef UMyInterface UClassType; \
	typedef IMyInterface ThisClass; \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_INCLASS_IINTERFACE \
protected: \
	virtual ~IMyInterface() {} \
public: \
	typedef UMyInterface UClassType; \
	typedef IMyInterface ThisClass; \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_11_PROLOG
#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_SPARSE_DATA \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_RPC_WRAPPERS \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_SPARSE_DATA \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	RunebreakGame_Source_RunebreakGame_Public_MyInterface_h_14_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RUNEBREAKGAME_API UClass* StaticClass<class UMyInterface>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID RunebreakGame_Source_RunebreakGame_Public_MyInterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
