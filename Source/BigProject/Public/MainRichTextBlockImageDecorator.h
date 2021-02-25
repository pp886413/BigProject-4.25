// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "MainRichTextBlockImageDecorator.generated.h"

UCLASS()
class BIGPROJECT_API UMainRichTextBlockImageDecorator : public URichTextBlockImageDecorator
{
	GENERATED_BODY()
public:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		int Height;
};
