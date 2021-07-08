// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "CoreMinimal.h"

#include "EngineMinimal.h"


#ifndef FN_PTR_DEFINE
#define FN_PTR_DEFINE

#define Action(fnPtrName, ParamTypes) void(*fnPtrName)ParamTypes
#define Func(RetType, fnPtrName, ParamTypes) RetType(*fnPtrName)ParamTypes
#endif

// Func(void, MyFunction, (int param1, float param2))
// RetType = void
// fnPtrName = MyFunction
// ParamTypes = (int param1, float param2)
// void (MyFunction)(int param1, float param2) == void (MyFunction)(int, float)
// �Լ�������


// #define Func(fnPtrName, ParamTypes, ...) auto fnPtrName = [##__VA_ARGS__]ParamTypes
// Func(MyFunction, (int a, int b), this, myVariable1, . myVariable2)
// {
// 	return a + b + myVariable1 + myVariable2;
// }
// 
// ==
// 
// 
// int(*MyFunction)(int, int) = [this, myVariable1, myVariable2](int a, int b)
// { return a + b + myVariable1 + myVariable2; }


// Unreal Script
// ���÷��� �ý���(Property System) �� �����մϴ�.
// ���÷���
// ��Ÿ���� �ڽ��� ������ �� �ִ� ���
// ��ũ�� �Լ� �������� �����Ǿ� �ֽ��ϴ�.
/// - ��ũ�� ����
///   - UENUM(), UCLASS(), USTRUCT(), UFUNCTION(), UPROPERTY()
//  ����� Property System �� �����ϴ� �������� ��ŷ ��Ű�� ���
/// - "fileName.generated.h" �� ���Խ�ŵ�ϴ�.
/// - ���� ���� ���ϴܿ� �ۼ��մϴ�.
// Unreal GC System
/// - UObject �������� �� �̻� �ʿ� ������ ��ü�� �ڵ����� �����մϴ�.

// UObject : �𸮾� ������Ʈ
/// - �𸮾� ������ ������ �޴� ��ü�� �ǹ��մϴ�.
/// - UHT : �� ������ �޾ƾ� UObject �� ������ �� ����!
/// - UObject �԰ݿ� �°� �ۼ��Ͽ� UHT ������ �޴� ���
///		- "fileName.generated.h" �� ���Խ�ŵ�ϴ�.
///     - ��ũ�� �ۼ� (ex : UCLASS())
///		- UObject ���λ� �ۼ� (ex : U, A, F, I, E)
///     - UObject �� ������� �δ� Ŭ������ ��ӹ޽��ϴ�.
///     - GENERATED_BODY() / GENERATED_USTRUCT_BODY()

// Unreal �� �ǰ��ϴ� ������ ������ �� ����ϴ� �ڷ���
/// - ���� : �ھ� ������ ������ ����մϴ�.
/// - int8  : __int8
/// - int16 : __int16
/// - int32 : __int32
/// - int64 : __int64
/// - uint8  : unsigned __int8
/// - uint16 : unsigned __int16
/// - uint32 : unsigned __int32
/// - uint64 : unsigned __int64
///
/// - ����
/// - TCHAR - char / wchar_t
///
/// - ���ڿ�
/// - FString : �Ϲ����� ���ڿ��� ������ �� �ִ� Ÿ��
/// - FName : ��� ��ü�� �̸��� ���Ǵ� ����
///   - ��ҹ��ڸ� �������� �ʽ��ϴ�.
///   - IsNone() �� ���� �� ���ڿ����� Ȯ���մϴ�.
/// - FText : ����ȭ ���� �ؽ�Ʈ�� ���Ǵ� Ÿ��
///   - ���� UI �� ǥ�õǴ� ���ڿ��� ���Ǹ�,
///     �ٸ� ����ڿ��� �ٸ� ���� ������ �� �ֵ��� �մϴ�.

// ���ڿ� ��ȯ
/// - FName to FString : FNameInst.ToString()
/// - FName to FText   : FText::FromName(FNameInst)		(��ȯ �� �ڵ� ����ȭ�� ���� ���� �� ����.)
///
/// - FString to FName : FName(*FStringInst)			(��ȯ �� ��ҹ��ڸ� �������� �ʰ� ��.)
/// - FString to FText : FText::FromString(FStringInst)	(��ȯ �� �ڵ� ����ȭ�� ���� ���� �� ����.)
///
/// - FText to FString : FTextInst.ToString()			(�Ϻ� ���� ���������� ��ȯ���� ���� �� ����.)
/// - FText to FName   : FName(*FTextInst.ToString())	(�Ϻ� ���� ���������� ��ȯ���� ���� �� ����.)
///														(��ȯ �� ��ҹ��ڸ� �������� �ʰ� ��.)

// �𸮾� �۸� ��Ģ
/// - �Ľ�Į, �밡����



