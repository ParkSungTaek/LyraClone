// Fill out your copyright notice in the Description page of Project Settings.


#include "LyCAssetManager.h"
#include "LyraClone/LyCLogChannels.h"

ULyCAssetManager::ULyCAssetManager()
{
}

ULyCAssetManager& ULyCAssetManager::Get()
{
	check(GEngine);

	// 우리는 AssetManager를 UEngine의 GEngine의 AssetManager의 class를 오버라이드 했기 때문에, GEngine에 AssetManager가 있음
	if(ULyCAssetManager* Singleton = Cast<ULyCAssetManager>(GEngine -> AssetManager))
	{ 
		return *Singleton;
	}

	// 만약 GEngine의 AssetManager가 ULyCAssetManager 타입이 아니라면, Fatal 에러를 발생시킴
	UE_LOG(LogLyC, Fatal, TEXT("invalid AssetManagerClassname in DefaultEngine.ini (project setting) it must be LyCAssetManager"));

	return *NewObject<ULyCAssetManager>();
}

PRAGMA_DISABLE_OPTIMIZATION
void ULyCAssetManager::StartInitialLoading()
{
	// 디버깅 잡아본 결과 - 아직 언리얼이 켜지기도 전 로딩 타임에 일어난다.
	// 언리얼이 켜지기 전 로딩 타임에는 언리얼이 멀티스레드로 동작하며 로직적으로 안정성이 보장되지않는다. 
	Super::StartInitialLoading();
}

PRAGMA_DISABLE_OPTIMIZATION
bool ULyCAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

/// <summary>
/// 동기식 로딩 
/// 동기식 로딩의 장점 : 비동기식보다 함수의 속도가 빠르다. 로직이 간단하며 직관적이다.  
/// 동기식 로딩의 단점 : 다음 로직이 로딩에 의해 지연될 수 있다.
/// 합리적 사용처 : 게임 시작 시, "로딩타임"에 게임이 시작되기 전에 반드시 필요한 리소스들 (예: UI, HUD 등) 을 로딩할 때 사용한다.
/// 
/// 인게임에서 자주 사용하면 프레임 드랍이 발생할 수 있으므로, 인게임에서 자주 사용하지 않는 것이 좋다.
/// </summary>
/// <param name="AssetPath"></param>
/// <returns></returns>
UObject* ULyCAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// 해당 함수를 따로 만든 이유는 'synchronous load asset 이 불필요하게 하는 것이 없는지 확인하기 위함'
	if (AssetPath.IsValid())
	{
		// FScopeLogTime을 확인해본다.
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads()) // LogAssetLoads 를 넘기면 확인해볼거임
		{
			// 단순히 로깅하면서, 초단위로 로깅 진행
			// 이 함수가 얼마나 걸렸는지 확인가능
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		// 여기서 두가지 분기 : 
		// 1. AssetManager가 있으면, AssetManager의 StreamableManager를 통해 정적 로딩
		// 2. 아니면, FSoftObjectPath를 통해 바로 정적 로딩
		if (UAssetManager::IsValid())
		{
			// GetStreamableManager 동기,비동기 로딩을 관리하는 매니저
			// LoadSynchronous 진짜 로딩 진행
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// if asset manager is not ready, use LoadObject()
		// - 슥 보면, StaticLoadObject 가 보인다. 
		// - 참고로, 항상 StaticLoadObject하기 전에 StaticFindObject를 통해 확인하고 실패하면 진짜 로딩함
		return AssetPath.TryLoad(); // - 매우 느려서 애지간하면 쓰지마라, UAssetManager 가 없을때만 

		// 추가
		// 위 함수들 AssetPath.TryLoad() 와 UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath); 는
		// 이미 로딩이 되어있으면 로딩 되어있는 거 가지고 온다. 따로 추가 로딩하지 않음
		// 이 함수의 의의는 동기로딩으로 시간이 낭비되는거 로그로 확인하고 싶어서 따로 동기 로딩만 뺀것
		
		// FSoftObjectPath 는 보조기억장치에 들어있는 에셋들의 경로를 들고 있음 (메모리에 안올라온 에셋들의 경로가 필요 그걸 담당하는게 FSoftObjectPath)
		// 에셋 잡고 ctrl + c 하고 ctrl + v해서 나오는 그 패스를 들고있는 담당자가 FSoftObjectPath 인것
	}
	return nullptr;
}

void ULyCAssetManager::AddLoadedAsset(const UObject* Asset)
{
	// AssetManager 는 기본적으로 언리얼 시작시 로딩 타임에 생성되므로 멀티스레드에 수반되는 위험이 있음
	// Race condition 방지를 위해 Lock설정
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}
