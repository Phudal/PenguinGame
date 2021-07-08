// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevel.generated.h"

/**
 * 
 */
UCLASS()
class CLONEPENGUIN_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	class USoundWave* S_Game;

public:
	AGameLevel();

protected:
	virtual void BeginPlay() override;
};
