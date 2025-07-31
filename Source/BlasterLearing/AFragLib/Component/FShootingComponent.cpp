// Fill out your copyright notice in the Description page of Project Settings.


#include "FShootingComponent.h"
#include "BlasterLearing/AFragLib/Weapon/FWeaponBase.h"
#include "BlasterLearing/AFragLib/Character/FCharacter.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"

UFShootingComponent::UFShootingComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UFShootingComponent::BeginPlay()
{
	Super::BeginPlay();


}



void UFShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFShootingComponent::SetWeapon( AFWeaponBase* Weapon)
{
	if (Character == nullptr || Weapon == nullptr)
	{
		return;
	}
	CurWeapon = Weapon;
	CurWeapon->SetState(FWeaponState::EWS_Equipped); // 设置武器的拥有者为角色
	
	 USkeletalMeshComponent* mesh = Character->GetMesh(); // 获取角色的网格组件
	const USkeletalMeshSocket* hand = mesh-> GetSocketByName(FName("RightHandSocket")); // 将武器附加到角色的右手插槽
	if (hand)
    {
        hand->AttachActor(CurWeapon, mesh); // 将武器附加到角色的右手插槽
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("RightHandSocket not found!"));
    }
	CurWeapon ->SetOwner(Character); // 设置武器的拥有者为角色
	
}

