// Fill out your copyright notice in the Description page of Project Settings.


#include "LEDCage.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Containers/UnrealString.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ALEDCage::ALEDCage()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    Cage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cage"));
    CreateCage(TubesPerGage);
    //CreateLightStrip(LEDPerMeter);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Cage);
    SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
    SpringArm->TargetArmLength = 400.f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.f;
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ALEDCage::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void ALEDCage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALEDCage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALEDCage::CreateLightStrip(int32 LEDAmount, UStaticMeshComponent* Tube)
{
  
    for (int32 i = 0; i < LEDAmount; i++)
    {
        FName LEDName = *FString::Printf(TEXT("LED %i"), i);
        UStaticMeshComponent* LED = CreateDefaultSubobject<UStaticMeshComponent>(LEDName);
        LEDs.Add(LED);
        LED->SetupAttachment(Tube);

        static ConstructorHelpers::FObjectFinder<UStaticMesh>LEDAsset(TEXT("StaticMesh'/Game/Assets/LED.LED'"));

        if (LEDAsset.Succeeded())
        {
            float YLocation = i*1.6f - 55.f;
            LED->SetStaticMesh(LEDAsset.Object);
            LED->SetRelativeLocation(FVector(0.f, YLocation, 0.f));
        }

        static ConstructorHelpers::FObjectFinder<UMaterialInterface>LEDMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/EWhite.EWhite'"));
        if (LEDMaterial.Succeeded())
        {
            LED->SetMaterial(0, LEDMaterial.Object);
        }
    }
}


void ALEDCage::CreateCage(int32 TubesAmount)
{
    for (int32 i = 0; i < TubesAmount; i++)
    {
        FName TubeName = *FString::Printf(TEXT("Tube %i"), i);
        UStaticMeshComponent* Tube = CreateDefaultSubobject<UStaticMeshComponent>(TubeName);
        Tubes.Add(Tube);
        Tube->SetupAttachment(Cage);
        
        static ConstructorHelpers::FObjectFinder<UStaticMesh>TubeAsset(TEXT("StaticMesh'/Game/Assets/Tube.Tube'"));

        if (TubeAsset.Succeeded())
        {
            Tube->SetStaticMesh(TubeAsset.Object);
        }

        static ConstructorHelpers::FObjectFinder<UMaterialInterface>TubeMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/RGWhite.RGWhite'"));
        if (TubeMaterial.Succeeded())
        {
            Tube->SetMaterial(0, TubeMaterial.Object);
        }
    }
}
