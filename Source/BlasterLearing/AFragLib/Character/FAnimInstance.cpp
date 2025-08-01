// Fill out your copyright notice in the Description page of Project Settings.


#include "FAnimInstance.h"
#include "FCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFAnimInstance::NativeInitializeAnimation()
{
    // 初始化动画实例时调用
    Super::NativeInitializeAnimation();
    //尝试获取角色实例
    FCharacter = Cast<AFCharacter>(TryGetPawnOwner());
}


void UFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    // 每帧更新动画实例时调用
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    if(FCharacter == nullptr)
    {
        // 如果FCharacter为空，尝试获取角色实例
        FCharacter = Cast<AFCharacter>(TryGetPawnOwner());
    }

    if (FCharacter == nullptr)
    {
        // 如果仍然为空，直接返回
        return;
    }

    FVector Velocity = FCharacter->GetVelocity();

    // 计算角色的速度
    // 忽略垂直分量，通常用于地面移动速度计算
    Velocity.Z = 0; // 忽略垂直速度分量
    Speed = Velocity.Size(); // 计算速度大小

    bIsInAir= FCharacter->GetMovementComponent()->IsFalling(); // 检查角色是否在空中
    bIsAccelerating = FCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0; // 检查角色是否正在加速

    bIsWeaponEquipped = FCharacter-> IsWeaponEquipped(); // 检查角色是否装备了武器

    bIsCroused = FCharacter ->bIsCrouched;

    bAnim = FCharacter ->IsAniming(); // 检查角色是否正在执行动画
}