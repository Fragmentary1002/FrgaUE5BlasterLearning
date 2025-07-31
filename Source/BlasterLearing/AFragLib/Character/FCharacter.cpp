// Fill out your copyright notice in the Description page of Project Settings.


#include "FCharacter.h"

#include "BlasterLearing/AFragLib/Weapon/FWeaponBase.h"
#include "BlasterLearing/AFragLib/Component/FShootingComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"


#pragma region 生命周期
AFCharacter::AFCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 创建弹簧臂组件（挂载到根组件）
    // - TEXT 宏确保字符串的跨平台本地化支持
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));  
    // 将弹簧臂附加至角色的根组件（如胶囊体）
    // - 确保组件层级关系：RootComponent → SpringArm → Camera [1,5](@ref)
    CameraBoom->SetupAttachment(RootComponent);   
    // 设置弹簧臂长度（摄像机与角色的默认距离）
    CameraBoom->TargetArmLength = 500.f;   
    // 启用角色旋转控制弹簧臂  当玩家控制器旋转时，弹簧臂同步旋转（适用于第三人称视角） 
    CameraBoom->bUsePawnControlRotation = true;
    // 创建摄像机组件（挂载到弹簧臂末端插槽）
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));   
    // 将摄像机附加到弹簧臂末端的插槽
    // - 摄像机自动继承弹簧臂的位置和旋转，并处理碰撞回避 [3,5](@ref)
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// 设置摄像机的视角控制
    FollowCamera->bUsePawnControlRotation = false; // 禁用摄像机的控制器旋转（通常用于第一人称视角）


    //动画后的优化
    bUseControllerRotationYaw = false; // 禁止控制器偏航旋转
    GetCharacterMovement()->bOrientRotationToMovement = true; // 角色朝向移动方向


    //HUD
    FPlayerHUDWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("FPlayerHUDWidget"));
    FPlayerHUDWidget->SetupAttachment(RootComponent); // 将OverheadWidget附加到角色的根组件

    //Component
    shootingComponent = CreateDefaultSubobject<UFShootingComponent>(TEXT("ShootingComponent"));
	shootingComponent ->SetIsReplicated(true); // 确保射击组件在网络上复制
}

// Called when the game starts or when spawned
void AFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

 
}

#pragma endregion 

# pragma region 变量复制
void AFCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(AFCharacter,OverlappingWeapon,COND_OwnerOnly);
    
}



void AFCharacter::SetOverlappingWeapon(AFWeaponBase* Weapon)
{
    if (OverlappingWeapon)
    {
        OverlappingWeapon->ShowPickupWidget(false);
    }
    OverlappingWeapon = Weapon;
    if (IsLocallyControlled())
    {
        if (OverlappingWeapon)
        {
            OverlappingWeapon->ShowPickupWidget(true);
        }
    }
}

void AFCharacter::OnRep_OverlappingWeapon(AFWeaponBase* lastWeapon)
{
    if (OverlappingWeapon)
    {
        OverlappingWeapon->ShowPickupWidget(true);
    }
   if (lastWeapon)
   {
       lastWeapon->ShowPickupWidget(false);
   }
}


# pragma endregion

# pragma region 装备
void AFCharacter::EquipButtonPressed()
{
    if (shootingComponent )
    {
        if (HasAuthority())
        {
            //server端装备武器
            shootingComponent-> SetWeapon(OverlappingWeapon);
        }
        else
        {
            //客户端请求装备武器
            ServerEquipButtonPressed();
        }
       
    }
}

void AFCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    if (shootingComponent)
    {
        shootingComponent->Character= this; // 设置射击组件的角色引用
    }
}

# pragma endregion 


#pragma region 网络函数
void AFCharacter::ServerEquipButtonPressed_Implementation()
{
    EquipButtonPressed();
}
#pragma endregion


#pragma region 移动函数
void AFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);


    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFCharacter::Jump);

    PlayerInputComponent->BindAxis("MoveForward", this, &AFCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AFCharacter::Turn);   
    PlayerInputComponent->BindAxis("LookUp", this, &AFCharacter::LookUp);
    
    PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AFCharacter::Jump);

}


void AFCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // 获取前向向量并应用移动

        // 完整控制器旋转（包含俯仰角）​
        // const FRotator Rotation = Controller->GetControlRotation();
        //  ​​仅Yaw方向旋转（锁定水平移动）​
        const FRotator Rotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // 获取右向向量并应用移动

        // ​​完整控制器旋转（包含俯仰角）​
        // const FRotator Rotation = Controller->GetControlRotation();
        //  ​​仅Yaw方向旋转（锁定水平移动）​
        const FRotator Rotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AFCharacter::Turn(float Value)
{
    // 处理水平旋转输入
    AddControllerYawInput(Value);
}


void AFCharacter::LookUp(float Value)
{
    // 处理垂直旋转输入
    AddControllerPitchInput(Value);
}



#pragma endregion

