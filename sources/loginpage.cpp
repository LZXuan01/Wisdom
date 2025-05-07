#include <string>
#include "raylib.h"
#include "raymath.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "sound.h"
#include "image.h"
#include "video.h"
#include "effect.h"
#include "camera.h"
#include "input.h"
#include "keyboard.h"

#include <iostream>

Rectangle YesButton     = {0};
Rectangle NoButton      = {0};
Rectangle ConfirmButton = {0};


void InitLoginPage()
{
    YesButton     = {static_cast<float>(screenWidth * 0.20), static_cast<float>(screenHeight * 0.65), static_cast<float>(screenWidth * 0.60), static_cast<float>(screenHeight * 0.05)};
    NoButton      = {static_cast<float>(screenWidth * 0.20), static_cast<float>(screenHeight * 0.75), static_cast<float>(screenWidth * 0.60), static_cast<float>(screenHeight * 0.05)};
    ConfirmButton = {static_cast<float>(screenWidth * 0.30), static_cast<float>(screenHeight * 1.00), static_cast<float>(screenWidth * 0.40), static_cast<float>(screenHeight * 0.05)};
}

void UpdateYesButton()
{

    InputUserName();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), YesButton) && !IsCameraActive)  
    {
        PlaySound(anno1801)    ;
        camera.target.y = static_cast<float>(screenHeight * 0.64f);
        camera.zoom     = 1.20f;
        IsCameraActive  = true ;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), YesButton) && IsCameraActive && !IsKeyboardActive )
    {
        PlaySound(anno1803);
        IsKeyboardActive = true;
    }
}

void UpdateNoButton()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), NoButton) && !IsCameraActive) 
    {
        PlaySound(eldenringSound);
        currentPage = CLOSE;
    }
}

void UpdateConfirmButton()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), ConfirmButton) && IsCameraActive && !IsKeyboardActive && username.length()>1) // and the name must be input
    {
        //RemoveEditText();
        PlaySound(milestone);
        ResetCamera();
        currentPage = HOME;
        SaveUserName();
        StartFadeIn();
    }
}

void UpdateLoginPage()
{
    Vector2 mouseScreenPos           = GetMousePosition();                                  
    Vector2 mouseWorldPos            = GetScreenToWorld2D(mouseScreenPos, camera);         
    bool isMouseOverCameraYesButton  = CheckCollisionPointRec(mouseWorldPos, YesButton);     
    bool isMouseOverCameraConfirmBtn = CheckCollisionPointRec(mouseWorldPos, ConfirmButton); 
    bool isMouseOverKeyboard         = CheckCollisionPointRec(mouseWorldPos , {keyboardBackground.x , keyboardBackground.y + 250 / ppi , keyboardBackground.width , keyboardBackground.height});

    if (IsCameraActive && IsKeyboardActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (!isMouseOverCameraYesButton && !isMouseOverCameraConfirmBtn && !isMouseOverKeyboard)
        {
            IsKeyboardActive = false;
            return;
        }
    }
    else if (IsCameraActive && !IsKeyboardActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (!isMouseOverCameraYesButton && !isMouseOverCameraConfirmBtn)
        {
            ResetCamera();
            IsKeyboardActive = false;
            return;
        }
    }
    

    UpdateYesButton();
    UpdateNoButton();
    UpdateConfirmButton();
}

