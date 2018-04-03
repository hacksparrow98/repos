// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandlerComponent();
	AttachInputComponent();
}

void UGrabber::FindPhysicsHandlerComponent(void)
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle for %s not found"), *GetOwner()->GetName());
	}
}

void UGrabber::AttachInputComponent(void)
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component for %s not found"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab(void)
{
	auto HitResult=GetHitBody();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
		//attach physics body
	if(ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ActorHit->GetActorLocation(),
			ActorHit->GetActorRotation()
		);
	}	
}

void UGrabber::Release(void)
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();//release physics body
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

const FHitResult UGrabber::GetHitBody(void)
{
	//Defining collision params
	FHitResult Hit;
	FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());

	//Tracing the generated Line
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetPlayerVPLocation(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		QueryParams
	);
	return Hit;
}

const FVector UGrabber::GetLineTraceEnd(void)
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerVPLocation, PlayerVPRotation);
	return PlayerVPLocation + PlayerVPRotation.Vector()*Reach;
}

const FVector UGrabber::GetPlayerVPLocation(void)
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerVPLocation, PlayerVPRotation);
	return PlayerVPLocation;
}

