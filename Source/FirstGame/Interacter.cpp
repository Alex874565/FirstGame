// Fill out your copyright notice in the Description page of Project Settings.


#include "Interacter.h"
#include "Engine/World.h"
#include "Misc/OutputDeviceNull.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values for this component's properties
UInteracter::UInteracter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteracter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteracter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotation = GetOwner() -> GetActorRotation();
	FVector Position = GetOwner() -> GetActorLocation();

	FHitResult HitResult;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool HasHit = GetWorld() -> SweepSingleByChannel(HitResult, 
									Position, 
									Position + GetForwardVector() * InteractDistance,
									FQuat::Identity, 
									ECC_GameTraceChannel2,
									Sphere);

	if(HasHit){
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("%s"), *(HitActor -> GetActorNameOrLabel()));
		FOutputDeviceNull ar;
		const FString command = FString::Printf(TEXT("ShowText"));
		HitActor->CallFunctionByNameWithArguments(*command, ar, NULL, true);
	}else{
		FOutputDeviceNull ar;
		this -> GetOwner() -> CallFunctionByNameWithArguments(*FString::Printf(TEXT("HideText")), ar, NULL, true);
	}
}
