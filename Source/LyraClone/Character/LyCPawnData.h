// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyCPawnData.generated.h"

/**
 * � ���� �������ұ�?
 * ��ǲ ��� ������?
 * �����Ƽ �ý����� ��� �ұ�?
 */
UCLASS()
class LYRACLONE_API ULyCPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public :
	ULyCPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
