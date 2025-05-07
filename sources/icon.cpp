#include <string>
#include "raylib.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "sound.h"
#include <homepage.h>
#include "navigation.h"


Rectangle homeButton     = {0};       
Rectangle documentButton = {0};  
Rectangle exitButton     = {0};
Rectangle menuButton     = {0};
Rectangle playButton     = {0};
Rectangle recordButton   = {0};
bool  IsSongPlaying  = false ;



void InitIcon()
{
    homeButton     = { screenWidth * 0.02f , screenHeight * 0.05f , screenWidth * 0.10f , screenHeight * 0.07f};                // 圆形按钮区域（x, y, width, height）
    documentButton = { screenWidth * 0.47f , screenHeight * 0.07f , screenWidth * 0.05f , screenHeight * 0.025f};               // 文档按钮区域
    exitButton     = { screenWidth * 0.02f , screenHeight - screenHeight * 0.10f , screenWidth * 0.10f , screenHeight * 0.07f }; // Exit button
    menuButton     = { screenWidth * 0.12f , screenHeight - screenHeight * 0.10f , screenWidth * 0.10f , screenHeight * 0.07f }; // Menu button
    playButton     = { screenWidth * 0.46f , screenHeight - screenHeight * 0.10f , screenWidth * 0.10f , screenHeight * 0.07f }; // Play button
    recordButton   = { screenWidth * 0.84f , screenHeight - screenHeight * 0.10f , screenWidth * 0.10f , screenHeight * 0.07f }; // Record button
}

