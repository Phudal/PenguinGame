// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpawnDropObjectComponent/SpawnDropObjectComponent.h"

#include "Actor/DropObject/DropObject.h"
#include "Actor/PlayerCharacter/PlayerCharacter.h"
#include "Engine/DataTable.h"
#include "Struct/DropObjectInfo/DropObjectInfo.h"

// Sets default values for this component's properties
USpawnDropObjectComponent::USpawnDropObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DROP_OBJECT_INFO(
		TEXT("DataTable'/Game/00_Work/DataTables/DT_DropObjectInfo.DT_DropObjectInfo'"));

	if (DT_DROP_OBJECT_INFO.Succeeded())
		DT_DropObjectInfo = DT_DROP_OBJECT_INFO.Object;

	MinDelay = 1.0f;
	MaxDelay = 0.02f;

	SpawnMaxLeftY = 981.0f;
	SpawnMaxRightY = -815.9f;
}


// Called when the game starts
void USpawnDropObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = MinDelay;

	// DataTable 에서 행의 이름들을 얻음
	for (FName rowName : DT_DropObjectInfo->GetRowNames())
	{
		// FindRow 메서드를 이용하여 행을 찾을 때, 문제가 생길 경우
		// 문제 내용을 알릴 문자열 변수를 선언
		FString contextString;

		// DataTable 에서 이름을 이용하여 행을 찾음
		auto info = DT_DropObjectInfo->FindRow<FDropObjectInfo>(rowName, contextString);

		//if (info->DropObjectType == EDropObjectType::DT_Fish)
		//	FishObjInfos.Add(info);
		//else TrashObjInfos.Add(info);

		// 내용을 추가할 배열에 대한 참조자
		TArray<FDropObjectInfo*>& targetArray =
			(info->DropObjectType == EDropObjectType::DT_Fish) ?
			FishObjInfos : TrashObjInfos;

		targetArray.Add(info);
	}

	SpawnDropObject();
}


// Called every frame
void USpawnDropObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ChangeDelayFaster(DeltaTime);
}

void USpawnDropObjectComponent::SpawnDropObject()
{
#pragma region Functions
	// 생성할 DropObject 의 타입을 fishDropPer 에 따라 반환하는 함수
	Func(EDropObjectType, fnGetRandomDropType, (float)) = [](float fishDropPer)
	{
		return (FMath::FRandRange(1.0f, 100.0f) <= fishDropPer) ?
			EDropObjectType::DT_Fish : EDropObjectType::DT_Trash;
	};

	// dropObjectType 에 따라 랜덤한 DropObject 정보를 얻음
	Func(FDropObjectInfo*,
		fnGetRandomDropObjInfo,
		(EDropObjectType, const TArray<FDropObjectInfo*>*, const TArray<FDropObjectInfo*>*)) =
		[](EDropObjectType dropObjType,
			const TArray<FDropObjectInfo*>* fishObjInfos,
			const TArray<FDropObjectInfo*>* trashObjInfos)
	{
		const TArray<FDropObjectInfo*>* dropObjInfo = (dropObjType == EDropObjectType::DT_Fish) ?
			fishObjInfos : trashObjInfos;

		return ((*dropObjInfo)[FMath::RandRange(0, dropObjInfo->Num() - 1)]);		
		/// - TArrayInstance.Num() : 배열의 요소 개수를 반환합니다.
	};
#pragma endregion

	// 생성할 DropObj 의 타입을 저장
	EDropObjectType dropObjType = fnGetRandomDropType(FishDropPercentage);

	// 랜덤한 DropObj 의 정보를 얻음
	FDropObjectInfo* dropObjInfo = fnGetRandomDropObjInfo(
		dropObjType, &FishObjInfos, &TrashObjInfos);

	FVector spawnLocation =
		GetOwner()->GetActorLocation() +
		(FMath::FRandRange(SpawnMaxRightY, SpawnMaxLeftY) * FVector::RightVector);

	// DropObject 액터를 생성
	ADropObject* newDropObject = GetWorld()->SpawnActor<ADropObject>(
		spawnLocation,
		FRotator::ZeroRotator);
	/// - SpawnActor<T>(FVector location, FRotator rotation) : T 형식의 액터를
	///   location 위치에 생성하고 rotation 회전값으로 설정합니다.

	// TODO
	// DropObject 초기화
	newDropObject->InitializeDropObject(
		300.0f + (300.0f * (MinDelay - SpawnDelay)),
		dropObjInfo);

	FTimerHandle hSpawnDropObjTimer;
	GetWorld()->GetTimerManager().SetTimer(
		hSpawnDropObjTimer,
		this,
		&USpawnDropObjectComponent::SpawnDropObject,
		SpawnDelay,
		false);

	// 타이머 : 정의한 시간마다 특정한 동작을 수행하는 기능
	/// - 타이머가 수행할 행동의 함수 형태 : void()
}

void USpawnDropObjectComponent::ChangeDelayFaster(float dt)
{
	if (SpawnDelay > MaxDelay)
		SpawnDelay -= dt * 0.05f;

	else
		SpawnDelay = MaxDelay;
}

