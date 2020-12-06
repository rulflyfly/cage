// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LEDCage.generated.h"

class UStaticMeshComponent;
class UMaterial;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ME_N_LESHA_API ALEDCage : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALEDCage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    TArray<UStaticMeshComponent*> LEDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TArray<UStaticMeshComponent*> Tubes;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Cage;
    
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    UCameraComponent* Camera;
    
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    USpringArmComponent* SpringArm;
    
    UFUNCTION()
    void CreateLightStrip(int32 LEDAmount, UStaticMeshComponent* Tube);
    
    UFUNCTION()
    void CreateCage(int32 TubesAmount);
    
    UPROPERTY(EditAnywhere, Category = "LED Strip")
    int32 LEDPerMeter = 60;
    
    UPROPERTY(EditAnywhere, Category = "Tube")
    int32 TubesPerGage = 24;
    
    void LightFirstFrame();
    
};
