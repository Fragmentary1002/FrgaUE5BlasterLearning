// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FShootingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTERLEARING_API UFShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFShootingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class AFCharacter;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetWeapon(class AFWeaponBase* Weapon) ;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class AFCharacter * Character;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Weapon")
	class AFWeaponBase* CurWeapon;
	
public:	
	
	

		
};
