// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClonePenguin.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

// �ش� Ŭ������ �߻� Ŭ������ ������
UCLASS(Abstract)
class CLONEPENGUIN_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UUserWidget* Widget;

public:
	ABasePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// ���� ���ǵ� �� ȣ��Ǵ� �޼���
	virtual void OnPossess(APawn* InPawn) override;

protected:
	// ������ ���
	/// - widgetClass : ��� ������ UClass �� ������
	class UUserWidget* FloatingWidget(TSubclassOf<class UUserWidget> widgetClass);

private:
	// ī�޶� �並 ������
	void SetCameraView();

public:
	// ��� ���� ��ü�� ����
	FORCEINLINE class UUserWidget* GetWidget() const
	{
		return Widget;
	}
};
