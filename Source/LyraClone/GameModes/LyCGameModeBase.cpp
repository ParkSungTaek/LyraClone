// Fill out your copyright notice in the Description page of Project Settings.

#include "LyCGameModeBase.h"
#include "LyCGameState.h"
#include "LyraClone/Character/LyCCharacter.h"
#include "LyraClone/Player/LyCPlayerController.h"
#include "LyraClone/Player/LyCPlayerState.h"

ALyCGameModeBase::ALyCGameModeBase()
{
	GameStateClass = ALyCGameState::StaticClass();
	PlayerControllerClass = ALyCPlayerController::StaticClass();
	PlayerStateClass = ALyCPlayerState::StaticClass();
	DefaultPawnClass = ALyCCharacter::StaticClass();

}

void ALyCGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// 아직 GameInstance를 통해, 초기화 작업이 진행되므로, 현 프레임에는 Lyra의 Concept인 Experience 처리를 진행할 수 없다.
	// - 이를 처리하기 위해, 한프레임 뒤에 이벤트를 받아 처리를 이어서 진행한다.
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);

}

/// <summary>
/// 왜 다음 프레임? 익스피리언스 로딩의 주체는 LyCExperienceManagerComponent 그런데? 
/// ALyCGameModeBase 의 InitGame 은 게임 실행의 거의 맨 앞에서 불림 즉 LyCExperienceManagerComponent 생성 전에 불림
/// 그런데 로딩 주체는 LyCExperienceManagerComponent 즉 즉시 실행 시 LyCExperienceManagerComponent 가 없어 에러 발생 
/// 그래서 다음 프레임에 부름
/// </summary>
void ALyCGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{

}
