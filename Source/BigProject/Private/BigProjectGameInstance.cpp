#include "BigProjectGameInstance.h"
#include "Widgets/SWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "BigProjectSaveGame.h"
#include "Components/Image.h"

void UBigProjectGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UBigProjectGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UBigProjectGameInstance::EndLoadingScreen);
}

void UBigProjectGameInstance::BeginLoadingScreen(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreen;

	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreen.MinimumLoadingScreenDisplayTime = 2.0f;
	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	LoadingWidget = CreateWidget<UUserWidget>(this, LoadingScreenTypeBp);
	
	if (LoadingWidget)
	{
		TSharedPtr<SWidget>WidgetPtr = LoadingWidget->TakeWidget();
		LoadingScreen.WidgetLoadingScreen = WidgetPtr;
		
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}
void UBigProjectGameInstance::EndLoadingScreen(UWorld * InLoadedWorld)
{
}

void UBigProjectGameInstance::DestroyActorWhenContainName()
{
	TArray<AActor*> Object;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("CanBeDestoryed"), Object);
	
	if (UGameplayStatics::DoesSaveGameExist("DestroyedActors", 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("DestroyedActors Exist"));

		UBigProjectSaveGame * SaveGameRef = Cast<UBigProjectSaveGame>(UGameplayStatics::LoadGameFromSlot("DestroyedActors", 0));
		
		if (SaveGameRef != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SaveGameRef has ptr"));
			if (SaveGameRef->DestroyedActorName.Num() > 0)
			{
				this->DestroyedActorsName.SetNum(SaveGameRef->DestroyedActorName.Num());
				
				/** Set save game object's DestroyActorName back to self's */
				for (int i = 0; i < SaveGameRef->DestroyedActorName.Num(); i++)
				{
					this->DestroyedActorsName[i] = SaveGameRef->DestroyedActorName[i];
				}

				/** Destroy index's actor */
				for (int j = 0; j < this->DestroyedActorsName.Num(); j++)
				{
					for (int k = 0; k < Object.Num(); k++)
					{
						if (this->DestroyedActorsName[j] == Object[k]->GetName())
						{
							Object[k]->Destroy();
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Array have items"));
						}
					}					
				}
			}
		}		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("DestroyedActors slot Not Exist"));
	}
}
void UBigProjectGameInstance::AddActorsName(const FString& Name)
{
	this->DestroyedActorsName.AddUnique(Name);
}

void UBigProjectGameInstance::ReplaceImage(TArray<UImage*> ReplacedImage, TArray<int>IndexNumbers, FVector2D ImageSize)
{
	switch (ControllerSelection)
	{
		case Pc:
			for (int i = 0; i < IndexNumbers.Num(); i++)
			{
				ReplacedImage[i]->SetBrushFromTexture(KeyboardTexures[IndexNumbers[i]]);
				ReplacedImage[i]->SetBrushSize(ImageSize);
			}
			break;
		case Ps4:
			for (int i = 0; i < IndexNumbers.Num(); i++)
			{
				ReplacedImage[i]->SetBrushFromTexture(Ps4Textures[IndexNumbers[i]]);
				ReplacedImage[i]->SetBrushSize(ImageSize);
			}
			break;
		case Xbox:
			for (int i = 0; i < IndexNumbers.Num(); i++)
			{
				ReplacedImage[i]->SetBrushFromTexture(XboxTextures[IndexNumbers[i]]);
				ReplacedImage[i]->SetBrushSize(ImageSize);
			}
			break;
	}
}

/*void UBigProjectGameInstance::LoadSound()
{
	if (UGameplayStatics::DoesSaveGameExist("Audio", 0))
	{
		UBigProjectSaveGame * SaveGameRef = Cast<UBigProjectSaveGame>(UGameplayStatics::LoadGameFromSlot("Audio", 0));

		GameMusicMagnitude = SaveGameRef->SavedGameMusic;
		GameSoundEffectMagnitude = SaveGameRef->SavedGameSound;
		GameUIMagnitude = SaveGameRef->SavedGameUiSound;
	}
}*/

