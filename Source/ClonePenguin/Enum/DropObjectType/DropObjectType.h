// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropObjectType.generated.h"

// ���� ������ �����մϴ�.
/// - BlueprintType : ��� ����Ʈ������ ��� �����ϵ��� �մϴ�.
/// - ��� ����Ʈ���� ��� ������ ���� ������ 
///   ������� Ÿ���� uint8 �������� �����Ǿ�� �մϴ�.

UENUM(BlueprintType)
enum class EDropObjectType : uint8
{
	DT_Trash UMETA(DisplayName = Trash),
	DT_Fish UMETA(DisplayName = Fish)
};
// UMETA()
/// - Ŭ������ �������̽�, ����ü. ���� Ÿ��, ���� Ÿ�� ���, �Լ�, �Ӽ� ����
///   �����ϴ� ����� ������ �� ����ϴ� ��Ÿ ������ �������Դϴ�.
