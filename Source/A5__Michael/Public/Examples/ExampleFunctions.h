// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleFunctions.generated.h"

UCLASS()
class A5__MICHAEL_API AExampleFunctions : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExampleFunctions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BlueprintCallable();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintImplementableEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BlueprintNativeEvent();
	virtual void BlueprintNativeEvent_Implementation();

	// Pure Function
	UFUNCTION(BlueprintCallable)
	float PureFunction() const;

	// Multiple Returns
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool MultipleReturns(AActor* Actor1, FRotator Rotation, AActor*& Actor2, int32& Index);
};
