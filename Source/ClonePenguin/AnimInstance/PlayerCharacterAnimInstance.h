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
	// ���� ĳ���� �ӷ�
	UPROPERTY(BlueprintReadOnly)
	float VelocityLength;
	/// - BlueprintReadOnly : �������Ʈ Ŭ�������� �б� �������� ������ ��Ÿ���ϴ�.
	/// - BlueprintReadWrite : �������Ʈ Ŭ�������� �б� ���Ⱑ ��� ������ Ÿ������ ��Ÿ���ϴ�.

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
