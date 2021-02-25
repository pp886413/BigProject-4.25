// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BigProjectGameMode.generated.h"

class FDelegateHandle;

UCLASS()
class BIGPROJECT_API ABigProjectGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE(FMultiDelegate)

	/** For testing */
	FMultiDelegate MultiDelegate;
	FDelegateHandle DelegateHandle;

	/* Override base game pad analog control */
	UFUNCTION(BlueprintCallable,Category = "SetNavigation")
	void SetNavigation(bool AllowAnalog);
	
	/** Slow time when attack hit */
	void AttackHitTimeSlow(const float &TimeDilation,const float &WaitDuration);
	
	/** Return time speed to normal speed*/
	void EndAttackHitTimeSlow();
	
	void PrintHello();
	void PrintGoodBye();
	void DoSomething(FMultiDelegate & UsedDelegate);

private:
	FTimerHandle AttackHitTimeHandle;

	virtual void BeginPlay();

};
