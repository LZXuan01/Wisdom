#include "raylib.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "sound.h"
#include "image.h"
#include "video.h"
#include "effect.h"


Rectangle GoButton = {0};


void InitStartPage()
{
    GoButton = {static_cast<float>(screenWidth * 0.36), static_cast<float>(screenHeight * 0.88), static_cast<float>(screenWidth * 0.28), static_cast<float>(screenHeight * 0.06)};
}

void UpdateStartPage()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition() , GoButton))
    {
        PlaySound(paperSound);
        currentPage = LOGIN;
        IsVideoPlaying = true ;
        StartFadeIn();
    }
}

void DrawGoButton()
{
    DrawRectangleRoundedLinesEx(GoButton, 0.9, 38, 4 / ppi, BLACK);
    DrawTextEx(LBRITE, "Let's go!", {static_cast<float>(static_cast<int>(GoButton.x + GoButton.width / 2 - MeasureTextEx(LBRITE ,"Let's go", 50 / ppi , 0).x / 2)), static_cast<float>(static_cast<int>(GoButton.y + GoButton.height / 2 - 25 / ppi))}, 50 / ppi, 0, FontColor);
}

void DrawStartPage()
{
    ClearBackground(Cream);
    DrawTexture(SnapFingerTexture, screenWidth * 0.08, screenHeight * 0.20, WHITE);
    DrawTextEx(cambriab, "Hello there", {static_cast<float>(screenWidth * 0.21), static_cast<float>(screenHeight * 0.60)}, 150 / ppi, 0, BLACK);
    DrawTextEx(LBRITE, "Everything you need is calm down and enjoy ", {static_cast<float>(screenWidth * 0.12), static_cast<float>(screenHeight * 0.67)}, 45 / ppi, 0, FontColor);
    DrawTextEx(LBRITE, "now flow in the knowledge of river.", {static_cast<float>(screenWidth * 0.12), static_cast<float>(screenHeight * 0.70)}, 45 / ppi, 0, FontColor);
    DrawTextEx(LBRITED, "Beyond", {static_cast<float>(screenWidth * 0.74), static_cast<float>(screenHeight * 0.70)}, 45 / ppi, 0, FontColor);
    DrawTextEx(LBRITED, "The Cosmos", {static_cast<float>(screenWidth * 0.41), static_cast<float>(screenHeight * 0.73)}, 45 / ppi, 0, FontColor);
    DrawGoButton();
    ScreenFadeIn(0.20f);
}