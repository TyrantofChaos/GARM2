// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadNow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEnded);

/**
 *
 */
UCLASS()
class A5__MICHAEL_API UCharacterAnimation : public UAnimInstance 
{

	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Declare Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnReloadEnded onReloadEnded;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnReloadNow onReloadNow;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events") FOnDeathEnded onDeathEnded;

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) bool isAttacking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Velocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Direction;

	// Fire
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) UAnimSequenceBase* FireAsset;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) bool DebugFire = true;

	// Hurt
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) UAnimSequenceBase* HurtAsset;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) bool DebugHurt = true;

	// Reload
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) UAnimSequenceBase* ReloadAsset;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) bool DebugReload = true;

	//Dead
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) UAnimSequenceBase* DeadAsset;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) TArray<UAnimSequenceBase*> DeadAssets;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) bool DebugDead = true;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default) FName SlotNodeName;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) 
	void PreviewWindowUpdate(); // Don't Create this
	virtual void PreviewWindowUpdate_Implementation();

public:

	UFUNCTION(BlueprintCallable) void FireAnimation();
	UFUNCTION(BlueprintCallable) void HurtAnimation(float Unused);
	UFUNCTION(BlueprintCallable) void DeathAnimation(float Unused);
	UFUNCTION(BlueprintCallable) virtual void DeathAnimation_Implementation();
	UFUNCTION(BlueprintCallable) void ReloadAnimation();
	UFUNCTION(BlueprintCallable) void AnimNotify_BP_ReloadEnd();
	UFUNCTION(BlueprintCallable) void AnimNotify_BP_ReloadNow();
};
