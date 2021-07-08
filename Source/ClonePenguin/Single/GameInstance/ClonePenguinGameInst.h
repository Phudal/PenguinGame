// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Serialization/JsonWriter.h"
#include "JsonObjectConverter.h"

#include "Struct/SaveData/SaveData.h"

#include "ClonePenguinGameInst.generated.h"

#ifndef GAME_INST_DEF
#define GAME_INST_DEF
#define GameInst() (Cast<UClonePenguinGameInst>(GetGameInstance()))
#endif


UCLASS()
class CLONEPENGUIN_API UClonePenguinGameInst : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bIsGameOver;

private:
	// ���� ������ ��Ÿ��
	UPROPERTY()
	float CurrentScore;

public:
	virtual void Init() override;

public:
	// ������ ������Ŵ
	void AddScore(float addScore);

	// �ְ� ���� ������ �õ�
	void TryUpdateBestScore();

	template<typename T>
	bool LoadJson(FString fileName, T& outResult, FString keyName = FString(TEXT("default")))
	{
		// ������ ����� ���� ���
		FString folderPath = FPaths::ProjectDir() + TEXT("/Content/00_Work/Resources/Json");

		// ��ΰ� �������� �ʴ´ٸ� �ε� ����
		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*folderPath))
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find Paths : %s"), *folderPath);
			return false;
		}

		FString fullPath = folderPath + FString(TEXT("/")) + fileName + FString(TEXT(".json"));

		// ������ �о��
		FString jsonStr;
		if (!FFileHelper::LoadFileToString(jsonStr, *fullPath))
		{
			// - ���� ������ ���� ���ߴٸ� �ε� ����
			UE_LOG(LogTemp, Error, TEXT("Can't Read File : %s"), *fullPath);
			return false;
		}

		// Json ������ ���� ��ü ����
		TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonStr);

		// Json ������Ʈ ����
		TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

		// ������ȭ�Ͽ� ���ϴ� �����͸� ����
		bool completed = false;
		completed = FJsonSerializer::Deserialize(reader, jsonObj);

		// ������ȭ�� �����ߴٸ�
		if (completed)
		{
			// outResult �� ���� ���� ����
			FJsonObjectConverter::JsonObjectStringToUStruct(
				jsonObj->GetStringField(keyName), &outResult, 0, 0);
		}

		return completed;
	}

	template<typename T>
	void SaveJson(FString fileName, T& saveData, FString keyName = FString(TEXT("default")))
	{
		// ������ ����� ���� ���
		FString folderPath = FPaths::ProjectDir() + TEXT("/Content/00_Work/Resources/Json");
		/// - FPaths : ����, ������ ��� ���� �˻��ϱ� ���� ����� �����ϴ� Ŭ����
		/// - GameDir() : ���� ��θ� ��ȯ�մϴ�.
		
		// ���� ��ΰ� ���ٸ� ��� ����
		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*folderPath))
			FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*folderPath);

		// ������ ������(saveData)�� ���ڿ��� ��ȯ�Ͽ� ������
		FString serializedData;
		FJsonObjectConverter::UStructToJsonObjectString(saveData, serializedData);
		/// - FJsonObjectConverter : Json ��ü�� UStruct ���� ��ȯ�� ���� ����� �����ϴ� Ŭ����
		/// - UStructToJsonObjectString() : UStruct ���� Json ���ڿ��� ��ȯ�մϴ�.

		// Json ���Ͽ� �Է��� ���ڿ� ���� ����
		FString jsonStr;
		auto jsonObj = TJsonWriterFactory<>::Create(&jsonStr);
		/// - TJsonWriter : Json ���� ���⿡ ���� ������ �����ϴ� Ŭ����

		// Json ������Ʈ�� ����
		jsonObj->WriteObjectStart();
		// - Json �� �����ʹ� �߰�ȣ�� ���� �������� �ְ�, Ű : ���� ���� ���еǾ� ����.
		// - �� �� key �� string, �������δ� bool, int, float, string Ÿ������ ����� �� ����.
		// - WriteObjectStart() : �߰�ȣ�� ���� Json ������ ������Ʈ�� ������ ������ �ϸ�,
		//   ������ �߰�ȣ�� �ʿ��ϱ� ������ �ۼ��Ǿ���.
		// - ������ �Է��� �����ٸ� Close() �޼��带 ȣ���Ͽ� Json ������ ���� �˸��� �ȴ�.
		// - Json ������ �����ϱ� ���ؼ� ������ �����͸� ���� string ��ü��, ���� ��θ�
		//   FFileHelper::SaveStringToFile() �޼����� �μ��� �����ϸ� �ȴ�.

		// ������ ����
		jsonObj->WriteValue(keyName, serializedData);

		// Json ������Ʈ �� ����
		jsonObj->WriteObjectEnd();

		// Json ������Ʈ ������ �Է� ��
		jsonObj->Close();

		// ������ ���� ��θ� ����
		folderPath += FString(TEXT("/")) + fileName + FString(TEXT(".json"));

		// ���� ����
		FFileHelper::SaveStringToFile(*jsonStr, *folderPath);
	}
	
public:
	FORCEINLINE float GetCurrentScore() const
	{
		return CurrentScore;
	}

	FORCEINLINE void ResetCurrentScore()
	{
		CurrentScore = 0.0f;
	}
	
	bool GetSaveData(FSaveData& outSaveData);
};