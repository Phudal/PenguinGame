// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CharacterMovementHelperComponent/CharacterMovementHelperComponent.h"

#include "Actor/PlayerCharacter/PlayerCharacter.h"

// Sets default values for this component's properties
UCharacterMovementHelperComponent::UCharacterMovementHelperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UCharacterMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCharacterMovementHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 좌우 이동
	HorizontalMovement();
}

void UCharacterMovementHelperComponent::HorizontalMovement()
{
	// PlayerCharacter 가 nullptr 라면
	if (!IsValid(PlayerCharacter))
	{
		// PlayerCharacter 액터를 얻음
		PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
		/// - Cast<T>(instance) : instance 를 T 형식으로 캐스팅합니다.
		///   캐스팅에 실패한 경우 nullptr 를 반환합니다.
		/// - GetOwner() : 컴포넌트를 소유하는 Actor 를 반환합니다.		
	}
	
	// 이동할 방향을 저장함
	FVector moveDirection = PlayerCharacter->GetHorizontalInputValue() *
		FVector::RightVector;

	// 캐릭터를 이동
	PlayerCharacter->AddMovementInput(moveDirection);
}

