#include "raylib.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "effect.h"
#include "icon.h"
#include "input.h"
#include "navigation.h"

void UpdateSettingPage()
{
    UpdateNavigation();
    UpdateIcon();
}

void DrawSettingPage()
{
    ClearBackground(Cream);

    DrawTextEx(LBRITED, "Settings", {static_cast<float>(GetScreenWidth() * 0.34), static_cast<float>(GetScreenHeight() * 0.06)}, 100 / ppi, 1, HomeButtonColor);

    std::string halo = "Hi, " + username;
    DrawTextEx(LBRITEDI, halo.c_str(), {static_cast<float>(GetScreenWidth() - MeasureTextEx(LBRITEDI, halo.c_str(), 40 / ppi, 0).x - 20 / ppi), static_cast<float>(GetScreenHeight() * 0.075)}, 40 / ppi, 0, HomeButtonColor);

    DrawHomeIcon();

    const char *title1 = "Change Username";
    const char *title2 = "Set Notification";
    const char *title3 = "Privacy Settings";
    const char *title4 = "Language Options";

    const char *subtitle = "Not Available yet";

    DrawRectangleRounded({GetScreenWidth() * 0.05f, GetScreenHeight() * 0.15f, GetScreenWidth() * 0.90f, GetScreenHeight() * 0.75f}, 0.2f, 38, Fade(YELLOW, 0.05f));
    DrawRectangleRoundedLinesEx({GetScreenWidth() * 0.05f, GetScreenHeight() * 0.15f, GetScreenWidth() * 0.90f, GetScreenHeight() * 0.75f}, 0.3f, 38, 3 / ppi, BLACK);

    // 修改用户名
    Vector2 title1Size = MeasureTextEx(LBRITEI, title1, 40 / ppi, 1);
    DrawTextEx(LBRITEI, title1, {GetScreenWidth() / 2.0f - title1Size.x / 2, screenHeight * 0.25f}, 40 / ppi, 1, DARKGRAY);

    Vector2 subtitleSize1 = MeasureTextEx(LBRITEI, subtitle, 30 / ppi, 1);
    DrawTextEx(LBRITEI, subtitle, {GetScreenWidth() / 2.0f - subtitleSize1.x / 2, screenHeight * 0.30f}, 30 / ppi, 1, LIGHTGRAY);

    // 设置通知
    Vector2 title2Size = MeasureTextEx(LBRITEI, title2, 40 / ppi, 1);
    DrawTextEx(LBRITEI, title2, {GetScreenWidth() / 2.0f - title2Size.x / 2, screenHeight * 0.35f}, 40 / ppi, 1, DARKGRAY);

    Vector2 subtitleSize2 = MeasureTextEx(LBRITEI, subtitle, 30 / ppi, 1);
    DrawTextEx(LBRITEI, subtitle, {GetScreenWidth() / 2.0f - subtitleSize2.x / 2, screenHeight * 0.40f}, 30 / ppi, 1, LIGHTGRAY);

    // 隐私设置
    Vector2 title3Size = MeasureTextEx(LBRITEI, title3, 40 / ppi, 1);
    DrawTextEx(LBRITEI, title3, {GetScreenWidth() / 2.0f - title3Size.x / 2, screenHeight * 0.45f}, 40 / ppi, 1, DARKGRAY);

    Vector2 subtitleSize3 = MeasureTextEx(LBRITEI, subtitle, 30 / ppi, 1);
    DrawTextEx(LBRITEI, subtitle, {GetScreenWidth() / 2.0f - subtitleSize3.x / 2, screenHeight * 0.50f}, 30 / ppi, 1, LIGHTGRAY);

    // 语言选项
    Vector2 title4Size = MeasureTextEx(LBRITEI, title4, 40 / ppi, 1);
    DrawTextEx(LBRITEI, title4, {GetScreenWidth() / 2.0f - title4Size.x / 2, screenHeight * 0.55f}, 40 / ppi, 1, DARKGRAY);

    Vector2 subtitleSize4 = MeasureTextEx(LBRITEI, subtitle, 30 / ppi, 1);
    DrawTextEx(LBRITEI, subtitle, {GetScreenWidth() / 2.0f - subtitleSize4.x / 2, screenHeight * 0.60f}, 30 / ppi, 1, LIGHTGRAY);

    DrawExitIcon();
    DrawMenuIcon();
    DrawPlayIcon();
    DrawRecordIcon();

    DrawNavigation();

    ScreenFadeIn();
}
