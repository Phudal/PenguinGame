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
	// ������ ���̺� �ּ� DT_DropObjectInfo �� ��Ÿ��
	class UDataTable* DT_DropObjectInfo;

private:
	// ����� ���� Ȯ��
	UPROPERTY(EditAnywhere, meta = (ClampMin = 10.0, ClampMax = 50.0,
		UIMin = 10.0, UIMax = 50.0, AllowPrivateAccess = "true"), Category = "����� ���� Ȯ��")
	float FishDropPercentage;
	/// - meta : ��Ÿ������ �������Դϴ�.
	/// - AllowPrivateAccess = "true" : private ����� �����Ϳ��� ���� �����ϵ��� �մϴ�.
	/// - ClampMin, Max : �ش� �Ӽ��� ������ �� �ִ� �ּ�, �ִ� ���� �����մϴ�.
	/// - UIMin, Max : �����̴��� ���Ͽ� ������ �� �ִ� ���� �ּ�, �ִ� ���� �����մϴ�.

	UPROPERTY(EditAnywhere, Category = "������Ʈ ���� ������", meta = (AllowPrivateAccess = "true"))
	float MinDelay;
	
	UPROPERTY(EditAnywhere, Category = "������Ʈ ���� ������", meta = (AllowPrivateAccess = "true"))
	float MaxDelay;

	// ������Ʈ ���� ������
	float SpawnDelay;

	float SpawnMaxLeftY;
	float SpawnMaxRightY;

	// �����, ������ ������ ������ �迭
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
	// DropObject Actor �� ������Ű�� �޼���
	void SpawnDropObject();

	// ���� �ӵ��� ���� �� ������ ������
	void ChangeDelayFaster(float dt);
};
