// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bStartWithTickEnabled = false;


}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	

}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	rifle->Attack();
}
