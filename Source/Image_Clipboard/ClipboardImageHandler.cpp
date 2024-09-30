// Fill out your copyright notice in the Description page of Project Settings.
#include "ClipboardImageHandler.h"
//#include "Misc/Clipboard.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Engine/Texture2D.h"
#include <windows.h>

void AClipboardImageHandler::CopyImageToClipboard(const int32 InSizeX, const int32 InSizeY, const TArray<FColor>& InImageData)
{
    // Create a DIB (Device Independent Bitmap) for Windows clipboard use
    BITMAPINFO BitmapInfo = { 0 };
    BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BitmapInfo.bmiHeader.biWidth = InSizeX;
    BitmapInfo.bmiHeader.biHeight = -InSizeY; // Negative height to indicate top-down DIB
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32; // RGBA
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    // Copy image data into the buffer
    const int32 ImageDataSize = InSizeX * InSizeY * sizeof(FColor);
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, ImageDataSize);
    void* pData = GlobalLock(hMem);
    FMemory::Memcpy(pData, InImageData.GetData(), ImageDataSize);
    GlobalUnlock(hMem);

    // Open the clipboard and set the data
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        SetClipboardData(CF_DIB, hMem);
        CloseClipboard();
    }

    // Clean up
    GlobalFree(hMem);
}