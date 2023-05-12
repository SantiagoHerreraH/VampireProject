#include "ProyectoVampiro/Widgets/LifeBar.h"

#include <Components/ProgressBar.h>

void ULifeBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerCharacter.IsValid())
		return;

	LifeBar->SetPercent(OwnerCharacter->GetCurrentLife() / OwnerCharacter->GetMaxLife());
}
