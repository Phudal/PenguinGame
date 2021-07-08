// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TitleGameMode/TitleGameMode.h"

#include "Actor/PlayerController/TitlePlayerController.h"

ATitleGameMode::ATitleGameMode()
{
	PlayerControllerClass = ATitlePlayerController::StaticClass();
}
