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


// 매개변수는 하나: 우리가 로딩을 완료 한 Experience 를 알려줘야해
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLyCExperienceLoaded, const ULyCExperienceDefinition*)

/**
 * GameState 아래 하위 기능들을 모듈화 하여 붙이고 필요없어지면 제거 - 확장성이 좋아진다
 * 단점 - 디버깅이 힘들고 파일양이 많아짐
 * 
 * - 강의 주석 - 
 * LyCExperienceManagerComponent
 * - 말 그대로, 해당 Component는 game state 를 owner로 가지면서, experience의 상태 정보를 가지고 있는 component이다
 * - 뿐만 아니라, manager라는 단어가 포함되어 있듯이, experience 로딩 상태 업데이트 및 이벤트를 관리한다.
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
	* 아래의 OnExperienceLoaded에 바인딩하거나, 이미 Experience 로딩이 완료되었다면 바로 호출함
	*/
	void CallOrRegister_OnExperienceLoaded(FOnLyCExperienceLoaded::FDelegate && Delegate);

public:
	// 어떤걸 로딩 할건지 알아야해
	// ***** 여기에 필요한걸 들고있다고 로딩 완료는 아니야 why?
	// 여기 있는걸 GameState에 부탁하고 GameState 에서 로딩하므로 아직 GameState 가 로딩을 안했을수도
	UPROPERTY()
	TObjectPtr<const ULyCExperienceDefinition> CurrentExperience;

	/** Experience의 로딩 상태를 모니터링 */
	ELyCExperienceLoadState LoadState = ELyCExperienceLoadState::Unloaded;

	/** Experience 로딩이 완료된 이후, Broadcasting Delegate */
	FOnLyCExperienceLoaded OnExperienceLoaded;

};
