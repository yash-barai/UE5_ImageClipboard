// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClipboardImageHandler.generated.h"

UCLASS()
class IMAGE_CLIPBOARD_API AClipboardImageHandler : public AActor
{
    GENERATED_BODY()

public:
    // Function to copy the image to the clipboard
    static void CopyImageToClipboard(const int32 InSizeX, const int32 InSizeY, const TArray<FColor>& InImageData);
};
