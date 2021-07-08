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
	// 현재 점수를 나타냄
	UPROPERTY()
	float CurrentScore;

public:
	virtual void Init() override;

public:
	// 점수를 증가시킴
	void AddScore(float addScore);

	// 최고 점수 갱신을 시도
	void TryUpdateBestScore();

	template<typename T>
	bool LoadJson(FString fileName, T& outResult, FString keyName = FString(TEXT("default")))
	{
		// 파일이 저장된 폴더 경로
		FString folderPath = FPaths::ProjectDir() + TEXT("/Content/00_Work/Resources/Json");

		// 경로가 존재하지 않는다면 로드 실패
		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*folderPath))
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find Paths : %s"), *folderPath);
			return false;
		}

		FString fullPath = folderPath + FString(TEXT("/")) + fileName + FString(TEXT(".json"));

		// 파일을 읽어옴
		FString jsonStr;
		if (!FFileHelper::LoadFileToString(jsonStr, *fullPath))
		{
			// - 만약 파일을 읽지 못했다면 로드 실패
			UE_LOG(LogTemp, Error, TEXT("Can't Read File : %s"), *fullPath);
			return false;
		}

		// Json 파일을 읽을 객체 생성
		TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonStr);

		// Json 오브젝트 생성
		TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

		// 역직렬화하여 원하는 데이터를 얻음
		bool completed = false;
		completed = FJsonSerializer::Deserialize(reader, jsonObj);

		// 역직렬화에 성공했다면
		if (completed)
		{
			// outResult 에 읽은 값을 저장
			FJsonObjectConverter::JsonObjectStringToUStruct(
				jsonObj->GetStringField(keyName), &outResult, 0, 0);
		}

		return completed;
	}

	template<typename T>
	void SaveJson(FString fileName, T& saveData, FString keyName = FString(TEXT("default")))
	{
		// 파일이 저장된 폴더 경로
		FString folderPath = FPaths::ProjectDir() + TEXT("/Content/00_Work/Resources/Json");
		/// - FPaths : 게임, 엔진의 경로 등을 검색하기 위한 기능을 제공하는 클래스
		/// - GameDir() : 게임 경로를 반환합니다.
		
		// 만약 경로가 없다면 경로 생성
		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*folderPath))
			FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*folderPath);

		// 저장할 데이터(saveData)를 문자열로 변환하여 저장함
		FString serializedData;
		FJsonObjectConverter::UStructToJsonObjectString(saveData, serializedData);
		/// - FJsonObjectConverter : Json 객체와 UStruct 간의 변환에 대한 기능을 제공하는 클레스
		/// - UStructToJsonObjectString() : UStruct 에서 Json 문자열로 변환합니다.

		// Json 파일에 입력할 문자열 변수 선언
		FString jsonStr;
		auto jsonObj = TJsonWriterFactory<>::Create(&jsonStr);
		/// - TJsonWriter : Json 파일 쓰기에 대한 내용을 제공하는 클래스

		// Json 오브젝트를 생성
		jsonObj->WriteObjectStart();
		// - Json 의 데이터는 중괄호를 통해 나누어져 있고, 키 : 내용 으로 구분되어 있음.
		// - 이 때 key 는 string, 내용으로는 bool, int, float, string 타입으로 저장될 수 있음.
		// - WriteObjectStart() : 중괄호를 펼쳐 Json 파일의 오브젝트를 나누는 역할을 하며,
		//   최초의 중괄호는 필요하기 때문에 작성되었음.
		// - 데이터 입력이 끝난다면 Close() 메서드를 호출하여 Json 데이터 끝을 알리면 된다.
		// - Json 파일을 저장하기 위해서 파일의 데이터를 담을 string 객체와, 파일 경로를
		//   FFileHelper::SaveStringToFile() 메서드의 인수로 전달하면 된다.

		// 데이터 쓰기
		jsonObj->WriteValue(keyName, serializedData);

		// Json 오브젝트 끝 구분
		jsonObj->WriteObjectEnd();

		// Json 오브젝트 데이터 입력 끝
		jsonObj->Close();

		// 저장할 파일 경로를 저장
		folderPath += FString(TEXT("/")) + fileName + FString(TEXT(".json"));

		// 파일 저장
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
