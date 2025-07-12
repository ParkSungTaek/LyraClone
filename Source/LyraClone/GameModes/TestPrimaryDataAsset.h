// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONE_API UTestPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/** the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowTypes = "Map"))
	FPrimaryAssetId MapID;

	/** the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowTypes = "LyCExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};
