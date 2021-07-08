// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnDropObjectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLONEPENGUIN_API USpawnDropObjectComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// 데이터 테이블 애셋 DT_DropObjectInfo 을 나타냄
	class UDataTable* DT_DropObjectInfo;

private:
	// 물고기 생성 확률
	UPROPERTY(EditAnywhere, meta = (ClampMin = 10.0, ClampMax = 50.0,
		UIMin = 10.0, UIMax = 50.0, AllowPrivateAccess = "true"), Category = "물고기 생성 확률")
	float FishDropPercentage;
	/// - meta : 메타데이터 지정자입니다.
	/// - AllowPrivateAccess = "true" : private 멤버를 에디터에서 접근 가능하도록 합니다.
	/// - ClampMin, Max : 해당 속성에 설정될 수 있는 최소, 최대 값을 지정합니다.
	/// - UIMin, Max : 슬라이더를 통하여 설정될 수 있는 값의 최소, 최대 값을 지정합니다.

	UPROPERTY(EditAnywhere, Category = "오브젝트 생성 딜레이", meta = (AllowPrivateAccess = "true"))
	float MinDelay;
	
	UPROPERTY(EditAnywhere, Category = "오브젝트 생성 딜레이", meta = (AllowPrivateAccess = "true"))
	float MaxDelay;

	// 오브젝트 생성 딜레이
	float SpawnDelay;

	float SpawnMaxLeftY;
	float SpawnMaxRightY;

	// 물고기, 쓰레기 정보를 저장할 배열
	TArray<struct FDropObjectInfo*> FishObjInfos;
	TArray<struct FDropObjectInfo*> TrashObjInfos;
	
public:	
	// Sets default values for this component's properties
	USpawnDropObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(
		float DeltaTime, 
		ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	// DropObject Actor 를 스폰시키는 메서드
	void SpawnDropObject();

	// 생성 속도를 점점 더 빠르게 변경함
	void ChangeDelayFaster(float dt);
};
