// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DaniMuerete/DaniMuereteGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDaniMuereteGameMode() {}
// Cross Module References
	DANIMUERETE_API UClass* Z_Construct_UClass_ADaniMuereteGameMode_NoRegister();
	DANIMUERETE_API UClass* Z_Construct_UClass_ADaniMuereteGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_DaniMuerete();
// End Cross Module References
	void ADaniMuereteGameMode::StaticRegisterNativesADaniMuereteGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADaniMuereteGameMode);
	UClass* Z_Construct_UClass_ADaniMuereteGameMode_NoRegister()
	{
		return ADaniMuereteGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ADaniMuereteGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADaniMuereteGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_DaniMuerete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADaniMuereteGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DaniMuereteGameMode.h" },
		{ "ModuleRelativePath", "DaniMuereteGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADaniMuereteGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADaniMuereteGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ADaniMuereteGameMode_Statics::ClassParams = {
		&ADaniMuereteGameMode::StaticClass,
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
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ADaniMuereteGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADaniMuereteGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADaniMuereteGameMode()
	{
		if (!Z_Registration_Info_UClass_ADaniMuereteGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADaniMuereteGameMode.OuterSingleton, Z_Construct_UClass_ADaniMuereteGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ADaniMuereteGameMode.OuterSingleton;
	}
	template<> DANIMUERETE_API UClass* StaticClass<ADaniMuereteGameMode>()
	{
		return ADaniMuereteGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADaniMuereteGameMode);
	struct Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_DaniMuereteGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_DaniMuereteGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ADaniMuereteGameMode, ADaniMuereteGameMode::StaticClass, TEXT("ADaniMuereteGameMode"), &Z_Registration_Info_UClass_ADaniMuereteGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADaniMuereteGameMode), 1348996776U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_DaniMuereteGameMode_h_3953138204(TEXT("/Script/DaniMuerete"),
		Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_DaniMuereteGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_DaniMuereteGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
