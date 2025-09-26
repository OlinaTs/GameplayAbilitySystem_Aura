// Copyright Mazi Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircle.generated.h"

UCLASS()
class AURA_API AMagicCircle : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicCircle();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	/* A material that is rendered onto the surface of a mesh. A kind of 'bumper sticker' for a model. */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDecalComponent> MagicCircleDecal;
};
