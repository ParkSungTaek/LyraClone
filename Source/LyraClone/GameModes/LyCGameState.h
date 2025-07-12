// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LyCGameState.generated.h"

class ULyCExperienceManagerComponent;
/**
 * 
 */
UCLASS()
class LYRACLONE_API ALyCGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ALyCGameState();

public:
	// ExperienceManagerComponent 를 GameState 에서 관리
	UPROPERTY()
	TObjectPtr<ULyCExperienceManagerComponent> ExperienceManagerComponent; 

	
};
