#include "raylib.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "effect.h"
#include "icon.h"
#include "input.h"
#include "navigation.h"

void UpdateAboutPage()
{
    UpdateNavigation();
    UpdateIcon();
}

void DrawAboutPage()
{
    ClearBackground(Cream);

    DrawTextEx(LBRITED, "About", {static_cast<float>(GetScreenWidth() * 0.38), static_cast<float>(GetScreenHeight() * 0.06)}, 100 / ppi, 1, HomeButtonColor);

    std::string halo = "Hi, " + username;
    DrawTextEx(LBRITEDI, halo.c_str(), {static_cast<float>(GetScreenWidth() - MeasureTextEx(LBRITEDI, halo.c_str(), 40 / ppi, 0).x - 20 / ppi), static_cast<float>(GetScreenHeight() * 0.075)}, 40 / ppi, 0, HomeButtonColor);

    DrawHomeIcon();

    const char *version = "Version: 1.0.0";
    const char *description = "An app to record and grow your knowledge.";
    const char *donate = "Donate: Thank you for your support!";
    const char *phone = "Phone: 011-59801085";

    DrawRectangleRounded({GetScreenWidth() * 0.05f , GetScreenHeight() * 0.15f , GetScreenWidth() * 0.90f , GetScreenHeight() * 0.75f } , 0.2f  , 38  , Fade(YELLOW , 0.05f));
    DrawRectangleRoundedLinesEx({GetScreenWidth() * 0.05f, GetScreenHeight() * 0.15f, GetScreenWidth() * 0.90f, GetScreenHeight() * 0.75f}, 0.3f, 38, 3 / ppi, BLACK);
    // 版本
    Vector2 versionSize = MeasureTextEx(LBRITEI, version, 40 / ppi, 1);
    DrawTextEx(LBRITEI, version, {GetScreenWidth() / 2.0f - versionSize.x / 2, screenHeight * 0.25f}, 40 / ppi, 1, DARKGRAY);

    // 简述
    Vector2 descSize = MeasureTextEx(LBRITEI, description, 40 / ppi, 1);
    DrawTextEx(LBRITEI, description, {GetScreenWidth() / 2.0f - descSize.x / 2, screenHeight * 0.35f}, 40 / ppi, 1, DARKGRAY);

    // 捐赠提示
    Vector2 donateSize = MeasureTextEx(LBRITEI, donate, 40 / ppi, 1);
    DrawTextEx(LBRITEI, donate, {GetScreenWidth() / 2.0f - donateSize.x / 2, screenHeight * 0.45f}, 40 / ppi, 1, DARKGRAY);

    // 电话号码
    Vector2 phoneSize = MeasureTextEx(LBRITEI, phone, 40 / ppi, 1);
    DrawTextEx(LBRITEI, phone, {GetScreenWidth() / 2.0f - phoneSize.x / 2, screenHeight * 0.55f}, 40 / ppi, 1, DARKGRAY);

    DrawExitIcon();
    DrawMenuIcon();
    DrawPlayIcon();
    DrawRecordIcon();

    DrawNavigation();

    ScreenFadeIn();
}
