#pragma once

#include "ProyectoVampiro/ProyectoVampiroCharacter.h"
#include "ProyectoVampiro/Components/LifeComponent.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifeBar.generated.h"

UCLASS( Abstract )
class PROYECTOVAMPIRO_API ULifeBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(AProyectoVampiroCharacter* InCharacter) { OwnerCharacter = InCharacter; }
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

	TWeakObjectPtr<AProyectoVampiroCharacter> OwnerCharacter;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* LifeBar;
};
