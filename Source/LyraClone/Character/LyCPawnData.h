// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyCPawnData.generated.h"

/**
 * 어떤 폰을 만들어야할까?
 * 인풋 어떻게 받을까?
 * 어빌리티 시스템을 어떻게 할까?
 */
UCLASS()
class LYRACLONE_API ULyCPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public :
	ULyCPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
