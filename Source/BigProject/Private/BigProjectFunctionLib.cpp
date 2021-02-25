// Fill out your copyright notice in the Description page of Project Settings.
#include "BigProjectFunctionLib.h"
#include "BigProjectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"


void UBigProjectFunctionLib::StartAttackHitTimeSlow(UObject * object, const float &TimeDilation, const float &WaitDuration)
{
	ABigProjectGameMode* GameMode = Cast<ABigProjectGameMode>(UGameplayStatics::GetGameMode(object));

	if (GameMode)
	{
		GameMode->AttackHitTimeSlow(TimeDilation, WaitDuration);
	}
}
float UBigProjectFunctionLib::GetAttackDirection(AActor * Target, AActor * ActorSelf)
{
	FRotator LookedRotation = UKismetMathLibrary::FindLookAtRotation(Target->GetActorLocation(), ActorSelf->GetActorLocation());

	return UKismetMathLibrary::NormalizedDeltaRotator(Target->GetActorRotation(), LookedRotation).Yaw;
}


