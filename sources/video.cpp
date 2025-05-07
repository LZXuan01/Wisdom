// 使用video is playing 来操控video是否需要被绘制

#include "raylib.h"
#include "main.h"
#include "navigation.h"

int coffeeVideoWidth    = 800;
int coffeeVideoHeight   = 800;
int MyClockVideoWidth   = 180;
int MyClockVideoHeight  = 180;
int coffeeVideoFileSize = 0  ;
int clockVideoFileSize  = 0  ;


bool IsVideoPlaying = false;

unsigned char *coffeBuffer    = nullptr;
unsigned char *coffee         = nullptr;
unsigned char *MyClockBuffer    = nullptr;
unsigned char *MyClock          = nullptr;

Texture2D coffeeTexture;
Texture2D MyClockTexture ;

void LoadVideoResources()
{
    coffee = LoadFileData("video/coffee.raw", &coffeeVideoFileSize);
    MyClock  = LoadFileData("video/clock.raw",&clockVideoFileSize);

    if (coffee == nullptr)
    {
        coffee = LoadFileData("../assets/video/coffeeVScode.raw", &coffeeVideoFileSize);
        coffeeVideoWidth  = 182;
        coffeeVideoHeight = 182;
    }

    if (MyClock == nullptr)
    {
        MyClock = LoadFileData("../assets/video/clockVScode.raw",&clockVideoFileSize);
        MyClockVideoWidth = 64 ;
        MyClockVideoHeight= 64 ;

    }

    coffeBuffer = new unsigned char[coffeeVideoWidth * coffeeVideoHeight * 4];
    MyClockBuffer = new unsigned char[MyClockVideoWidth * MyClockVideoHeight * 4];

    Image coffeeImage =
    {
        .data = coffeBuffer,
        .width = coffeeVideoWidth,
        .height = coffeeVideoHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    Image MyClockImage = 
    {
        .data = MyClockBuffer,
        .width = MyClockVideoWidth,
        .height = MyClockVideoHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };


    coffeeTexture = LoadTextureFromImage(coffeeImage);
    MyClockTexture  = LoadTextureFromImage(MyClockImage);
}

void UnloadVideoResources()
{
    if (coffeBuffer)
    {
        delete[] coffeBuffer;
        coffeBuffer = nullptr;
    }

    if (MyClockBuffer)
    {
        delete[] MyClockBuffer;
        MyClockBuffer = nullptr;
    }

    if (coffee)
    {
        UnloadFileData(coffee);
        coffee = nullptr;
    }

    if (MyClock)
    {
        UnloadFileData(MyClock);
        MyClock = nullptr;
    }

    UnloadTexture(coffeeTexture);
    UnloadTexture(MyClockTexture) ;
}

void DrawCoffeeVideo()
{
    if (IsVideoPlaying && coffee != nullptr)
    {
        static int framePos = 0;
        int frameSize = coffeeVideoWidth * coffeeVideoHeight * 4;

        // Ensure we don’t exceed the bounds of the loaded video data
        if (framePos + frameSize > coffeeVideoFileSize)
        {
            framePos = 0; // Loop back to start if we reach the end of the file
        }

        // Copy frame data to coffeBuffer
        for (int i = 0; i < frameSize; ++i)
        {
            coffeBuffer[i] = coffee[framePos + i];
        }

        // Update the texture with new frame data
        UpdateTexture(coffeeTexture, coffeBuffer);
        DrawTexture  (coffeeTexture, static_cast<int>(GetScreenWidth() * 0.12), static_cast<int>(GetScreenHeight() * 0.08), WHITE);

        // Move to the next frame
        framePos += frameSize;
    }
}

void DrawClockVideo()
{
    if (IsVideoPlaying && MyClock != nullptr)
    {
        static int framePos = 0;
        int frameSize = MyClockVideoWidth * MyClockVideoHeight * 4;

        // Ensure we don’t exceed the bounds of the loaded video data
        if (framePos + frameSize > clockVideoFileSize)
        {
            framePos = 0; // Loop back to start if we reach the end of the file
        }

        // Copy frame data to coffeBuffer
        for (int i = 0; i < frameSize; ++i)
        {
            MyClockBuffer[i] = MyClock[framePos + i];
        }

        // Update the texture with new frame data
        UpdateTexture(MyClockTexture, MyClockBuffer);
        DrawTexture(MyClockTexture, static_cast<int>(barX + 320 / ppi ), static_cast<int>(GetScreenHeight() * 0.12), WHITE);

        // Move to the next frame
        framePos += frameSize;
    }
}
