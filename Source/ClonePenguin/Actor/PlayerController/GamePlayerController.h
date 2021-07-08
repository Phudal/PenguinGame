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
	// BP_Game Widget Ŭ������ ��Ÿ��
	TSubclassOf<class UUserWidget> BP_Game;

private:
	// �������ϴ� PlayerCharacter Pawn�� ��Ÿ��
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public:
	AGamePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

	// ���� ���ǵ� �� ȣ��Ǵ� �޼���
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
