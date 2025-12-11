// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		MoveComp = OwnerCharacter->GetCharacterMovement();
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
		if (!OwnerCharacter)
			return;
	}

	if (!MoveComp)
	{
		MoveComp = OwnerCharacter->GetCharacterMovement();
		if (!MoveComp)
			return;
	}

	FVector Velocity = OwnerCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	bIsInAir = MoveComp->IsFalling();

	bIsCrouching = OwnerCharacter->bIsCrouched;

	MovementDirection = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
}
