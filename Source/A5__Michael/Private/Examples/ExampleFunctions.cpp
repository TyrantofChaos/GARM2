// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleFunctions.h"
#include "../A5__Michael.h"

// Sets default values
AExampleFunctions::AExampleFunctions() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AExampleFunctions::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(Game, Warning, TEXT("STARTING calling BlueprintNativeEvent_Implementation"));
	BlueprintNativeEvent_Implementation();
	UE_LOG(Game, Warning, TEXT("STARTING calling BlueprintNativeEvent"));
	BlueprintNativeEvent();
	UE_LOG(Game, Warning, TEXT("Finsihed Begin Play"));
}
void AExampleFunctions::BlueprintCallable() {
	UE_LOG(Game, Error, TEXT("In C++ BlueprintCallable"));
}
//void AExampleFunctions::BlueprintImplementableEvent() {
//	UE_LOG(Game, Error, TEXT("In C++ BlueprintImplementableEvent"));
//}
void AExampleFunctions::BlueprintNativeEvent_Implementation() {
	UE_LOG(Game, Warning, TEXT("In C++ BlueprintNativeEvent"));
}

float AExampleFunctions::PureFunction() const {
	return 5.43f;
}
