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

	// �¿� �̵�
	HorizontalMovement();
}

void UCharacterMovementHelperComponent::HorizontalMovement()
{
	// PlayerCharacter �� nullptr ���
	if (!IsValid(PlayerCharacter))
	{
		// PlayerCharacter ���͸� ����
		PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
		/// - Cast<T>(instance) : instance �� T �������� ĳ�����մϴ�.
		///   ĳ���ÿ� ������ ��� nullptr �� ��ȯ�մϴ�.
		/// - GetOwner() : ������Ʈ�� �����ϴ� Actor �� ��ȯ�մϴ�.		
	}
	
	// �̵��� ������ ������
	FVector moveDirection = PlayerCharacter->GetHorizontalInputValue() *
		FVector::RightVector;

	// ĳ���͸� �̵�
	PlayerCharacter->AddMovementInput(moveDirection);
}

