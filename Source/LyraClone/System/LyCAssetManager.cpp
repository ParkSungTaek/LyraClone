// Fill out your copyright notice in the Description page of Project Settings.


#include "LyCAssetManager.h"
#include "LyraClone/LyCLogChannels.h"

ULyCAssetManager::ULyCAssetManager()
{
}

ULyCAssetManager& ULyCAssetManager::Get()
{
	check(GEngine);

	// �츮�� AssetManager�� UEngine�� GEngine�� AssetManager�� class�� �������̵� �߱� ������, GEngine�� AssetManager�� ����
	if(ULyCAssetManager* Singleton = Cast<ULyCAssetManager>(GEngine -> AssetManager))
	{ 
		return *Singleton;
	}

	// ���� GEngine�� AssetManager�� ULyCAssetManager Ÿ���� �ƴ϶��, Fatal ������ �߻���Ŵ
	UE_LOG(LogLyC, Fatal, TEXT("invalid AssetManagerClassname in DefaultEngine.ini (project setting) it must be LyCAssetManager"));

	return *NewObject<ULyCAssetManager>();
}

PRAGMA_DISABLE_OPTIMIZATION
void ULyCAssetManager::StartInitialLoading()
{
	// ����� ��ƺ� ��� - ���� �𸮾��� �����⵵ �� �ε� Ÿ�ӿ� �Ͼ��.
	// �𸮾��� ������ �� �ε� Ÿ�ӿ��� �𸮾��� ��Ƽ������� �����ϸ� ���������� �������� ��������ʴ´�. 
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
/// ����� �ε� 
/// ����� �ε��� ���� : �񵿱�ĺ��� �Լ��� �ӵ��� ������. ������ �����ϸ� �������̴�.  
/// ����� �ε��� ���� : ���� ������ �ε��� ���� ������ �� �ִ�.
/// �ո��� ���ó : ���� ���� ��, "�ε�Ÿ��"�� ������ ���۵Ǳ� ���� �ݵ�� �ʿ��� ���ҽ��� (��: UI, HUD ��) �� �ε��� �� ����Ѵ�.
/// 
/// �ΰ��ӿ��� ���� ����ϸ� ������ ����� �߻��� �� �����Ƿ�, �ΰ��ӿ��� ���� ������� �ʴ� ���� ����.
/// </summary>
/// <param name="AssetPath"></param>
/// <returns></returns>
UObject* ULyCAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// �ش� �Լ��� ���� ���� ������ 'synchronous load asset �� ���ʿ��ϰ� �ϴ� ���� ������ Ȯ���ϱ� ����'
	if (AssetPath.IsValid())
	{
		// FScopeLogTime�� Ȯ���غ���.
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads()) // LogAssetLoads �� �ѱ�� Ȯ���غ�����
		{
			// �ܼ��� �α��ϸ鼭, �ʴ����� �α� ����
			// �� �Լ��� �󸶳� �ɷȴ��� Ȯ�ΰ���
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		// ���⼭ �ΰ��� �б� : 
		// 1. AssetManager�� ������, AssetManager�� StreamableManager�� ���� ���� �ε�
		// 2. �ƴϸ�, FSoftObjectPath�� ���� �ٷ� ���� �ε�
		if (UAssetManager::IsValid())
		{
			// GetStreamableManager ����,�񵿱� �ε��� �����ϴ� �Ŵ���
			// LoadSynchronous ��¥ �ε� ����
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// if asset manager is not ready, use LoadObject()
		// - �� ����, StaticLoadObject �� ���δ�. 
		// - �����, �׻� StaticLoadObject�ϱ� ���� StaticFindObject�� ���� Ȯ���ϰ� �����ϸ� ��¥ �ε���
		return AssetPath.TryLoad(); // - �ſ� ������ �������ϸ� ��������, UAssetManager �� �������� 

		// �߰�
		// �� �Լ��� AssetPath.TryLoad() �� UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath); ��
		// �̹� �ε��� �Ǿ������� �ε� �Ǿ��ִ� �� ������ �´�. ���� �߰� �ε����� ����
		// �� �Լ��� ���Ǵ� ����ε����� �ð��� ����Ǵ°� �α׷� Ȯ���ϰ� �; ���� ���� �ε��� ����
		
		// FSoftObjectPath �� ���������ġ�� ����ִ� ���µ��� ��θ� ��� ���� (�޸𸮿� �ȿö�� ���µ��� ��ΰ� �ʿ� �װ� ����ϴ°� FSoftObjectPath)
		// ���� ��� ctrl + c �ϰ� ctrl + v�ؼ� ������ �� �н��� ����ִ� ����ڰ� FSoftObjectPath �ΰ�
	}
	return nullptr;
}

void ULyCAssetManager::AddLoadedAsset(const UObject* Asset)
{
	// AssetManager �� �⺻������ �𸮾� ���۽� �ε� Ÿ�ӿ� �����ǹǷ� ��Ƽ�����忡 ���ݵǴ� ������ ����
	// Race condition ������ ���� Lock����
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}
