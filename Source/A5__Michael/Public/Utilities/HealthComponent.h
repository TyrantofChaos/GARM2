// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHurt, float, percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, float, percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeal, float, percent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A5__MICHAEL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION() void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Variables") FOnHurt onHurt;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Variables") FOnDead onDead;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Variables") FOnHeal onHeal;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables") float maxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables") float currentHealth;

	


};
