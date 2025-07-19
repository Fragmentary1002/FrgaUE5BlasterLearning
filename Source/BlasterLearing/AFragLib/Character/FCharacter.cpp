// Fill out your copyright notice in the Description page of Project Settings.


#include "FCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


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
    // - 单位：虚幻单位（UU），1 UU ≈ 1 厘米
    CameraBoom->TargetArmLength = 500.f;
    
    // 启用角色旋转控制弹簧臂
    // - 当玩家控制器旋转时，弹簧臂同步旋转（适用于第三人称视角）
    CameraBoom->bUsePawnControlRotation = true;
    
    // 启用摄像机延迟效果
    // - 移动时产生平滑跟随感，避免镜头瞬时跳动
    CameraBoom->bEnableCameraLag = true;



    // 创建摄像机组件（挂载到弹簧臂末端插槽）
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    
    // 将摄像机附加到弹簧臂末端的插槽
    // - 摄像机自动继承弹簧臂的位置和旋转，并处理碰撞回避 [3,5](@ref)
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// 设置摄像机的视角控制
    FollowCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

