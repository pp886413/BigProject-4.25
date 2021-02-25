#include "MainRichTextBlockImageDecorator.h"
#include "UObject/SoftObjectPtr.h"
#include "Rendering/DrawElements.h"
#include "Framework/Text/SlateTextRun.h"
#include "Framework/Text/SlateTextLayout.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Framework/Application/SlateApplication.h"
#include "Fonts/FontMeasure.h"
#include "Math/UnrealMathUtility.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SBox.h"
#include "Misc/DefaultValueHelper.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"

class SMainRichInlineImage : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainRichInlineImage)
	{}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const FSlateBrush* Brush, const FTextBlockStyle& TextStyle, TOptional<int32> Width, TOptional<int32> Height, EStretch::Type Stretch)
	{
		if (ensure(Brush))
		{
			int32 IconWidth = 0;
			int32 IconHeight = 0;

			if (Width.IsSet())
			{
				IconWidth = Width.GetValue();
			}

			if (Height.IsSet())
			{
				IconHeight = Height.GetValue();
			}

			ChildSlot
				[
					SNew(SBox)
					.HeightOverride(IconHeight)
				.WidthOverride(IconWidth)
				[
					SNew(SScaleBox)
					.Stretch(Stretch)
				.StretchDirection(EStretchDirection::DownOnly)
				.VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(Brush)
				]
				]
				];
		}
	}
};

class FMainRichInlineImage : public FRichTextDecorator
{
public:
	FMainRichInlineImage(URichTextBlock* InOwner, UMainRichTextBlockImageDecorator* InDecorator, const int& InWidth, const int& InHeight)
		: FRichTextDecorator(InOwner)
		, Decorator(InDecorator), Width(InWidth), Height(InHeight)
	{
	}

	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override
	{
		if (RunParseResult.Name == TEXT("img") && RunParseResult.MetaData.Contains(TEXT("id")))
		{
			const FTextRange& IdRange = RunParseResult.MetaData[TEXT("id")];
			const FString TagId = Text.Mid(IdRange.BeginIndex, IdRange.EndIndex - IdRange.BeginIndex);

			const bool bWarnIfMissing = false;
			return Decorator->FindImageBrush(*TagId, bWarnIfMissing) != nullptr;
		}

		return false;
	}

protected:
	virtual TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& TextStyle) const override
	{
		const bool bWarnIfMissing = true;
		const FSlateBrush* Brush = Decorator->FindImageBrush(*RunInfo.MetaData[TEXT("id")], bWarnIfMissing);

		TOptional<int32> OptionalWidth;
		if (const FString* WidthString = RunInfo.MetaData.Find(TEXT("width")))
		{
			int32 WidthTemp;
			OptionalWidth = FDefaultValueHelper::ParseInt(*WidthString, WidthTemp) ? WidthTemp : TOptional<int32>();
		}

		TOptional<int32> OptionalHeight;
		if (const FString* HeightString = RunInfo.MetaData.Find(TEXT("height")))
		{
			int32 HeightTemp;
			OptionalHeight = FDefaultValueHelper::ParseInt(*HeightString, HeightTemp) ? HeightTemp : TOptional<int32>();
		}

		return SNew(SMainRichInlineImage,
			   Brush,
			   TextStyle,
			   OptionalWidth.IsSet() ? OptionalWidth : Width,
			   OptionalHeight.IsSet() ? OptionalHeight : Height,
			   EStretch::Fill);
	}

private:
	UMainRichTextBlockImageDecorator* Decorator;
	int Width;
	int Height;
};

TSharedPtr<ITextDecorator> UMainRichTextBlockImageDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FMainRichInlineImage(InOwner, this, Width, Height));
}
