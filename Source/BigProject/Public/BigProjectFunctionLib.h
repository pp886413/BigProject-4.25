// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BigProjectFunctionLib.generated.h"

class AActor;

UCLASS()
class BIGPROJECT_API UBigProjectFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Slow time to increase hit feeling */
	UFUNCTION(BlueprintCallable, Category = "Attack Hit Time Slow")
		static void StartAttackHitTimeSlow(UObject * object, const float &TimeDilation, const float &WaitDuration);
	/** Get attack direction base on two of them's location */
	UFUNCTION(BlueprintCallable, Category = "Attack Direction")
		static float GetAttackDirection(AActor * Target, AActor * ActorSelf);
	
};
