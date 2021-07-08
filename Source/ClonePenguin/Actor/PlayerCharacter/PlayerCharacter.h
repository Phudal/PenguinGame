// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClonePenguin.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
/// - 해당 클래스가 UObject 임을 선언
class CLONEPENGUIN_API APlayerCharacter final
	: public ACharacter
{
	/// - U : UObject 형태의 클래스에 사용됩니다.
	/// - A : Actor 클래스를 상속받는 클래스에 사용됩니다.
	/// - F : 일반 클래스나 구조체에 사용됩니다.
	/// - I : 인터페이스 클래스에 사용됩니다.
	///       인터페이스 클래스는 U 도 함께 사용됩니다.
	/// - E : 열거 형식에 사용됩니다.
	
	GENERATED_BODY()
	/// - 항상 클래스 첫 줄에 작성되어야 함
	
private:
	// 수평 입력 값을 나타냄
	float HorizontalInputValue;

	// 배고픔 입력 값을 나타냄
	float HungryValue;

	// 빙의된 플레이어 컨트롤러 객체를 나타냄
	class AGamePlayerController* GamePlayerController;

protected:
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementHelperComponent* MovementHelper;
	/// - VisibleAnywhere : 이 필드가 모든 곳에서 표시되도록 합니다.
	/// - EditAnywhere : 이 필드를 모든 곳에서 값을 변경할 수 있도록 합니다.

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	// 프로젝트 세팅 -> 입력에 매핑한 키 입력 이벤트를 폰에 등록합니다.
	/// - UInputComponent : 액터에 입력 이벤트를 등록하는 기능을 제공하는 컴포넌트입니다.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// A, D, <, > 키에 바인딩 시킬 메서드
	void InputHorizontal(float axis);

public:
	void AddHungryValue(float addValue);
	
private:
	UFUNCTION()
	void OnHit(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamagedCauser);
		
public:
	// HorizontalInputValue 값을 반환
	FORCEINLINE float GetHorizontalInputValue() const
	{
		return HorizontalInputValue;
	}

	FORCEINLINE float GetHungryValue() const
	{
		return HungryValue;
	}
};
