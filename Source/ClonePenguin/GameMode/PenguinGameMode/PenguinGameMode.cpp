// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PenguinGameMode/PenguinGameMode.h"

#include "Actor/PlayerCharacter/PlayerCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

APenguinGameMode::APenguinGameMode()
{
	/*

	static ConstructorHelpers::FClassFinder<APlayerCharacter> BP_PLAYER_CHARACTER(
		TEXT("Blueprint'/Game/Blueprints/Actor/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	/// - ConstructorHelpers : 생성자에서 Resource 나 Blueprint Class 를 불러오는 작업을
	///   도와주는 기능을 제공하는 클래스
	/// - ConstructorHelpers::FClassFinder : UClass 를 가져올 때 사용하는 타입
	///   - 경로 뒤에 _C 를 작성합니다.
	/// - ConstructorHelpers::FObjectFinder : UClass 를 제외한 애셋을 가져올 때 사용하는 타입

	// 해당 애셋을 성공적으로 로드했다면
	if (BP_PLAYER_CHARACTER.Succeeded())
		DefaultPawnClass = BP_PLAYER_CHARACTER.Class;
	/// - ClassName::StaticClass() : 생성된 C++ 클래스의 UClass 를 반환합니다.
	// TSubclassOf : UClass 타입의 안전성을 보장해주는 클래스이며,
	// UClass 의 선택지를 제한시킬 때 사용합니다.

	*/
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AGamePlayerController::StaticClass();

	//PlayerControllerClass;

}