// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClonePenguin.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
/// - �ش� Ŭ������ UObject ���� ����
class CLONEPENGUIN_API APlayerCharacter final
	: public ACharacter
{
	/// - U : UObject ������ Ŭ������ ���˴ϴ�.
	/// - A : Actor Ŭ������ ��ӹ޴� Ŭ������ ���˴ϴ�.
	/// - F : �Ϲ� Ŭ������ ����ü�� ���˴ϴ�.
	/// - I : �������̽� Ŭ������ ���˴ϴ�.
	///       �������̽� Ŭ������ U �� �Բ� ���˴ϴ�.
	/// - E : ���� ���Ŀ� ���˴ϴ�.
	
	GENERATED_BODY()
	/// - �׻� Ŭ���� ù �ٿ� �ۼ��Ǿ�� ��
	
private:
	// ���� �Է� ���� ��Ÿ��
	float HorizontalInputValue;

	// ����� �Է� ���� ��Ÿ��
	float HungryValue;

	// ���ǵ� �÷��̾� ��Ʈ�ѷ� ��ü�� ��Ÿ��
	class AGamePlayerController* GamePlayerController;

protected:
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementHelperComponent* MovementHelper;
	/// - VisibleAnywhere : �� �ʵ尡 ��� ������ ǥ�õǵ��� �մϴ�.
	/// - EditAnywhere : �� �ʵ带 ��� ������ ���� ������ �� �ֵ��� �մϴ�.

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	// ������Ʈ ���� -> �Է¿� ������ Ű �Է� �̺�Ʈ�� ���� ����մϴ�.
	/// - UInputComponent : ���Ϳ� �Է� �̺�Ʈ�� ����ϴ� ����� �����ϴ� ������Ʈ�Դϴ�.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// A, D, <, > Ű�� ���ε� ��ų �޼���
	void InputHorizontal(float axis);

public:
	void AddHungryValue(float addValue);
	
private:
	UFUNCTION()
	void OnHit(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamagedCauser);
		
public:
	// HorizontalInputValue ���� ��ȯ
	FORCEINLINE float GetHorizontalInputValue() const
	{
		return HorizontalInputValue;
	}

	FORCEINLINE float GetHungryValue() const
	{
		return HungryValue;
	}
};
