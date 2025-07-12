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

	// ���� GameInstance�� ����, �ʱ�ȭ �۾��� ����ǹǷ�, �� �����ӿ��� Lyra�� Concept�� Experience ó���� ������ �� ����.
	// - �̸� ó���ϱ� ����, �������� �ڿ� �̺�Ʈ�� �޾� ó���� �̾ �����Ѵ�.
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);

}

/// <summary>
/// �� ���� ������? �ͽ��Ǹ��� �ε��� ��ü�� LyCExperienceManagerComponent �׷���? 
/// ALyCGameModeBase �� InitGame �� ���� ������ ���� �� �տ��� �Ҹ� �� LyCExperienceManagerComponent ���� ���� �Ҹ�
/// �׷��� �ε� ��ü�� LyCExperienceManagerComponent �� ��� ���� �� LyCExperienceManagerComponent �� ���� ���� �߻� 
/// �׷��� ���� �����ӿ� �θ�
/// </summary>
void ALyCGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{

}
