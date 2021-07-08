// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"


UCLASS()
class CLONEPENGUIN_API UPlayerCharacterAnimInstance :
	public UAnimInstance
{
	GENERATED_BODY()

protected:
	// 현재 캐릭터 속력
	UPROPERTY(BlueprintReadOnly)
	float VelocityLength;
	/// - BlueprintReadOnly : 블루프린트 클래스에서 읽기 전용으로 사용됨을 나타냅니다.
	/// - BlueprintReadWrite : 블루프린트 클래스에서 읽기 쓰기가 모두 가능한 타입임을 나타냅니다.

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
