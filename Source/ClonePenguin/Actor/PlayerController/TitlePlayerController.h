// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClonePenguin.h"
#include "Actor/PlayerController/BasePlayerController.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLONEPENGUIN_API ATitlePlayerController final :
	public ABasePlayerController
{
	GENERATED_BODY()

private:
	TSubclassOf<class UTitleWidget> BP_Title;

public:
	ATitlePlayerController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
