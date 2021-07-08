// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DropObject/DropObject.h"

#include "GameFramework/DamageType.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Struct/DropObjectInfo/DropObjectInfo.h"

// Sets default values
ADropObject::ADropObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent 를 추가함
	DropObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DROP_OBJ_MESH"));

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("ROTATING_MOVEMENT"));

	// 추가한 StaticMeshComponent 를 액터를 대표하는 컴포넌트로 지정함
	SetRootComponent(DropObjectMesh);
}

// Called when the game starts or when spawned
void ADropObject::BeginPlay()
{
	Super::BeginPlay();

	DropObjectMesh->OnComponentBeginOverlap.AddDynamic(
		this, &ADropObject::AddDamage);
}

// Called every frame
void ADropObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FallDown(DeltaTime);
}

void ADropObject::FallDown(float dt)
{
	FVector newLocation = GetActorLocation() +
		(FVector::DownVector * FallDownSpeed * dt);

	SetActorLocation(newLocation);

	if (newLocation.Z < -250.0f)
	{
		// 액터를 제거
		Destroy();
		/// - 만약 다른 액터를 제거하고 싶을 경우 
		///   GetWorld()->DestroyActor() 를 사용합니다.
	}
}

void ADropObject::InitializeDropObject(float fallDownSpeed, FDropObjectInfo* dropObjInfo)
{
	// 떨어지는 속력 설정
	FallDownSpeed = fallDownSpeed;

	// 대미지, 회복량 설정
	ChangeHungryValue = dropObjInfo->ChangeHungryValue;

	// 오브젝트 타입 설정
	DropObjectType = dropObjInfo->DropObjectType;

	RotatingMovement->RotationRate = (DropObjectType == EDropObjectType::DT_Fish) ?
		FRotator::ZeroRotator : FRotator(0.0f, 0.0f, -180.0f);

	// Static Mesh 애셋 적용
	DropObjectMesh->SetStaticMesh(dropObjInfo->DropObjectStaticMesh);

	// static Mesh Component 의 Collision Preset 속성 변경
	DropObjectMesh->SetCollisionProfileName(FName(TEXT("OverlapAllDynamic")));
}

void ADropObject::AddDamage(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	// 플레이어 캐릭터와 겹쳤을 경우
	if (OtherActor->ActorHasTag(TEXT("PlayerCharacter")))
	{
		// 대미지 / 회복량 저장
		float addDamage = (DropObjectType == EDropObjectType::DT_Fish) ?
			ChangeHungryValue : -ChangeHungryValue;

		// 플레이어 캐릭터에게 대미지를 가함
		UGameplayStatics::ApplyDamage(
			OtherActor,
			addDamage,
			nullptr,
			this,
			UDamageType::StaticClass());
		/// ApplyDamage(AActor *					DamagedActor
		///             float						BaseDamage
		///             AController*				EventInstigator
		///             AActor *					DamageCauser
		///             TSubclassOf<UDamageType>	DamageTypeClass)
		/// - DamagedActor : 대미지를 가할 액터를 나타냅니다.
		/// - BaseDamage : 가할 대미지를 나타냅니다.
		/// - EventInstigator : 피해를 가한 컨트롤러를 나타냅니다.
		/// - DamageCauser : 피해를 입히는 객체를 나타냅니다.
		/// - DamageTypeClass : 대미지 타입을 설명하는 UClass 를 전달합니다.

		// UE_LOG(LogTemp, Log, TEXT("crash!"));
		
		// 액터를 제거
		Destroy();
	}
}

