// Fill out your copyright notice in the Description page of Project Settings.
// FPS �� �갡 �ϳ� AOS ��忡 �갡 �ϳ�. 
// ���� ���躰�� �ϳ�.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyCUserFacingExperience.generated.h"

/**
 * ��� �ϴ� ���� ����־� 
 * �� Experience �� ����־� 
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
