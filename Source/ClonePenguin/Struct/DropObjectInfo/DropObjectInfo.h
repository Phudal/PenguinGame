// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/DropObjectType/DropObjectType.h"

#include "DropObjectInfo.generated.h"

// �ش� ����ü Ÿ�Կ� ���� ���÷��� �ý����� �����ϵ��� �մϴ�.
/// - BlueprintType : ��� ����Ʈ������ ��� �����ϵ��� �մϴ�.
USTRUCT(BlueprintType)
struct CLONEPENGUIN_API FDropObjectInfo
: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	// - ����ü�� ��� GENERATED_USTRUCT_BODY() �� �ۼ��մϴ�.

public:
	// ������Ʈ Ÿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	EDropObjectType DropObjectType;

	// �������� ������Ʈ�� ���� Static Mesh ������ ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	class UStaticMesh* DropObjectStaticMesh;

	// ������ �� ������ ����� ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "���� ��")
	float ChangeHungryValue;
};
