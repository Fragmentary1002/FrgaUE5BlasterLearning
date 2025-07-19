// Fill out your copyright notice in the Description page of Project Settings.


#include "FCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
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
}

// Called when the game starts or when spawned
void AFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AFCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AFCharacter::Turn);   
    PlayerInputComponent->BindAxis("LookUp", this, &AFCharacter::LookUp);

}

void AFCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // 获取前向向量并应用移动

        // ​​完整控制器旋转（包含俯仰角）​
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

// Called every frame
void AFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




