// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterMovementHelperComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLONEPENGUIN_API UCharacterMovementHelperComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// 사용할 PlayerCharacter 객체를 나타냄
	UPROPERTY() // PlayerCharacter 의 기본 값(nullptr)을 보장받기 위하여 작성함
	class APlayerCharacter* PlayerCharacter;
	
public:	
	// Sets default values for this component's properties
	UCharacterMovementHelperComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 좌우 이동을 구현함
	void HorizontalMovement();
};