void UpdateIcon()
{
    if ((CheckCollisionPointRec(GetMousePosition() , exitButton) || CheckCollisionPointRec(GetMousePosition() , menuButton)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsNavigationShowing)
    {
        PlaySound(eldenringSound);
        currentPage = CLOSE ;
    }

    if (CheckCollisionPointRec(GetMousePosition() , playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsNavigationShowing)
    {
        if (!IsMusicStreamPlaying(pureimagination))
        {
            ResumeMusicStream(pureimagination); // 如果音乐暂停，就继续播放
            PlayMusicStream(pureimagination);   // 如果从未播放过，就播放
            IsSongPlaying = true ;
        }
        else
        {
            PauseMusicStream(pureimagination);  // 正在播放就暂停
            IsSongPlaying = false;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition() , recordButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsNavigationShowing)
    {
        PlaySound(screenshotSound);
        KnowledgeGroup.clear();
        WaitTime(0.3f);
    }
}

void DrawHomeIcon() 
{
    int centerX = homeButton.x + homeButton.width / 2;
    int centerY = homeButton.y + homeButton.height / 2;
    int radius = homeButton.width / 2;

    DrawCircle(centerX, centerY, radius, HomeButtonColor);

    // 缩放比例
    float scale = 0.85f;

    // ↑↑ 向上偏移量
    float verticalOffset = -radius * 0.10f;

    // 屋顶（三角形）——向上偏移
    float roofSizeFactor = 0.85f;
    Vector2 roof[3] = 
    {
        { centerX - radius * 0.5f * roofSizeFactor, static_cast<float>(centerY) + verticalOffset },
        { centerX + radius * 0.5f * roofSizeFactor, static_cast<float>(centerY) + verticalOffset },
        { static_cast<float>(centerX), centerY - radius * 0.5f * roofSizeFactor + verticalOffset }
    };
    DrawTriangle(roof[0], roof[1], roof[2], RAYWHITE);

    // 房体（带圆角矩形）——向上偏移
    float houseWidth = radius * 1.0f * scale;
    float houseHeight = radius * 0.7f * scale;
    float houseX = centerX - houseWidth / 2;
    float houseY = centerY - houseHeight / 2 + radius * 0.3f * scale + verticalOffset;
    DrawRectangleRounded({houseX , houseY, houseWidth, houseHeight}, 0.4f, 38, RAYWHITE);

    // 小门 —— 同样上移
    DrawRectangleRounded(
        { houseX + houseWidth / 3.2f, houseY + houseHeight * 0.20f, houseWidth * 0.40f, houseHeight * 0.90f },
        0.4f, 38, HomeButtonColor
    );
}

void DrawDocumentIcon() 
{
    // 外框
    DrawRectangleRoundedLinesEx(documentButton, 0.4f, 38, 4.5f / ppi, BLACK);

    // 行高、间隔与边距
    int padding = 9 / ppi;
    int lineSpacing = 12 / ppi;
    float lineThickness = 4.5f / ppi;

    // 更靠近边界：设置左右边距小一些
    float startX = documentButton.x + padding;
    float endX_long = documentButton.x + documentButton.width - padding;
    float endX_short = startX + (endX_long - startX) * 0.4f;  // 短线：60% 长度

    float startY = documentButton.y + padding;

    // 前 3 条长线
    for (int i = 0; i < 3; i++)
    {
        float y = startY + i * lineSpacing;
        DrawLineEx({startX, y}, {endX_long, y}, lineThickness, BLACK);
    }

    // 第 4 条短线，位于稍下方
    float y_last = startY + 3 * lineSpacing;
    DrawLineEx({startX, y_last}, {endX_short, y_last}, lineThickness, BLACK);
}

void DrawExitIcon()
{
    Vector2 center = { exitButton.x + exitButton.width / 2, exitButton.y + exitButton.height / 2 };
    float size = exitButton.width * 0.25f;

    DrawLineEx({center.x + size, center.y - size}, {center.x - size, center.y}, 8 / ppi, DARKGRAY);
    DrawLineEx({center.x + size, center.y + size}, {center.x - size, center.y}, 8 / ppi, DARKGRAY);
}

void DrawMenuIcon()
{
    Vector2 center = { menuButton.x + menuButton.width / 2, menuButton.y + menuButton.height / 2 };
    float width = menuButton.width * 0.6f;
    float height = menuButton.height * 0.05f;
        
    DrawRectangle(center.x - width / 2  ,  center.y + -1 * menuButton.height * 0.13f - height / 2, width, height, DARKGRAY);
    DrawRectangle(center.x - width / 2 + 20 /ppi,  center.y + 0 * menuButton.height * 0.13f - height / 2, width, height, DARKGRAY);
    DrawRectangle(center.x - width / 2 - 10/ppi,  center.y + 1 * menuButton.height * 0.13f - height / 2, width, height, DARKGRAY);

}

void DrawPlayIcon()
{
    Vector2 center = { playButton.x + playButton.width / 2, playButton.y + playButton.height / 2 };
    float size = playButton.width * 0.3f;

    if (!IsSongPlaying)
    {
        // 播放图标(三角形)
        DrawTriangle( { center.x - size, center.y - size }, { center.x - size, center.y + size }, { center.x + size, center.y }, HomeButtonColor );
    }
    else
    {
        // 暂停图标(两条竖线)
        float barWidth = size * 0.3f;
        float barHeight = size * 1.6f;
        float gap = size * 0.4f;

        DrawRectangle(center.x - gap - barWidth, center.y - barHeight / 2, barWidth, barHeight, HomeButtonColor);
        DrawRectangle(center.x + gap, center.y - barHeight / 2, barWidth, barHeight, HomeButtonColor);
    }
}

void DrawRecordIcon()
{
    Vector2 center = { recordButton.x + recordButton.width / 2, recordButton.y + recordButton.height / 2 };
    float outerR = recordButton.width * 0.3f;
    float innerR = recordButton.width * 0.25f;

    DrawCircleV(center, outerR, Color{203, 137, 125,255});
    DrawCircleV(center, innerR, Color{209, 101, 76,255});
    DrawCircleLines(center.x , center.y , recordButton.width*0.30f , HomeButtonColor);
}
