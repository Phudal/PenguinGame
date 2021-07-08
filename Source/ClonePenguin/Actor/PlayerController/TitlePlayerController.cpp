// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PlayerController/TitlePlayerController.h"

#include "Widget/TitleWidget/TitleWidget.h"

ATitlePlayerController::ATitlePlayerController()
{
	static ConstructorHelpers::FClassFinder<UTitleWidget> BP_TITLE(
		TEXT("WidgetBlueprint'/Game/00_Work/Blueprints/Widget/BP_Title.BP_TITLE_C'"));

	if (BP_TITLE.Succeeded())
		BP_Title = BP_TITLE.Class;
}

void ATitlePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FloatingWidget(BP_Title);
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
