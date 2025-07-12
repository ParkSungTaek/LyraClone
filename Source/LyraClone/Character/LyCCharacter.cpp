// Fill out your copyright notice in the Description page of Project Settings.


#include "LyCCharacter.h"

// Sets default values
ALyCCharacter::ALyCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALyCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALyCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALyCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

