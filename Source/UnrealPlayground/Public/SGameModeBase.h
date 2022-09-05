// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMonsterData.h"
#include "AI/SAICharacter.h"
#include "Engine/DataTable.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FMonsterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId MonsterId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward = 20.f;
};


class USSaveGame;
UCLASS()
class UNREALPLAYGROUND_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UFUNCTION(Exec)
	void KillAll();

	UFUNCTION(BlueprintCallable, Category="SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();

protected:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION()
	void SpawnBot_TimerElapsed();

	UFUNCTION()
	void OnMonsterLoaded(FPrimaryAssetId LoadedId, FVector SpawnLocation);

	UFUNCTION()
	void OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UDataTable* MonsterTable;

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 MinionKillCreditsChange = 10;

	UPROPERTY()
	FString SlotName = "SaveGame01";

	UPROPERTY()
	USSaveGame* CurrentSaveGame;
};
