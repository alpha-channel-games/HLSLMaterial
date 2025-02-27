// Copyright 2021 Phyronnaz

#include "CoreMinimal.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_Base.h"
#include "Modules/ModuleInterface.h"
#include "HLSLMaterialFunctionLibrary.h"

class FAssetTypeActions_HLSLMaterialFunctionLibrary : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_HLSLMaterialFunctionLibrary() = default;

	//~ Begin IAssetTypeActions Interface
	virtual FText GetName() const override { return INVTEXT("HLSL Material Function Library"); }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::MaterialsAndTextures; }
	virtual FColor GetTypeColor() const override { return FColor(0, 175, 255); }
	virtual UClass* GetSupportedClass() const override { return UHLSLMaterialFunctionLibrary::StaticClass(); }

	virtual bool HasActions(const TArray<UObject*>&InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>&InObjects, FMenuBuilder & MenuBuilder) override
	{
		MenuBuilder.AddMenuEntry(
			INVTEXT("Update from HLSL"),
			INVTEXT("Update all the generated material functions from the HLSL code"),
			{},
			FUIAction(FExecuteAction::CreateLambda([this, Assets = GetTypedWeakObjectPtrs<UHLSLMaterialFunctionLibrary>(InObjects)]()
		{
			for (const TWeakObjectPtr<UHLSLMaterialFunctionLibrary>& Asset : Assets)
			{
				if (ensure(Asset.IsValid()))
				{
					Asset->Update();
				}
			}
		})));
	}
	//~ End IAssetTypeActions Interface
};

class FHLSLMaterialEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.RegisterAssetTypeActions(MakeShared<FAssetTypeActions_HLSLMaterialFunctionLibrary>());
	}
};
IMPLEMENT_MODULE(FHLSLMaterialEditorModule, HLSLMaterialEditor);