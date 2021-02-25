#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BigProjectGameInstance.h"
#include "BigProjectSaveGame.generated.h"

UCLASS()
class BIGPROJECT_API UBigProjectSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DestoryedActor")
		TArray<FString> DestroyedActorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
		TEnumAsByte<EControllerSelection> SavedControllerSelection;
};
