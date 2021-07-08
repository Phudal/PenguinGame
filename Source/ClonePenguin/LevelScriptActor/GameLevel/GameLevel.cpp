// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptActor/GameLevel/GameLevel.h"

#include "Kismet/GameplayStatics.h"


AGameLevel::AGameLevel()
{
	static ConstructorHelpers::FObjectFinder<USoundWave> S_GAME(
		TEXT("SoundWave'/Game/00_Work/Resources/Audio/game.game'"));

	if (S_GAME.Succeeded())
		S_Game = S_GAME.Object;
}

void AGameLevel::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(
		GetWorld(),
		S_Game, 0.3f);
}
