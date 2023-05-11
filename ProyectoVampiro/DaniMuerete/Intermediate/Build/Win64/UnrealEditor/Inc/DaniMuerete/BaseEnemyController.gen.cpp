// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DaniMuerete/BaseEnemyController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseEnemyController() {}
// Cross Module References
	DANIMUERETE_API UClass* Z_Construct_UClass_ABaseEnemyController_NoRegister();
	DANIMUERETE_API UClass* Z_Construct_UClass_ABaseEnemyController();
	AIMODULE_API UClass* Z_Construct_UClass_AAIController();
	UPackage* Z_Construct_UPackage__Script_DaniMuerete();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	void ABaseEnemyController::StaticRegisterNativesABaseEnemyController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABaseEnemyController);
	UClass* Z_Construct_UClass_ABaseEnemyController_NoRegister()
	{
		return ABaseEnemyController::StaticClass();
	}
	struct Z_Construct_UClass_ABaseEnemyController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_player_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_player;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABaseEnemyController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAIController,
		(UObject* (*)())Z_Construct_UPackage__Script_DaniMuerete,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemyController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "BaseEnemyController.h" },
		{ "ModuleRelativePath", "BaseEnemyController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemyController_Statics::NewProp_player_MetaData[] = {
		{ "Category", "Pursuit" },
		{ "ModuleRelativePath", "BaseEnemyController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABaseEnemyController_Statics::NewProp_player = { "player", nullptr, (EPropertyFlags)0x0010000000000801, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABaseEnemyController, player), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABaseEnemyController_Statics::NewProp_player_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemyController_Statics::NewProp_player_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABaseEnemyController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemyController_Statics::NewProp_player,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABaseEnemyController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABaseEnemyController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABaseEnemyController_Statics::ClassParams = {
		&ABaseEnemyController::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABaseEnemyController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemyController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ABaseEnemyController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemyController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABaseEnemyController()
	{
		if (!Z_Registration_Info_UClass_ABaseEnemyController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABaseEnemyController.OuterSingleton, Z_Construct_UClass_ABaseEnemyController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABaseEnemyController.OuterSingleton;
	}
	template<> DANIMUERETE_API UClass* StaticClass<ABaseEnemyController>()
	{
		return ABaseEnemyController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABaseEnemyController);
	struct Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnemyController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnemyController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABaseEnemyController, ABaseEnemyController::StaticClass, TEXT("ABaseEnemyController"), &Z_Registration_Info_UClass_ABaseEnemyController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABaseEnemyController), 1636843108U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnemyController_h_3703427232(TEXT("/Script/DaniMuerete"),
		Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnemyController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DaniMuerete_Source_DaniMuerete_BaseEnemyController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