void DrawYesButton()
{
    if (!IsCameraActive)
    {
        DrawTextEx(LBRITE, "The Name Is Mine", {static_cast<float>(static_cast<int>(YesButton.x + YesButton.width / 2 - MeasureText("The Name Is Mine", 50 / ppi) / 2.5)), static_cast<float>(static_cast<int>(YesButton.y + YesButton.height / 2 - 25 / ppi))}, 50 / ppi, 0, FontColor);
        DrawRectangleRoundedLinesEx(YesButton, 0.9, 38, 4 / ppi, BLACK);
    }
    else if (IsCameraActive && !IsKeyboardActive && !username.empty())
    {
        std::string nameLength = std::to_string(username.length())+ "/10" ;
        DrawTextEx (LBRITEDI, username.c_str(), {static_cast<float>(static_cast<int>(YesButton.x + YesButton.width / 2 - MeasureTextEx(LBRITEDI, username.c_str(), 40 / ppi , 0).x / 2.5)), static_cast<float>(static_cast<int>(YesButton.y + YesButton.height / 2 - 25 / ppi))}, 40 / ppi, 0, FontColor);
        DrawTextEx (LBRITEDI, nameLength.c_str(), {static_cast<float>(static_cast<int>(YesButton.x + YesButton.width * 0.94f - MeasureTextEx(LBRITEI,"1/10", 35 / ppi , 0).x)), static_cast<float>(static_cast<int>(YesButton.y + YesButton.height * 0.12f + 25 / ppi))}, 35 / ppi, 0, FontColor);
        if (username.length() > 3)
        {
            DrawTexture(correctTexture , static_cast<int>(screenWidth * 0.835), static_cast<float>(screenHeight * 0.663), WHITE);
        }
        DrawTexture(quillTexture, static_cast<int>(screenWidth * 0.23), static_cast<float>(screenHeight * 0.66), WHITE);
        DrawLine(YesButton.x, YesButton.y + YesButton.height, YesButton.x + YesButton.width, YesButton.y + YesButton.height, BLACK);
    }
    else if (IsCameraActive && !IsKeyboardActive && username.empty())
    {
        DrawTextEx (LBRITEDI, "Tap to sign here", {static_cast<float>(static_cast<int>(YesButton.x + YesButton.width / 2 - MeasureText("Tap to sign here", 40 / ppi) / 2.5)), static_cast<float>(static_cast<int>(YesButton.y + YesButton.height / 2 - 25 / ppi))}, 40 / ppi, 0, FontColor);
        DrawTexture(quillTexture, static_cast<int>(screenWidth * 0.23), static_cast<float>(screenHeight * 0.66), WHITE);
        DrawLine   (YesButton.x, YesButton.y + YesButton.height, YesButton.x + YesButton.width, YesButton.y + YesButton.height, BLACK);    
    }
    else if (IsCameraActive && IsKeyboardActive ) 
    {
        std::string nameWithCursor = username;
        if (fmod(GetTime(), 0.9f) < 0.45f)
        {
            nameWithCursor += "_";
        }
        std::string nameLength = std::to_string(username.length())+ "/10" ;
        DrawTextEx(LBRITEDI, nameWithCursor.c_str(), {static_cast<float>(static_cast<int>(YesButton.x + YesButton.width / 2 - MeasureTextEx(LBRITEDI , username.c_str(), 40 / ppi , 0).x / 2)), static_cast<float>(static_cast<int>(YesButton.y + YesButton.height / 2 - 25 / ppi))}, 40 / ppi, 0, FontColor);
        DrawTextEx(LBRITEDI, nameLength.c_str(), {static_cast<float>(static_cast<int>(YesButton.x + YesButton.width * 0.94f - MeasureTextEx(LBRITEDI , "1/10", 35 / ppi , 0).x)), static_cast<float>(static_cast<int>(YesButton.y + YesButton.height * 0.12f + 25 / ppi))}, 35 / ppi, 0, FontColor);
        DrawLine(YesButton.x, YesButton.y + YesButton.height, YesButton.x + YesButton.width, YesButton.y + YesButton.height, BLACK);
        if (username.length()>2)
        {
            DrawTexture(correctTexture , static_cast<int>(screenWidth * 0.835), static_cast<float>(screenHeight * 0.663), WHITE);
        }
        DrawTexture(quillTexture, static_cast<int>(screenWidth * 0.23), static_cast<float>(screenHeight * 0.66), WHITE);
    }
}

void DrawNoButton()
{
    if (!IsCameraActive)
    {
        DrawTextEx(LBRITE, "Remain Silent", {static_cast<float>(static_cast<int>(NoButton.x + NoButton.width / 2 - MeasureText("Remain Silent", 50 / ppi) / 2.5)), static_cast<float>(static_cast<int>(NoButton.y + NoButton.height / 2 - 25 / ppi))}, 50 / ppi, 0, FontColor);
        DrawRectangleRoundedLinesEx(NoButton, 0.9, 38, 4 / ppi, BLACK);
    }
}

void DrawConfirmButton()
{
    if (IsCameraActive && !IsKeyboardActive && username.length()>2)
    {
        DrawRectangleRoundedLinesEx(ConfirmButton, 0.9, 38 , 3/ppi , FontColor);
        DrawTextEx(LBRITED, "CONFIRM", {static_cast<float>(static_cast<int>(ConfirmButton.x + ConfirmButton.width / 2 - MeasureTextEx(LBRITED,"CONFIRM", 40 / ppi , 0).x / 2)), static_cast<float>(static_cast<int>(ConfirmButton.y + ConfirmButton.height / 2 - MeasureTextEx(LBRITED,"CONFIRM",40/ppi ,0).y/2))}, 40 / ppi, 0, FontColor);
    }
}

void DrawLoginPage()
{
    BeginMode2D(camera);
    ClearBackground(Cream);

    DrawCoffeeVideo();
    DrawTextEx(LBRITED, "Welcome"                                          , {static_cast<float>(screenWidth * 0.25), static_cast<float>(screenHeight * 0.45)}, 140/ ppi, 0, FontColor);
    DrawTextEx(LBRITE , "First things first , Every journey begins with a ", {static_cast<float>(screenWidth * 0.12), static_cast<float>(screenHeight * 0.53)}, 45 / ppi, 0, FontColor);
    DrawTextEx(LBRITE , "name . A name holds its power."                   , {static_cast<float>(screenWidth * 0.08), static_cast<float>(screenHeight * 0.56)}, 45 / ppi, 0, FontColor);
    DrawTextEx(LBRITED, "Whisper yours to"                                 , {static_cast<float>(screenWidth * 0.62), static_cast<float>(screenHeight * 0.56)}, 45 / ppi, 0, FontColor);
    DrawTextEx(LBRITED, "me"                                               , {static_cast<float>(screenWidth * 0.48), static_cast<float>(screenHeight * 0.59)}, 45 / ppi, 0, FontColor);

    DrawYesButton();
    DrawNoButton();
    DrawConfirmButton();

    EndMode2D();
    DrawKeyboard();
    ScreenFadeIn();
}