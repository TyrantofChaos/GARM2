// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleVariable.h"
#include "../A5__Michael.h"

// Sets default values
AExampleVariable::AExampleVariable() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ClassType = AExampleVariable::StaticClass();

	PointerArray.Add(this);
	PointerArray.Add(nullptr);

	ValueArray.Add(4);
	ValueArray.Add(7);
}
// Called when the game starts or when spawned
void AExampleVariable::BeginPlay() {
	Super::BeginPlay();
	
	// HOW TO BIND
	// Two input params is the object pointer and function pointer
	OnDelegateVariable.AddDynamic(this, &AExampleVariable::ExampleBoundFunction);

	// HOW TO CALL
	OnDelegateVariable.Broadcast(this);
}
// Called every frame
void AExampleVariable::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
void AExampleVariable::ExampleBoundFunction(AActor* Other) {
	UE_LOG(Game, Error, TEXT("Function called by delegate"));
}

