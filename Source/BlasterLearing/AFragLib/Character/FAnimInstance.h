// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLASTERLEARING_API UFAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	// Called when the animation instance is initialized
	virtual void NativeInitializeAnimation() override;
	// Called every frame
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class AFCharacter* FCharacter;

	// 可以在这里添加动画状态机相关的变量和函数
	// 例如：当前动画状态、速度、方向等
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	float Speed;// 速度值

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;  // 空中状态标识，True表示角色处于跳跃或下落状态

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating; // 加速状态标识，True表示角色正在加速移动（如奔跑）

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool bIsWeaponEquipped; // 武器装备状态标识，True表示角色已装备武器


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool bIsCroused; // 武器装备状态标识，True表示角色已装备武器

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool bAnim; // 武器装备状态标识，True表示角色已装备武器

};
