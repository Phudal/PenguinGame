// Fill out your copyright notice in the Description page of Project Settings.


//#include "ClonePenguin/Actor/PlayerCharacter/PlayerCharacter.h"
#include "Actor/PlayerCharacter/PlayerCharacter.h"

#include "Actor/PlayerController/GamePlayerController.h"
#include "Single/GameInstance/ClonePenguinGameInst.h"
#include "Widget/GameWidget/GameWidget.h"
#include "Component/CharacterMovementHelperComponent/CharacterMovementHelperComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 펭귄 SkeletalMesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("SkeletalMesh'/Game/00_Work/Resources/Character/SK_Penguin.SK_Penguin'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBP_PLAYER_CHARACTER(
		TEXT("AnimBlueprint'/Game/00_Work/Blueprints/Actor/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));

	// 펭귄 SkeletalMesh Asset을 성공적으로 찾았다면
	if (SK_BODY.Succeeded())
	{
		// 캐릭터 Skeletal Mesh 를 찾은 SK_BODY 로 설정
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
		/// - GetMesh() : Character 클래스에 내장되어있는 SkeletalMesh Component 객체를 반환합니다.

		// Skeletal Mesh Component 의 상대 위치를 설정합니다.
		//GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

		// Skeletal Mesh Component 의 상대 회전을 설정합니다.
		//GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

		// Skeletal Mesh Component 의 상대 위치 / 회전을 설정합니다.
		GetMesh()->SetRelativeLocationAndRotation(
			FVector::UpVector * -88.0f,
			FRotator(0.0f, -90.0f, 0.0f));

		if (ANIMBP_PLAYER_CHARACTER.Succeeded())
			GetMesh()->SetAnimInstanceClass(ANIMBP_PLAYER_CHARACTER.Class);
		/// - SkeletalMeshComponent 에서 사용할 AnimInstance Class 를 설정합니다.
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter.cpp :: %d LINE :: SK_BODY is not Loaded!"),
			__LINE__);
		// - UE_LOG(카테고리, 레벨, 내용)
		/// - 카테고리 : 로그의 카테고리를 설정합니다.
		/// - 레벨 : 로그의 수준을 설정합니다.
		///   - Fatal : 로그 파일과 콘솔에 항상 출력되며, 프로그램이 종료됩니다.
		///   - Error : 적색으로 콘솔과 파일에 출력됩니다.
		///   - Warning : 황색으로 콘솔과 파일에 출력됩니다.
	}

	MovementHelper = CreateDefaultSubobject<UCharacterMovementHelperComponent>(TEXT("MOVEMENT_HELPER"));
	/// - CreateDefaultSubobject<TReturnType>(HASH)
	/// - TReturnType 에 해당하는 클래스를 동적 할당합니다.
	/// - HASH : 액터에 속한 객체들을 구분하기 위해 사용되는 문자열

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	HungryValue = 50.0f;	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 액터에 태그 추가
	Tags.Add(FName(TEXT("PlayerCharacter")));

	// 피해를 입었을 경우 호출될 메서드를 바인딩
	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::OnHit);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddHungryValue(DeltaTime * -2.0f);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GamePlayerController = Cast<AGamePlayerController>(NewController);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

#pragma region Delegate Info
	// 대리자(Delegate)
	/// - 메서드를 보다 효율적으로 사용하기 위하여 특정 메서드 자체를 캡슐화 시킬 수 있게 
	///   만들어주는 기능
	/// - DECLARE_DELEGATE() : 싱글 캐스트 대리자 형식을 선언합니다.
	///
	/// - DECLARE_DYNAMIC_DELEGATE() : 블루프린트에서 사용 가능한 
	///   싱글 캐스트 대리자 형식을 선언합니다.
	///   바인딩되는 메서드 선언 상단에 UFUNCTION() 매크로가 작성되어야 합니다.
	///
	/// - DECLARE_MULTICAST_DELEGATE() : 멀티 캐스트 대리자 형식을 선언합니다.
	///
	/// - DECLARE_DYNAMIC_MULTICAST_DELEGATE() : 블루프린트에서 사용 가능한 
	///   멀티 캐스트 대리자 형식을 선언합니다.
	///   바인딩되는 메서드 선언 상단에 UFUNCTION() 매크로가 작성되어야 합니다.
	///
	/// - ~~~_RetVal : 해당 형식의 대리자는 void 반환형식이 아닌 
	///   다른 반환 형식의 메서드를 대리합니다.
	/// - ~~~_OneParam / _TwoParams / ThreeParams ....

	/*
	myTestDelegate.BindLambda(
		[this]()
		{ UE_LOG(LogTemp, Warning, TEXT("myTestDelegate Called!")); });


	if (myTestDelegate.IsBound())
		myTestDelegate.Execute();
	*/
	/// - IsBound() 대리자가 대리하는 메서드가 존재한다면 true 를 반환합니다.
	///
	/// - 싱글 캐스트 대리자
	/// - Execute() 대리자가 대리하는 메서드를 호출합니다.
	/// - ExecuteIfBound() 를 통해 대리하는 메서드가 존재하는 경우 
	///   대리하는 메서드를 호출할 수 있습니다.
	/// - 멀티 캐스트 대리자
	/// - Broadcast() 대리자가 대리하는 메서드들을 호출합니다.
#pragma endregion
	PlayerInputComponent->BindAxis(
		TEXT("Horizontal"), this, &APlayerCharacter::InputHorizontal);
	/// - BindAxis : 프로젝트 설정->입력에 정의된 축과 사용될 메서드를 등록합니다.
	/// - 등록될 수 있는 메서드의 형태 : void(float)
	/// - BindAxis(AxisName, Object, Func)
	/// - AxisName : 축 이름을 전달합니다.
	/// - Object : 메서드를 호출할 때 사용할 객체를 전달합니다.
	/// - Func : 호출시킬 메서드를 전달합니다.
}

void APlayerCharacter::InputHorizontal(float axis)
{
	HorizontalInputValue = axis;
}

void APlayerCharacter::AddHungryValue(float addValue)
{
	HungryValue += addValue;

	if (HungryValue <= 0.0f)
	{
		Cast<UGameWidget>(GamePlayerController->GetWidget())->
			SetGameOverVisibility(true, true);
	}

	// 배고픔 수치를 0 ~ 100 사이의 값으로 가둠
	HungryValue = FMath::Clamp(HungryValue, 0.0f, 100.0f);
	/// - Clamp(x, min, max) : x 의 값을 min ~ max 사이의 값으로 가두고, 그 결과를 반환함
}

void APlayerCharacter::OnHit(
	AActor* DamagedActor, 
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy, 
	AActor* DamagedCauser)
{
	// 배고픔 수치 변경
	AddHungryValue(Damage);

	// 점수 증가 / 감소'
	GameInst()->AddScore(Damage);
}

