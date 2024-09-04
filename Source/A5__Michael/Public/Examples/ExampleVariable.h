// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "ExampleVariable.generated.h" // Must be the last include and no code can go above this

// Create Delegate Type
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVariableDelegate, AActor*, OtherActor);

UCLASS(Abstract)
class A5__MICHAEL_API AExampleVariable : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExampleVariable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Read Only
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variable|ReadOnly")
	bool VisibleAnywhere;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Variable|ReadOnly")
	uint8 VisibleDefaultsOnly;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Variable|ReadOnly")
	int32 VisibleInstanceOnlyOdd;

	UPROPERTY(VisibleInstanceOnly, Category = "Variable|ReadOnly")
	int64 VisibleInstanceOnly;

	// Read Write
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable|ReadWrite")
	float EditAnywhere;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variable|ReadWrite")
	FName EditDefaultsOnlyOdd;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Variable|ReadWrite")
	FString EditInstanceOnlyOdd;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variable|ReadWrite")
	FText EditDefaultsOnly;
	UPROPERTY(EditInstanceOnly, Category = "Variable|ReadWrite")
	FVector EditInstanceOnly;

	//Class Reference
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variable|ClassReference")
	TSubclassOf<AActor> ClassType;

	// In BP called Event Dispatcher, in code called Delegate
	// This creates an Instance of the delegate class
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Variable)
	FVariableDelegate OnDelegateVariable;

	// Array
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variable|Array")
	TArray<int32> ValueArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variable|Array")
	TArray<UObject *> PointerArray;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void ExampleBoundFunction(AActor* Other);
};
