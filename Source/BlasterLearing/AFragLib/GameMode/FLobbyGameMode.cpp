// Fill out your copyright notice in the Description page of Project Settings.


#include "FLobbyGameMode.h"
#include "GameFramework/GameStateBase.h"


void AFLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    // 调用父类实现，确保基础登录流程完成
    Super::PostLogin(NewPlayer);
    
    // 获取当前已登录玩家数量（游戏状态中的玩家数组人数）
    int32 NumofPlayer = GameState.Get()->PlayerArray.Num();
    
    // 当有2名玩家登录时，开始游戏
    if(NumofPlayer == 2)
    {
        UWorld* World = GetWorld();
        if(World)
        {
            bUseSeamlessTravel = true;  // 启用无缝切换地图功能
            // 无缝切换到战斗地图（使用监听服务端模式）
            World->ServerTravel(FString("/Game/AFMaps/FBattleMap?listen"));
        }
    }
}
