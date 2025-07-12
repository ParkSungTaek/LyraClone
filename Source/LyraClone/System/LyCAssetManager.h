// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyCAssetManager.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class LYRACLONE_API ULyCAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	// 생성자
	ULyCAssetManager();

	// 싱글톤 인스턴스를 반환하는 함수
	static ULyCAssetManager& Get();

	/**
	* UAssetManager's interfaces
	*/
	virtual void StartInitialLoading() final;
	/**
	* 해당 함수는 FScopeLogTime을 사용할지 않을지 유무 판단을 위해 사용
	* - 굳이 클론할 필요 없지만, 알아두면 좋은 부분이 있다.
	*/
	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/**
	* GetAsset은 정적 로딩으로 BP Class와 Object 로딩
	* - 주목해야 할 부분은 bKeepInMemoary
	*/
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetsubClass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory);

	//** [THREAD-SAFE] 메모리에 로딩된 에셋 캐싱 */ 
	void AddLoadedAsset(const UObject* Asest);

	// GC제외를 위한 캐싱 (여기서 포인터 물고있으면 GC에 안잡히겠지 라는 마인드)
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	// Object 단위 Locking
	FCriticalSection SyncObject;
};

template <typename AssetType>
static AssetType* ULyCAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory)
{
	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		// 로딩이 되어있다 -> 바로 가져옴
		// 로딩이 안되어있다 -> null
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemeory)
		{
			// 여기서 AddLoadAsset은 메모리에 상주하기 위한 장치라고 생각하면 됨:
			// - 한번 등록되면 직접 내리지 않는한 unload가 되지 않음 (== 캐싱)
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}
	return LoadedAsset;
}


template <typename AssetType>
static TSubclassOf<AssetType> ULyCAssetManager::GetsubClass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory)
{
	TSubclassOf<AssetType>* LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();
	if (AssetPath.IsValid())
	{
		// 로딩이 되어있다 -> 바로 가져옴
		// 로딩이 안되어있다 -> null
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemeory)
		{
			// 여기서 AddLoadAsset은 메모리에 상주하기 위한 장치라고 생각하면 됨:
			// - 한번 등록되면 직접 내리지 않는한 unload가 되지 않음 (== 캐싱)
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}
	return LoadedSubclass;
}