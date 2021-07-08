// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PlayerCharacterAnimInstance.h"

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// �ش� �޼���� �����Ϳ����� ȣ��Ǳ� ������ TryGetPawnOwner() �� nullptr �� ��ȯ�Ѵٸ�
	// ������� �ʵ��� �Ѵ�.
	/// - Editer -> TryGetPawnOwner() �� nullptr �� ��ȯ��
	if (!IsValid(TryGetPawnOwner()))
		return;

	// ������ ���̸� VelocityLength �� ����
	VelocityLength = TryGetPawnOwner()->GetVelocity().Size();
}
