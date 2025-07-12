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
	// ������
	ULyCAssetManager();

	// �̱��� �ν��Ͻ��� ��ȯ�ϴ� �Լ�
	static ULyCAssetManager& Get();

	/**
	* UAssetManager's interfaces
	*/
	virtual void StartInitialLoading() final;
	/**
	* �ش� �Լ��� FScopeLogTime�� ������� ������ ���� �Ǵ��� ���� ���
	* - ���� Ŭ���� �ʿ� ������, �˾Ƶθ� ���� �κ��� �ִ�.
	*/
	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/**
	* GetAsset�� ���� �ε����� BP Class�� Object �ε�
	* - �ָ��ؾ� �� �κ��� bKeepInMemoary
	*/
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetsubClass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory);

	//** [THREAD-SAFE] �޸𸮿� �ε��� ���� ĳ�� */ 
	void AddLoadedAsset(const UObject* Asest);

	// GC���ܸ� ���� ĳ�� (���⼭ ������ ���������� GC�� ���������� ��� ���ε�)
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	// Object ���� Locking
	FCriticalSection SyncObject;
};

template <typename AssetType>
static AssetType* ULyCAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemeory)
{
	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		// �ε��� �Ǿ��ִ� -> �ٷ� ������
		// �ε��� �ȵǾ��ִ� -> null
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemeory)
		{
			// ���⼭ AddLoadAsset�� �޸𸮿� �����ϱ� ���� ��ġ��� �����ϸ� ��:
			// - �ѹ� ��ϵǸ� ���� ������ �ʴ��� unload�� ���� ���� (== ĳ��)
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
		// �ε��� �Ǿ��ִ� -> �ٷ� ������
		// �ε��� �ȵǾ��ִ� -> null
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemeory)
		{
			// ���⼭ AddLoadAsset�� �޸𸮿� �����ϱ� ���� ��ġ��� �����ϸ� ��:
			// - �ѹ� ��ϵǸ� ���� ������ �ʴ��� unload�� ���� ���� (== ĳ��)
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}
	return LoadedSubclass;
}