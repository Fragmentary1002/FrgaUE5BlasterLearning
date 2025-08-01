// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlasterLearing/AFragLib/Component/FShootingComponent.h"
#include "BlasterLearing/AFragLib/Weapon/FWeaponBase.h"
#include "GameFramework/Character.h"
#include "FCharacter.generated.h"

UCLASS()
class BLASTERLEARING_API AFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void CrouchPressed();
	
	void EquipButtonPressed();

private:	
	

	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* FPlayerHUDWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AFWeaponBase* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AFWeaponBase* lastWeapon);

	UPROPERTY(VisibleAnyWhere, Category = Compenents)
	 class UFShootingComponent* shootingComponent;
	
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

public:
	void SetOverlappingWeapon(AFWeaponBase* Weapon);
	bool IsWeaponEquipped() const { return shootingComponent != nullptr && shootingComponent -> CurWeapon; }
};
