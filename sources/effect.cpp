#include "raylib.h"

bool fadeInActive        = false;
static float fadeOpacity = 1.0f ;

void StartFadeIn()
{
    fadeInActive = true;
    fadeOpacity = 1.0f;
}

void ScreenFadeIn()
{
    if (!fadeInActive)
    {
        return;
    }

    fadeOpacity -= 0.40f * GetFrameTime();

    if (fadeOpacity <= 0.0f)
    {
        fadeOpacity = 0.0f;
        fadeInActive = false;
    }

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, fadeOpacity));
}

void ScreenFadeIn(float fadeSpeed)
{
    if (!fadeInActive) 
    {
        return ;
    }

    fadeOpacity -= fadeSpeed * GetFrameTime();

    if (fadeOpacity <= 0.0f)
    {
        fadeOpacity = 0.0f;
        fadeInActive = false;
    }

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, fadeOpacity));
}
