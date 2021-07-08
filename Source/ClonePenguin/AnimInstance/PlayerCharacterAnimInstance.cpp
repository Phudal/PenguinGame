// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PlayerCharacterAnimInstance.h"

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 해당 메서드는 에디터에서도 호출되기 때문에 TryGetPawnOwner() 이 nullptr 를 반환한다면
	// 실행되지 않도록 한다.
	/// - Editer -> TryGetPawnOwner() 는 nullptr 를 반환함
	if (!IsValid(TryGetPawnOwner()))
		return;

	// 벡터의 길이를 VelocityLength 에 저장
	VelocityLength = TryGetPawnOwner()->GetVelocity().Size();
}
