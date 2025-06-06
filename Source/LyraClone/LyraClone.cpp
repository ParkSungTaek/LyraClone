// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraClone.h"
#include "LyCLogChannels.h"
#include "Modules/ModuleManager.h"

class FLyraClone : public FDefaultGameModuleImpl
{
public : 
	/// <summary>
	/// ����� ���۵Ǿ��� �� �ߵ��ϴ� �������̵� �Լ�
	/// </summary>
	virtual void StartupModule() override; 
	/// <summary>
	/// ����� ����Ǿ��� �� �ߵ��ϴ� �������̵� �Լ�
	/// </summary>
	virtual void ShutdownModule() override;
};
void FLyraClone::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogLyC, Warning, TEXT("StartModule!!"));
}

void FLyraClone::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}

IMPLEMENT_PRIMARY_GAME_MODULE( FLyraClone, LyraClone, "LyraClone" );
