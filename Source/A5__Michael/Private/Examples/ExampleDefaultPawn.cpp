// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleDefaultPawn.h"
#include "../A5__Michael.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
AExampleDefaultPawn::AExampleDefaultPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AExampleDefaultPawn::BeginPlay() {
	Super::BeginPlay();

	// Upcast
	AActor* Actor = this;

	// Downcast
	APawn* Pawn = Cast<APawn>(Actor);
	if(Pawn) {
		// Valid
		UE_LOG(Game, Warning, TEXT("Actor is %s"), *Pawn->GetName());
	} else {
		// Not Valid
		UE_LOG(Game, Log, TEXT("Numbers are %f and %d"), 7.4f, 3);
	}
	UE_LOG(Game, Error, TEXT("Velocity is %s"), *GetVelocity().ToString());

	UE_LOG(Game, Log, TEXT("IT is %s"), true ? TEXT("TRUE") : TEXT("FALSE"));
}
// Called every frame
void AExampleDefaultPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void AExampleDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Don;t need for this class
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("TEST_Spawn", EKeys::SpaceBar));

	//How to do Action Mapping
	PlayerInputComponent->BindAction("TEST_Spawn", EInputEvent::IE_Pressed, this, &AExampleDefaultPawn::Spawn);

}
void AExampleDefaultPawn::Spawn() {
	FActorSpawnParameters Params;
	Params.Instigator = this;
	GetWorld()->SpawnActor<AActor>(SpawnBlueprintClass, GetActorTransform(), Params);
}