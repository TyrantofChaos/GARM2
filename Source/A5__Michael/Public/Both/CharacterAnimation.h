// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 *
 */
UCLASS()
class A5__MICHAEL_API UCharacterAnimation : public UAnimInstance {
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Velocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Direction;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();

	//*****************************************************************************
	// These functions get events out of the event graph. All the logic should go in PreviewWindowUpdate
	//*****************************************************************************
	UFUNCTION(BlueprintImplementableEvent, Category = "ShouldBeInCode|PutLogicInPreviewWindowUpdate")
	bool DebugFireAnimation();
	UFUNCTION(BlueprintImplementableEvent, Category = "ShouldBeInCode|PutLogicInPreviewWindowUpdate")
	bool DebugHitAnimation();
	UFUNCTION(BlueprintImplementableEvent, Category = "ShouldBeInCode|PutLogicInPreviewWindowUpdate")
	bool DebugDeathAnimation();
	//*****************************************************************************
	// These functions get events out of the event graph. All the logic should go in PreviewWindowUpdate
	//*****************************************************************************
};
