// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LyCGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONE_API ALyCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALyCGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/// <summary>
	/// 익스피리언스 로딩
	/// </summary>
	void HandleMatchAssignmentIfNotExpectingOne();
};
