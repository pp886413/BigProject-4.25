#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "GameFramework/SaveGame.h"
#include "Engine/Texture2D.h"
#include "BigProjectGameInstance.generated.h"

class UAudioComponent;

UENUM(BlueprintType)
enum EControllerSelection
{
	Pc = 0		UMETA(DisplayName = "Pc"),
	Ps4			UMETA(DisplayName = "Ps4"),
	Xbox 		UMETA(DisplayName = "Xbox")
};

UCLASS()
class BIGPROJECT_API UBigProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FirstLaunchGame")
		bool FirstOpen;

	UPROPERTY(EditDefaultSonly, BlueprintReadWrite, Category = "LoadingScreenType")
		TSubclassOf<class UUserWidget> LoadingScreenTypeBp;
	
	/** All usedable actor's id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorID")
		TArray<FString> DestroyedActorsName;

	/** Player choosed controller type */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ControllerType")
		TEnumAsByte<EControllerSelection> ControllerSelection;
	
	/** UI key textures */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Texture2D")
		TArray<UTexture2D*> KeyboardTexures;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Texture2D")
		TArray<UTexture2D*> Ps4Textures;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Texture2D")
		TArray<UTexture2D*> XboxTextures;

	/** Game sound magnitude */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Sound")
		float GameMusicMagnitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Sound")
		float GameSoundEffectMagnitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Sound")
		float GameUIMagnitude;

	/** All Scene's sound component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Sound")
		UAudioComponent * SceneSound;

	/** Loading Screen ui widget */
	class UUserWidget * LoadingWidget;

public:

	/** Call when loading map */
	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& MapName);
	
	/** Call when map loading fininsh */
	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	/** Add actor's Name which have been destoryed */
	UFUNCTION(BlueprintCallable, Category = "Actor ID")
		void AddActorsName(const FString& Name);

	/** When load map check ActorsName array contain Name already? if yes. destory it */
	UFUNCTION(BlueprintCallable,Category = "DestoryActor")
		void DestroyActorWhenContainName();

	/** Replace ui image adjust by select controller type */
	UFUNCTION(BlueprintCallable, Category = "ReplaceImage")
		void ReplaceImage(TArray<class UImage*> ReplacedImage, TArray<int>IndexNumbers, FVector2D ImageSize);

private:
	virtual void Init()override;
};
