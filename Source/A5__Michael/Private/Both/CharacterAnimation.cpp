// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds) {
	APawn *Pawn = TryGetPawnOwner();
	if(Pawn) {
		{
			//Is Valid
			Velocity = Pawn->GetVelocity().Size();

			Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		}
	} else {
		// Is Not Valid
		PreviewWindowUpdate();
	}
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation() {
	DebugFireAnimation();
}
