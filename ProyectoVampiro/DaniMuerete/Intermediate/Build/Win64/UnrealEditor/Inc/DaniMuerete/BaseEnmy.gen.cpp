// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DaniMuerete/BaseEnmy.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseEnmy() {}
// Cross Module References
	DANIMUERETE_API UClass* Z_Construct_UClass_ABaseEnmy_NoRegister();
	DANIMUERETE_API UClass* Z_Construct_UClass_ABaseEnmy();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_DaniMuerete();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	void ABaseEnmy::StaticRegisterNativesABaseEnmy()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABaseEnmy);
	UClass* Z_Construct_UClass_ABaseEnmy_NoRegister()
	{
		return ABaseEnmy::StaticClass();
	}
	struct Z_Construct_UClass_ABaseEnmy_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_playerToPursuit_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_playerToPursuit;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABaseEnmy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_DaniMuerete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnmy_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "BaseEnmy.h" },
		{ "ModuleRelativePath", "BaseEnmy.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnmy_Statics::NewProp_playerToPursuit_MetaData[] = {
		{ "Category", "BaseEnmy" },
		{ "ModuleRelativePath", "BaseEnmy.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABaseEnmy_Statics::NewProp_playerToPursuit = { "playerToPursuit", nullptr, (EPropertyFlags)0x0010000000000801, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABaseEnmy, playerToPursuit), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABaseEnmy_Statics::NewProp_playerToPursuit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnmy_Statics::NewProp_playerToPursuit_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABaseEnmy_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnmy_Statics::NewProp_playerToPursuit,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABaseEnmy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABaseEnmy>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABaseEnmy_Statics::ClassParams = {
		&ABaseEnmy::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABaseEnmy_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnmy_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ABaseEnmy_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnmy_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABaseEnmy()
	{
		if (!Z_Registration_Info_UClass_ABaseEnmy.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABaseEnmy.OuterSingleton, Z_Construct_UClass_ABaseEnmy_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABaseEnmy.OuterSingleton;
	}
	template<> DANIMUERETE_API UClass* StaticClass<ABaseEnmy>()
	{
		return ABaseEnmy::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABaseEnmy);
	struct Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnmy_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnmy_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABaseEnmy, ABaseEnmy::StaticClass, TEXT("ABaseEnmy"), &Z_Registration_Info_UClass_ABaseEnmy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABaseEnmy), 676329730U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnmy_h_2580864942(TEXT("/Script/DaniMuerete"),
		Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnmy_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnmy_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
