// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLASTERLEARING_API UFPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;

	void SetDisplayText(const  FString& TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void UpdateHUD(APawn* InPawn);

protected:
	
	virtual void NativeDestruct() override;
	
};
