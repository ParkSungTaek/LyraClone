// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LyCGameState.h"
#include "LyraClone/GameModes/LyCExperienceManagerComponent.h"

ALyCGameState::ALyCGameState()
{
	ExperienceManagerComponent = CreateDefaultSubobject<ULyCExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}
