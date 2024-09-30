


#include "ImageTestActor.h"
#include "Windows/WindowsPlatformMisc.h" // For clipboard handling
#include "Windows/AllowWindowsPlatformTypes.h" // Allows Windows types
#include <Windows.h> // This is where OpenClipboard, HBITMAP, etc. are defined
#include "Windows/HideWindowsPlatformTypes.h" // Hides Windows types after usage

// Sets default values
AImageTestActor::AImageTestActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AImageTestActor::BeginPlay()
{
    Super::BeginPlay();

    // Call the test function
    TestCopyImageToClipboard();
}

// Called every frame
void AImageTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to test copying an image to the clipboard
void AImageTestActor::TestCopyImageToClipboard()
{
    // Define the size of the image
    const int32 InSizeX = 256;
    const int32 InSizeY = 256;

    // Create a mock image data array
    TArray<FColor> InImageData;
    InImageData.SetNum(InSizeX * InSizeY);
    //TArray<uint8> ImageDataForClipboard;

    // Fill the array with red color data
    for (int32 i = 0; i < InImageData.Num(); ++i)
    {
        InImageData[i] = FColor::Red; // Fill the image with red pixels
    }

    for (int32 i = 0; i < InImageData.Num(); ++i)
    {
        UE_LOG(LogTemp, Warning, TEXT("Pixel %d: R=%d, G=%d, B=%d, A=%d"),
            i, InImageData[i].R, InImageData[i].G, InImageData[i].B, InImageData[i].A);
    }



    //// Open the clipboard
    //if (OpenClipboard(nullptr))
    //{
    //    // Clear any previous content in the clipboard
    //    EmptyClipboard();

    //    // Prepare the bitmap structure (assume you've created the bitmap properly)
    //    HBITMAP hBitmap = CreateDIBitmap(...); // Properly create the HBITMAP from your pixel data

    //    if (hBitmap != nullptr)
    //    {
    //        // Set the bitmap data in the clipboard
    //        SetClipboardData(CF_BITMAP, hBitmap);
    //    }

    //    // Close the clipboard
    //    CloseClipboard();
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Failed to open clipboard!"));
    //}
    //for (int32 i = 0; i < InImageData.Num(); ++i)
    //{
    //    FColor Pixel = InImageData[i];
    //    uint8 Red = Pixel.R;
    //    uint8 Green = Pixel.G;
    //    uint8 Blue = Pixel.B;
    //    uint8 Alpha = Pixel.A;

    //    // Add to clipboard in BGRA format
    //    ImageDataForClipboard.Add(Blue); // Blue
    //    ImageDataForClipboard.Add(Green); // Green
    //    ImageDataForClipboard.Add(Red);   // Red
    //    ImageDataForClipboard.Add(Alpha); // Alpha
    //}
    // Call the function with the mock data
    AClipboardImageHandler::CopyImageToClipboard(InSizeX, InSizeY, InImageData);
}

//#if PLATFORM_WINDOWS
//void AImageTestActor::CopyImageToClipboard(const int32 InSizeX, const int32 InSizeY, const TArray<FColor>& InImageData)
//{
//    if (OpenClipboard(nullptr))
//    {
//        EmptyClipboard();
//
//        // Assuming your image data is prepared for HBITMAP
//        HDC hdc = GetDC(nullptr);
//        BITMAPINFOHEADER bih = { sizeof(BITMAPINFOHEADER), InSizeX, -InSizeY, 1, 32, BI_RGB }; // Bitmap header setup
//        void* pBits;
//
//        // Create the HBITMAP
//        HBITMAP hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS, &pBits, NULL, 0);
//
//        if (hBitmap && pBits)
//        {
//            // Copy image data to bitmap memory
//            FMemory::Memcpy(pBits, InImageData.GetData(), InImageData.Num() * sizeof(FColor));
//
//            // Place the bitmap into the clipboard
//            SetClipboardData(CF_BITMAP, hBitmap);
//        }
//
//        CloseClipboard();
//        ReleaseDC(nullptr, hdc);
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Failed to open clipboard!"));
//    }
//}
//#endif
#if PLATFORM_WINDOWS
//#include "Windows/AllowWindowsPlatformTypes.h"
//#include <Windows.h>
//#include "Windows/HideWindowsPlatformTypes.h"
//#include "ImageTestActor.h"

void AImageTestActor::CopyImageToClipboard(const int32 InSizeX, const int32 InSizeY, const TArray<FColor>& InImageData)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();

        // Prepare BitmapInfo structure
        BITMAPINFO bmi;
        ZeroMemory(&bmi, sizeof(BITMAPINFO));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = InSizeX;
        bmi.bmiHeader.biHeight = -InSizeY;  // Negative to ensure top-down bitmap
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;  // Assuming 32-bit color (RGBA)
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = InSizeX * InSizeY * 4;

        // Create a device-independent bitmap (DIB)
        void* pBits = nullptr;
        HDC hdc = GetDC(nullptr);
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, nullptr, 0);

        if (hBitmap && pBits)
        {
            // Copy the image data from Unreal's FColor array to the bitmap
            FMemory::Memcpy(pBits, InImageData.GetData(), InImageData.Num() * sizeof(FColor));

            // Set the clipboard data
            SetClipboardData(CF_BITMAP, hBitmap);

            // Clean up
            DeleteObject(hBitmap);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create bitmap!"));
        }

        CloseClipboard();
        ReleaseDC(nullptr, hdc);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to open clipboard!"));
    }
}
#endif