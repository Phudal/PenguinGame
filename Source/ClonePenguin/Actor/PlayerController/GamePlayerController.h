// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Actor/PlayerController/BasePlayerController.h"
#include "GamePlayerController.generated.h"



UCLASS()
class CLONEPENGUIN_API AGamePlayerController :
	public ABasePlayerController
{
	GENERATED_BODY()

private:
	// BP_Game Widget 클래스를 나타냄
	TSubclassOf<class UUserWidget> BP_Game;

private:
	// 조종당하는 PlayerCharacter Pawn을 나타냄
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public:
	AGamePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

	// 폰에 빙의될 떄 호출되는 메서드
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	void RotateController();
	
	
public:
	FORCEINLINE class APlayerCharacter* GetPlayerCharacter() const
	{
		return PlayerCharacter;
	}
};
