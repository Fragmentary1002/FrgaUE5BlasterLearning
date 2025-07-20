// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLASTERLEARING_API AFLobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	virtual void PostLogin(APlayerController* NewPlayer) override; // Called when a player logs in
	// virtual void Logout(AController* Exiting) override;

};
