// Fill out your copyright notice in the Description page of Project Settings.
// FPS 에 얘가 하나 AOS 모드에 얘가 하나. 
// 유저 경험별로 하나.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyCUserFacingExperience.generated.h"

/**
 * 얘는 일단 맵을 들고있어 
 * 또 Experience 를 들고있어 
 */
UCLASS()
class LYRACLONE_API ULyCUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()
public :
	/** the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowTypes = "Map"))
	FPrimaryAssetId MapID;

	/** the specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowTypes = "LyCExperienceDefinition"))
	FPrimaryAssetId ExperienceID;

};
