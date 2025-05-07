#include <vector>
#include <string>
#include "raylib.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "video.h"
#include "sound.h"
#include "icon.h"
#include "effect.h"
#include "navigation.h"

using std::string;
using std::vector;

NavigationbarState navState = NavigationbarState::HIDDEN;
bool IsNavigationShowing = false;

float barX            =     0;
float barWidth        =     0;
float barSlideSpeed   =     0;
int   barOptionHeight =     0;
int   barOptionCount  =     0;
vector<string> barOptionTexts;

Vector2 startTouchPos = {0};
bool isSwiping = false;

void InitNavigation()
{
    barWidth = 0 ;
    barX = -barWidth;
    barSlideSpeed = 0;
    barOptionHeight = 200 / ppi;
    barOptionTexts = {"HOME", "SETTINGS", "ABOUT", "LOGOUT"};
    barOptionCount = barOptionTexts.size();
    IsNavigationShowing = false ;
}

void UpdateOptionClicked()
{
    for (int i = 0; i < barOptionCount; ++i)
    {
        if (navState == NavigationbarState::VISIBLE)
        {
            int buttonY = 0;
            if (i == 3)
            {
                buttonY = screenHeight * 0.90 + 65 / ppi; // 跟 DrawNavigation 对齐
            }
            else
            {
                buttonY = barOptionHeight * i + screenHeight * 0.30;
            }

            if (CheckCollisionPointRec(GetMousePosition(), {barX, (float)buttonY, (float)barWidth, (float)barOptionHeight}))
            {
                navState = NavigationbarState::HIDDEN;
                IsNavigationShowing = false;

                PlaySound(paperSound);

                if (barOptionTexts[i] == "LOGOUT")
                {
                    currentPage = START ;
                }
                if (barOptionTexts[i] == "HOME")
                {
                    currentPage = HOME ;
                }
                if (barOptionTexts[i] == "ABOUT")
                {
                    currentPage = ABOUT ;
                }
                if (barOptionTexts[i] == "SETTINGS")
                {
                    currentPage = SETTINGS ;
                }

                StartFadeIn();

                break;
            }
        }
    }
}

void UpdateNavigation()
{
    barWidth = screenWidth * 0.79; 
    
    if (navState == NavigationbarState::SLIDING_IN)
    {
        barX += barSlideSpeed;

        if (barX >= 0)
        {
            barX = 0;
            navState = NavigationbarState::VISIBLE;
            barSlideSpeed = 100;
            IsVideoPlaying = true ;
        }
    }
    else if (navState == NavigationbarState::SLIDING_OUT)
    {
        barX -= barSlideSpeed;

        if (barX <= -barWidth)
        {
            barX = -barWidth;
            navState = NavigationbarState::HIDDEN;
            barSlideSpeed = 100;
            IsVideoPlaying = false; 
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Rectangle homeArea = homeButton;
        Rectangle outsideBar = {barX + barWidth, 0 , screenWidth - barWidth, screenHeight};

        if (CheckCollisionPointRec(GetMousePosition(), homeArea))
        {
            if (navState == NavigationbarState::HIDDEN)
            {
                IsVideoPlaying = true;
                navState = NavigationbarState::SLIDING_IN;
                IsNavigationShowing = true ;
            }
        }
        else if (navState == NavigationbarState::VISIBLE && CheckCollisionPointRec(GetMousePosition(), outsideBar))
        {
            IsVideoPlaying = false;
            navState = NavigationbarState::SLIDING_OUT;
            IsNavigationShowing = false ;
        }
        else
        {
            UpdateOptionClicked();
        }
    }

    int touches = GetTouchPointCount();

    if (touches > 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 currentTouch = GetTouchPosition(0);
        if (!isSwiping)
        {
            startTouchPos = currentTouch;
            isSwiping = true;
        }
        else
        {
            if (currentTouch.x - startTouchPos.x > 100)
            {
                if (navState == NavigationbarState::HIDDEN)
                {
                    IsVideoPlaying = true;
                    navState = NavigationbarState::SLIDING_IN;
                    barSlideSpeed = 170;
                    IsNavigationShowing = false ;
                }
                isSwiping = false;
            }
        }
    }
    else
    {
        isSwiping = false;
    }
}

void DrawNavigation()
{
    if (navState == NavigationbarState::VISIBLE)
    {

        DrawRectangleRounded({barX, 0, barWidth , screenHeight} , 0.1 , 0 , BLACK);
        DrawLineEx({barX + 100 / ppi, screenHeight * 0.25f}, {barX + 10 + barWidth * 0.80f, screenHeight * 0.25f}, 3 / ppi, DARKGRAY);

        for (int i = 0; i < barOptionCount; ++i)
        {
            if (i == 3)
            {
                DrawTextEx(LBRITE, barOptionTexts[i].c_str(), {barX + 200 / ppi, static_cast<float>(screenHeight * 0.90 + 65 / ppi)}, 65 / ppi, 15 / ppi, Cream);
            }
            else
            {
                int buttonY = barOptionHeight * i + screenHeight * 0.29;
                DrawTextEx(LBRITE, barOptionTexts[i].c_str(), {barX + 200 / ppi, buttonY + 65 / ppi}, 65 / ppi, 15 / ppi, Cream);
            }
        }
        DrawClockVideo();
        }
    else if (navState != NavigationbarState::HIDDEN)
    {


        DrawRectangleRounded({barX, 0, barWidth, screenHeight}, 0.1, 0, BLACK);
        DrawLineEx({barX + 100 / ppi, screenHeight * 0.25f}, {barX + 10 + barWidth * 0.80f, screenHeight * 0.25f}, 3 / ppi, DARKGRAY);

        for (int i = 0; i < barOptionCount; ++i)
        {
            if (i == 3)
            {
                DrawTextEx(LBRITE, barOptionTexts[i].c_str(), {barX + 200 / ppi, static_cast<float>(screenHeight * 0.90 + 65 / ppi)}, 65 / ppi, 15 / ppi, Cream);
            }
            else
            {
                int buttonY = barOptionHeight * i + screenHeight * 0.29;
                DrawTextEx(LBRITE, barOptionTexts[i].c_str(), {barX + 200 / ppi, buttonY + 65 / ppi}, 65 / ppi, 15 / ppi, Cream);
            }
        }
        DrawClockVideo();
    }
    
}
