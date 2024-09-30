#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClipboardImageHandler.h" // Include your handler header
#include "ImageTestActor.generated.h"

UCLASS()
class IMAGE_CLIPBOARD_API AImageTestActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AImageTestActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void CopyImageToClipboard(const int32 InSizeX, const int32 InSizeY, const TArray<FColor>& InImageData);

    void TestCopyImageToClipboard(); // Function to run the test
};