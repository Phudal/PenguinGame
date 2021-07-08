// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/DropObjectType/DropObjectType.h"

#include "DropObjectInfo.generated.h"

// 해당 구조체 타입에 대해 리플렉션 시스템을 지원하도록 합니다.
/// - BlueprintType : 블루 프린트에서도 사용 가능하도록 합니다.
USTRUCT(BlueprintType)
struct CLONEPENGUIN_API FDropObjectInfo
: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	// - 구조체의 경우 GENERATED_USTRUCT_BODY() 를 작성합니다.

public:
	// 오브젝트 타입 정의
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	EDropObjectType DropObjectType;

	// 떨어지는 오브젝트에 사용될 Static Mesh 에셋을 나타냄
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	class UStaticMesh* DropObjectStaticMesh;

	// 겹쳤을 때 변경할 배고픔 게이지 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "변경 값")
	float ChangeHungryValue;
};
