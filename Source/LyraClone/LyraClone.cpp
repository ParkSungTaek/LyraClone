// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraClone.h"
#include "LyCLogChannels.h"
#include "Modules/ModuleManager.h"

class FLyraClone : public FDefaultGameModuleImpl
{
public : 
	/// <summary>
	/// 모듈이 시작되었을 때 발동하는 오버라이딩 함수
	/// </summary>
	virtual void StartupModule() override; 
	/// <summary>
	/// 모듈이 종료되었을 때 발동하는 오버라이딩 함수
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
