// Fill out your copyright notice in the Description page of Project Settings.


#include "Single/GameInstance/ClonePenguinGameInst.h"

void UClonePenguinGameInst::Init()
{
	Super::Init();

	TryUpdateBestScore();
}

void UClonePenguinGameInst::AddScore(float addScore)
{
	if (bIsGameOver)
		return;

	CurrentScore += addScore;

	CurrentScore = (CurrentScore < 0.0f) ? 0.0f : CurrentScore;
}

void UClonePenguinGameInst::TryUpdateBestScore()
{
	FSaveData saveData;
	GetSaveData(saveData);

	if (CurrentScore > saveData.BestScore)
	{
		FSaveData bestData(CurrentScore, FDateTime::Now());
		SaveJson(TEXT("BestData"), bestData);
	}	
}

bool UClonePenguinGameInst::GetSaveData(FSaveData& outSaveData)
{
	// 로드 결과를 저장함
	bool res = LoadJson(TEXT("BestData"), outSaveData);

	return res;
}
