#include "raylib.h"
#include "main.h"
#include "color.h"
#include "font.h"
#include "sound.h"
#include "image.h"
#include "video.h"
#include "icon.h"
#include "input.h"
#include "keyboard.h"
#include "effect.h"
#include "camera.h"
#include "slider.h"
#include "navigation.h"

#include "startpage.h"
#include "loginpage.h"
#include "homepage.h"
#include "knowledgepage.h"
#include "aboutpage.h"
#include "settingpage.h"

#include <iostream>

float screenWidth      ;
float screenHeight     ;
float ppi              ;

ScreenPage currentPage ;
ScreenPage previousPage;

void InitPage() 
{
    #ifdef PLATFORM_ANDROID
        screenWidth = 1080;
        screenHeight = 2400;
        ppi = 1;
    #else
        screenWidth = 247;
        screenHeight = 547;
        ppi = 4.38;
    #endif

    currentPage = LOADING;
    InitColor     ();
    InitIcon      ();
    InitCamera    ();
    InitSliders   ();
    InitKeyboard  ();
    InitNavigation();
    
    InitStartPage    ();
    InitLoginPage    ();
    InitHomePage     ();
    InitKnowledgePage();

}

void DrawLoadingPage()
{
    BeginDrawing();
    ClearBackground(Cream);
    DrawTextEx(LBRITEI  , "Loading ...", {static_cast<float>(screenWidth * 0.75f), static_cast<float>(screenHeight * 0.95f)}, 60 / ppi , 0.9, FontColor);
    DrawTextEx(beautiful, "Knowledge"  , {static_cast<float>(screenWidth * 0.22f), static_cast<float>(screenHeight * 0.42f)}, 200  / ppi , 2, FontColor);
    EndDrawing();
}

void DrawClosePage()
{
    ClearBackground(Cream);
    DrawTextEx(LBRITEI  , "Loading ...", {static_cast<float>(screenWidth * 0.75f), static_cast<float>(screenHeight * 0.95f)}, 60 / ppi, 0.9 , FontColor);
    DrawTextEx(beautiful, "Goodbye"    , {static_cast<float>(screenWidth * 0.25f), static_cast<float>(screenHeight * 0.42f)}, 250 / ppi  , 2, FontColor);
    EndDrawing();
    WaitTime(1.00);
}

void LoadResources()
{
    LoadFontResources();
    DrawLoadingPage();
    LoadImageResources();
    LoadSoundResources();
    LoadVideoResources();
    LoadUserName();

    if (username.empty())
    {
        currentPage = START;
    }
    else
    {
        currentPage = HOME ;
    }
    
}

void UpdatePage()
{
    
    previousPage = currentPage;
    UpdateMusicStream(pureimagination);
    
    if ( currentPage == START )
    {
        UpdateStartPage();
    }
    else if ( currentPage == LOGIN )
    {
        UpdateLoginPage();
    }
    else if ( currentPage == HOME )
    {
        UpdateHomePage ();
    }
    else if ( currentPage == KNOWLEDGE )
    {
        UpdateKnowledgePage();
    }
    else if ( currentPage == ABOUT )
    {
        UpdateAboutPage();
    }
    else if ( currentPage == SETTINGS )
    {
        UpdateSettingPage();
    }

}

void DrawPage()
{
    if ( currentPage == START )
    {
        DrawStartPage();
    }
    else if ( currentPage == LOGIN )
    {
        DrawLoginPage();
    }
    else if ( currentPage == HOME )
    {
        DrawHomePage() ;
    }
    else if ( currentPage == KNOWLEDGE )
    {
        DrawKnowledgePage();
    } 
    else if ( currentPage == ABOUT )
    {
        DrawAboutPage() ;
    }
    else if ( currentPage == SETTINGS )
    {
        DrawSettingPage() ;
    }

}

void UnloadResources()
{
    UnloadFontResources ();
    UnloadSoundResources();
    UnloadImageResources();
    UnloadVideoResources();
}
