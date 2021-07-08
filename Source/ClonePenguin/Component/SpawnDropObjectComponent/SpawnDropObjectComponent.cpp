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

	// DataTable ���� ���� �̸����� ����
	for (FName rowName : DT_DropObjectInfo->GetRowNames())
	{
		// FindRow �޼��带 �̿��Ͽ� ���� ã�� ��, ������ ���� ���
		// ���� ������ �˸� ���ڿ� ������ ����
		FString contextString;

		// DataTable ���� �̸��� �̿��Ͽ� ���� ã��
		auto info = DT_DropObjectInfo->FindRow<FDropObjectInfo>(rowName, contextString);

		//if (info->DropObjectType == EDropObjectType::DT_Fish)
		//	FishObjInfos.Add(info);
		//else TrashObjInfos.Add(info);

		// ������ �߰��� �迭�� ���� ������
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
	// ������ DropObject �� Ÿ���� fishDropPer �� ���� ��ȯ�ϴ� �Լ�
	Func(EDropObjectType, fnGetRandomDropType, (float)) = [](float fishDropPer)
	{
		return (FMath::FRandRange(1.0f, 100.0f) <= fishDropPer) ?
			EDropObjectType::DT_Fish : EDropObjectType::DT_Trash;
	};

	// dropObjectType �� ���� ������ DropObject ������ ����
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
		/// - TArrayInstance.Num() : �迭�� ��� ������ ��ȯ�մϴ�.
	};
#pragma endregion

	// ������ DropObj �� Ÿ���� ����
	EDropObjectType dropObjType = fnGetRandomDropType(FishDropPercentage);

	// ������ DropObj �� ������ ����
	FDropObjectInfo* dropObjInfo = fnGetRandomDropObjInfo(
		dropObjType, &FishObjInfos, &TrashObjInfos);

	FVector spawnLocation =
		GetOwner()->GetActorLocation() +
		(FMath::FRandRange(SpawnMaxRightY, SpawnMaxLeftY) * FVector::RightVector);

	// DropObject ���͸� ����
	ADropObject* newDropObject = GetWorld()->SpawnActor<ADropObject>(
		spawnLocation,
		FRotator::ZeroRotator);
	/// - SpawnActor<T>(FVector location, FRotator rotation) : T ������ ���͸�
	///   location ��ġ�� �����ϰ� rotation ȸ�������� �����մϴ�.

	// TODO
	// DropObject �ʱ�ȭ
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

	// Ÿ�̸� : ������ �ð����� Ư���� ������ �����ϴ� ���
	/// - Ÿ�̸Ӱ� ������ �ൿ�� �Լ� ���� : void()
}

void USpawnDropObjectComponent::ChangeDelayFaster(float dt)
{
	if (SpawnDelay > MaxDelay)
		SpawnDelay -= dt * 0.05f;

	else
		SpawnDelay = MaxDelay;
}

