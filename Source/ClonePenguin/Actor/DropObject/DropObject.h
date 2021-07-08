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
	// 떨어지는 속력
	float FallDownSpeed;

	// 플레이어에게 가할 데미지 / 회복할 체력
	float ChangeHungryValue;

	// 오브젝트의 타입을 나타냄
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
	// 떨어지는 움직임을 수행합니다.
	void FallDown(float dt);

public:
	// DropObject 를 초기화
	void InitializeDropObject(float fallDownSpeed,
		struct FDropObjectInfo* dropObjInfo);

private:
	UFUNCTION()	// Dynamic Delegate에 바인딩될 메서드이므로 작성함
		void AddDamage(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	/// - OverlappedComponent : 겹친 자신의 컴포넌트가 전달됩니다.
	/// - OtherActor : 겹친 상대 액터가 전달됩니다.
	/// - OtherComp : 겹친 상대 컴포넌트가 전달됩니다.
	/// - OtherBodyIndex : bMultibodyOverlap 이 true 일 경우
	///   여러 컬리전과 겹쳤을 경우 컬리전들을 구분하기 위한번호
	/// - bFromSweep : 액터가 이동할 때 Sweep 이벤트를 발생시키도록 하여 발생한
	///   발생한 이벤트인지를 나타냅니다.
	/// - SweepResult : Sweep 이벤트 발생 시 
	///   자세한 결과를 담고 있는 데이터가 전달됩니다.
};
