// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClonePenguin.h"
#include "GameFramework/Actor.h"
#include "Enum/DropObjectType/DropObjectType.h"

#include "DropObject.generated.h"

UCLASS()
class CLONEPENGUIN_API ADropObject final :
	public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DropObjectMesh;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* RotatingMovement;

private:
	// �������� �ӷ�
	float FallDownSpeed;

	// �÷��̾�� ���� ������ / ȸ���� ü��
	float ChangeHungryValue;

	// ������Ʈ�� Ÿ���� ��Ÿ��
	EDropObjectType DropObjectType;
	
public:	
	// Sets default values for this actor's properties
	ADropObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// �������� �������� �����մϴ�.
	void FallDown(float dt);

public:
	// DropObject �� �ʱ�ȭ
	void InitializeDropObject(float fallDownSpeed,
		struct FDropObjectInfo* dropObjInfo);

private:
	UFUNCTION()	// Dynamic Delegate�� ���ε��� �޼����̹Ƿ� �ۼ���
		void AddDamage(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	/// - OverlappedComponent : ��ģ �ڽ��� ������Ʈ�� ���޵˴ϴ�.
	/// - OtherActor : ��ģ ��� ���Ͱ� ���޵˴ϴ�.
	/// - OtherComp : ��ģ ��� ������Ʈ�� ���޵˴ϴ�.
	/// - OtherBodyIndex : bMultibodyOverlap �� true �� ���
	///   ���� �ø����� ������ ��� �ø������� �����ϱ� ���ѹ�ȣ
	/// - bFromSweep : ���Ͱ� �̵��� �� Sweep �̺�Ʈ�� �߻���Ű���� �Ͽ� �߻���
	///   �߻��� �̺�Ʈ������ ��Ÿ���ϴ�.
	/// - SweepResult : Sweep �̺�Ʈ �߻� �� 
	///   �ڼ��� ����� ��� �ִ� �����Ͱ� ���޵˴ϴ�.
};
