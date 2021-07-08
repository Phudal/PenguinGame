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

	// ��� SkeletalMesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("SkeletalMesh'/Game/00_Work/Resources/Character/SK_Penguin.SK_Penguin'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIMBP_PLAYER_CHARACTER(
		TEXT("AnimBlueprint'/Game/00_Work/Blueprints/Actor/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));

	// ��� SkeletalMesh Asset�� ���������� ã�Ҵٸ�
	if (SK_BODY.Succeeded())
	{
		// ĳ���� Skeletal Mesh �� ã�� SK_BODY �� ����
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
		/// - GetMesh() : Character Ŭ������ ����Ǿ��ִ� SkeletalMesh Component ��ü�� ��ȯ�մϴ�.

		// Skeletal Mesh Component �� ��� ��ġ�� �����մϴ�.
		//GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

		// Skeletal Mesh Component �� ��� ȸ���� �����մϴ�.
		//GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

		// Skeletal Mesh Component �� ��� ��ġ / ȸ���� �����մϴ�.
		GetMesh()->SetRelativeLocationAndRotation(
			FVector::UpVector * -88.0f,
			FRotator(0.0f, -90.0f, 0.0f));

		if (ANIMBP_PLAYER_CHARACTER.Succeeded())
			GetMesh()->SetAnimInstanceClass(ANIMBP_PLAYER_CHARACTER.Class);
		/// - SkeletalMeshComponent ���� ����� AnimInstance Class �� �����մϴ�.
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter.cpp :: %d LINE :: SK_BODY is not Loaded!"),
			__LINE__);
		// - UE_LOG(ī�װ�, ����, ����)
		/// - ī�װ� : �α��� ī�װ��� �����մϴ�.
		/// - ���� : �α��� ������ �����մϴ�.
		///   - Fatal : �α� ���ϰ� �ֿܼ� �׻� ��µǸ�, ���α׷��� ����˴ϴ�.
		///   - Error : �������� �ְܼ� ���Ͽ� ��µ˴ϴ�.
		///   - Warning : Ȳ������ �ְܼ� ���Ͽ� ��µ˴ϴ�.
	}

	MovementHelper = CreateDefaultSubobject<UCharacterMovementHelperComponent>(TEXT("MOVEMENT_HELPER"));
	/// - CreateDefaultSubobject<TReturnType>(HASH)
	/// - TReturnType �� �ش��ϴ� Ŭ������ ���� �Ҵ��մϴ�.
	/// - HASH : ���Ϳ� ���� ��ü���� �����ϱ� ���� ���Ǵ� ���ڿ�

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	HungryValue = 50.0f;	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���Ϳ� �±� �߰�
	Tags.Add(FName(TEXT("PlayerCharacter")));

	// ���ظ� �Ծ��� ��� ȣ��� �޼��带 ���ε�
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
	// �븮��(Delegate)
	/// - �޼��带 ���� ȿ�������� ����ϱ� ���Ͽ� Ư�� �޼��� ��ü�� ĸ��ȭ ��ų �� �ְ� 
	///   ������ִ� ���
	/// - DECLARE_DELEGATE() : �̱� ĳ��Ʈ �븮�� ������ �����մϴ�.
	///
	/// - DECLARE_DYNAMIC_DELEGATE() : �������Ʈ���� ��� ������ 
	///   �̱� ĳ��Ʈ �븮�� ������ �����մϴ�.
	///   ���ε��Ǵ� �޼��� ���� ��ܿ� UFUNCTION() ��ũ�ΰ� �ۼ��Ǿ�� �մϴ�.
	///
	/// - DECLARE_MULTICAST_DELEGATE() : ��Ƽ ĳ��Ʈ �븮�� ������ �����մϴ�.
	///
	/// - DECLARE_DYNAMIC_MULTICAST_DELEGATE() : �������Ʈ���� ��� ������ 
	///   ��Ƽ ĳ��Ʈ �븮�� ������ �����մϴ�.
	///   ���ε��Ǵ� �޼��� ���� ��ܿ� UFUNCTION() ��ũ�ΰ� �ۼ��Ǿ�� �մϴ�.
	///
	/// - ~~~_RetVal : �ش� ������ �븮�ڴ� void ��ȯ������ �ƴ� 
	///   �ٸ� ��ȯ ������ �޼��带 �븮�մϴ�.
	/// - ~~~_OneParam / _TwoParams / ThreeParams ....

	/*
	myTestDelegate.BindLambda(
		[this]()
		{ UE_LOG(LogTemp, Warning, TEXT("myTestDelegate Called!")); });


	if (myTestDelegate.IsBound())
		myTestDelegate.Execute();
	*/
	/// - IsBound() �븮�ڰ� �븮�ϴ� �޼��尡 �����Ѵٸ� true �� ��ȯ�մϴ�.
	///
	/// - �̱� ĳ��Ʈ �븮��
	/// - Execute() �븮�ڰ� �븮�ϴ� �޼��带 ȣ���մϴ�.
	/// - ExecuteIfBound() �� ���� �븮�ϴ� �޼��尡 �����ϴ� ��� 
	///   �븮�ϴ� �޼��带 ȣ���� �� �ֽ��ϴ�.
	/// - ��Ƽ ĳ��Ʈ �븮��
	/// - Broadcast() �븮�ڰ� �븮�ϴ� �޼������ ȣ���մϴ�.
#pragma endregion
	PlayerInputComponent->BindAxis(
		TEXT("Horizontal"), this, &APlayerCharacter::InputHorizontal);
	/// - BindAxis : ������Ʈ ����->�Է¿� ���ǵ� ��� ���� �޼��带 ����մϴ�.
	/// - ��ϵ� �� �ִ� �޼����� ���� : void(float)
	/// - BindAxis(AxisName, Object, Func)
	/// - AxisName : �� �̸��� �����մϴ�.
	/// - Object : �޼��带 ȣ���� �� ����� ��ü�� �����մϴ�.
	/// - Func : ȣ���ų �޼��带 �����մϴ�.
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

	// ����� ��ġ�� 0 ~ 100 ������ ������ ����
	HungryValue = FMath::Clamp(HungryValue, 0.0f, 100.0f);
	/// - Clamp(x, min, max) : x �� ���� min ~ max ������ ������ ���ΰ�, �� ����� ��ȯ��
}

void APlayerCharacter::OnHit(
	AActor* DamagedActor, 
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy, 
	AActor* DamagedCauser)
{
	// ����� ��ġ ����
	AddHungryValue(Damage);

	// ���� ���� / ����'
	GameInst()->AddScore(Damage);
}

