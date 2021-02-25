// Fill out your copyright notice in the Description page of Project Settings.

#include "BigProjectGameMode.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ABigProjectGameMode::BeginPlay()
{
	/** For testing */
	DelegateHandle = MultiDelegate.AddUObject(this, &ABigProjectGameMode::PrintHello);
	DelegateHandle = MultiDelegate.AddUObject(this, &ABigProjectGameMode::PrintGoodBye);

	DoSomething(MultiDelegate);
}

void ABigProjectGameMode::SetNavigation(bool AllowAnalog)
{
	auto& SlateApplication = FSlateApplication::Get();
	FNavigationConfig &NavigationConfig = *SlateApplication.GetNavigationConfig();

	NavigationConfig.bAnalogNavigation = AllowAnalog;
}

void ABigProjectGameMode::AttackHitTimeSlow(const float &TimeDilation, const float &WaitDuration)
{
	UGameplayStatics::SetGlobalTimeDilation(this, TimeDilation);
	GetWorld()->GetTimerManager().SetTimer(AttackHitTimeHandle, this, &ABigProjectGameMode::EndAttackHitTimeSlow, WaitDuration, false);
}

void ABigProjectGameMode::EndAttackHitTimeSlow()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1.0f);
}


/** For testing */
void ABigProjectGameMode::PrintHello()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
}
void ABigProjectGameMode::PrintGoodBye()
{
	UE_LOG(LogTemp, Warning, TEXT("GoodBye"));
}
void ABigProjectGameMode::DoSomething(FMultiDelegate & UsedDelegate)
{
	UsedDelegate.Broadcast();
}

