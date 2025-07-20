// Fill out your copyright notice in the Description page of Project Settings.


#include "FLobbyGameMode.h"
#include "GameFramework/GameStateBase.h"


void AFLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    // Additional logic for when a player logs in can be added here

    int32 NumofPlayer = GameState.Get()->PlayerArray.Num();// Add the new player to the game state player array

    if(NumofPlayer ==2){
        UWorld* World = GetWorld();
        if(World){
            bUseSeamlessTravel= true; // Set the game to started state
            // Start the game when there are 2 players
            World->ServerTravel(FString("/Game/AFMaps/FMap?listen")); // Replace with your actual game map path
        }

    }


    
}