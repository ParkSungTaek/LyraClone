// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyCExperienceDefinition.generated.h"

class ULyCPawnData;

/**
 * �������� ������ �������
 * + GameFeaturesToEnable - �ش� ���� ��忡 �ʿ��� GameFeature plugin�� ���� ����� ������ �Ѵ�.
 * 
 */
UCLASS(BlueprintType, Const)
class LYRACLONE_API ULyCExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	ULyCExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* member variable
	*/
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<ULyCPawnData> DefaultPawnData;

	/**
	* �ش� property�� �ܼ��� ��ŷ �� �������� ���ܵд�.
	* - ���� ��忡 ���� GameFeature plugin�� �ε��ϴµ� �̿� ���� �������� �����ϸ� �ȴ�.
	* - ���� ShooterCore ���� Plugin �۾��� ���, �����ϰ� �� �����̴�.
	*/
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;


};
