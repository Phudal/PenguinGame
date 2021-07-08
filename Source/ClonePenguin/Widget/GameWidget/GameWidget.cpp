// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameWidget/GameWidget.h"

#include "Single/GameInstance/ClonePenguinGameInst.h"

#include "Actor/PlayerCharacter/PlayerCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"

void UGameWidget::NativeConstruct()
{	
	Super::NativeConstruct();

	SetGameOverVisibility(false);
}

void UGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	MoveHungryImage();

	UpdateScoreText();
}

void UGameWidget::InitializeGameWidget(ABasePlayerController* playerController)
{
	PlayerController = Cast<AGamePlayerController>(playerController);
}

void UGameWidget::SetGameOverVisibility(bool bVisible, bool bStartTimer)
{
	Overlay_GameOver->SetVisibility(
		bVisible ?
		ESlateVisibility::SelfHitTestInvisible :
		ESlateVisibility::Hidden);

	if(bStartTimer)
	{
		if (GameInst()->bIsGameOver)
			return;

		GameInst()->bIsGameOver = true;

		Cast<UClonePenguinGameInst>(GetWorld()->GetGameInstance())->TryUpdateBestScore();

		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle,
			this, &UGameWidget::ChangeToTitleMap, 3.0f, false);
	}
}

void UGameWidget::MoveHungryImage()
{
	// �÷��̾� ĳ���Ͱ� �������� �ʴ� ��� �޼��� ȣ�� ����
	auto playerCharacter = PlayerController->GetPlayerCharacter();
	if (!IsValid(playerCharacter))
		return;

	// Image_HungryGuage ���� ũ�⸦ ����
	FVector2D gaugeSize = Cast<UCanvasPanelSlot>(Image_HungryGauge->Slot)->GetSize();

	// Imaeg_CurrentGauge �� CanvasPanelSlot�� ����
	auto currentGaugeSlot = Cast<UCanvasPanelSlot>(Image_CurrentGauge->Slot);

	// ������ ��ġ�� �����
	FVector2D newPosition = currentGaugeSlot->GetPosition();
	newPosition.X = (gaugeSize.X * 0.01f) * playerCharacter->GetHungryValue();

	// Image_CurrentGauge �� X ��ġ�� ������
	currentGaugeSlot->SetPosition(newPosition);
}

void UGameWidget::UpdateScoreText()
{
	FString scoreStr = FString::Printf(TEXT("Current Score\n%.2f"), GameInst()->GetCurrentScore());
	// FString scoreStr = FString::Printf(TEXT("Current Score\n%.2f"), 500.0f);

	// FString scoreStr = FString::FromInt(GameInst()->GetCurrentScore());

	Text_Score->SetText(FText::FromString(scoreStr));
}

void UGameWidget::ChangeToTitleMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TitleMap"));
}
