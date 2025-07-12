// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "LyCExperienceManagerComponent.generated.h"

class ULyCExperienceDefinition;

enum class ELyCExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deactivating,
};


// �Ű������� �ϳ�: �츮�� �ε��� �Ϸ� �� Experience �� �˷������
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLyCExperienceLoaded, const ULyCExperienceDefinition*)

/**
 * GameState �Ʒ� ���� ��ɵ��� ���ȭ �Ͽ� ���̰� �ʿ�������� ���� - Ȯ�强�� ��������
 * ���� - ������� ����� ���Ͼ��� ������
 * 
 * - ���� �ּ� - 
 * LyCExperienceManagerComponent
 * - �� �״��, �ش� Component�� game state �� owner�� �����鼭, experience�� ���� ������ ������ �ִ� component�̴�
 * - �Ӹ� �ƴ϶�, manager��� �ܾ ���ԵǾ� �ֵ���, experience �ε� ���� ������Ʈ �� �̺�Ʈ�� �����Ѵ�.
 */
UCLASS()
class LYRACLONE_API ULyCExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
public: 
	/**
	* member methods
	*/
	bool IsExperienceLoaded() { return (LoadState == ELyCExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }


	/**
	* �Ʒ��� OnExperienceLoaded�� ���ε��ϰų�, �̹� Experience �ε��� �Ϸ�Ǿ��ٸ� �ٷ� ȣ����
	*/
	void CallOrRegister_OnExperienceLoaded(FOnLyCExperienceLoaded::FDelegate && Delegate);

public:
	// ��� �ε� �Ұ��� �˾ƾ���
	// ***** ���⿡ �ʿ��Ѱ� ����ִٰ� �ε� �Ϸ�� �ƴϾ� why?
	// ���� �ִ°� GameState�� ��Ź�ϰ� GameState ���� �ε��ϹǷ� ���� GameState �� �ε��� ����������
	UPROPERTY()
	TObjectPtr<const ULyCExperienceDefinition> CurrentExperience;

	/** Experience�� �ε� ���¸� ����͸� */
	ELyCExperienceLoadState LoadState = ELyCExperienceLoadState::Unloaded;

	/** Experience �ε��� �Ϸ�� ����, Broadcasting Delegate */
	FOnLyCExperienceLoaded OnExperienceLoaded;

};
