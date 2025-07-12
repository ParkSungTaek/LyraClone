// Fill out your copyright notice in the Description page of Project Settings.


#include "LyCExperienceManagerComponent.h"

void ULyCExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnLyCExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		/**
		* 아래의 
		*/
		Delegate.Execute(CurrentExperience); 
	}
	else
	{
		/**
		* 참고로, 여러분들은 Delegate 객체를 자세히 살펴보면, 내부적으로 필요한 변수들을 메모리 할당해놓는다:
		* TArray<int> a = {1, 2, 3, 4};
		* delegate_type delegate = [a](){
		*  return a.Num();
		* }
		* a는 delegate_type 내부에 new 로 할당되어 있다. 복사 비용을 낮추기 위해 Move 
		*/
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}
