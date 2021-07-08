// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveData.generated.h"

USTRUCT()
struct CLONEPENGUIN_API FSaveData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	float BestScore;

	UPROPERTY()
	int32 Year;
	UPROPERTY()
	int32 Month;
	UPROPERTY()
	int32 Day;
	UPROPERTY()
	int32 Hours;
	UPROPERTY()
	int32 Minutes;
	UPROPERTY()
	int32 Seconds;

public:
	FSaveData();
	
	FSaveData(float bestScore, FDateTime dateTime);

	FORCEINLINE FText GetDateString() const
	{
		return FText::FromString(FString::Printf(TEXT("%d-%d-%d %d:%d:%d"),
			Year, Month, Day, Hours, Minutes, Seconds));
	}

	FORCEINLINE FText GetScoreText() const
	{
		return FText::FromString(FString::Printf(TEXT("%.2f"), BestScore));
	}
};
