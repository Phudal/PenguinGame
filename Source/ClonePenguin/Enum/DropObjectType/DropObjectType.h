// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropObjectType.generated.h"

// 열거 형식을 선언합니다.
/// - BlueprintType : 블루 프린트에서도 사용 가능하도록 합니다.
/// - 블루 프린트에서 사용 가능한 열거 형식은 
///   언더라잉 타입이 uint8 형식으로 지정되어야 합니다.

UENUM(BlueprintType)
enum class EDropObjectType : uint8
{
	DT_Trash UMETA(DisplayName = Trash),
	DT_Fish UMETA(DisplayName = Fish)
};
// UMETA()
/// - 클래스나 인터페이스, 구조체. 열거 타입, 열거 타입 요소, 함수, 속성 등의
///   동작하는 방식을 제어할 때 사용하는 메타 데이터 지정자입니다.
