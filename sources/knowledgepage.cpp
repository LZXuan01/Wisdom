#include <ctime> 
#include "string.h"
#include "raylib.h"
#include "main.h"
#include "font.h"
#include "sound.h"
#include "color.h"
#include "image.h"
#include "effect.h"
#include "input.h"
#include "keyboard.h"
#include "slider.h"
#include "homepage.h"

Rectangle cancelButton       = {0};
Rectangle editDateTimeButton = {0};
Rectangle confirmButton      = {0};

static char dateStr[20], timeStr[20];

bool  showCursor = true;
float cursorTimer = 0.0f;
float cursorBlinkTime = 0.5f;  
bool  IsDrawSliders = false ;

void InitKnowledgePage()
{
    cancelButton       = {screenWidth * 0.20f - 40 / ppi, screenHeight * 0.95f - 40 / ppi, (40 * 2) / ppi, (40 * 2) / ppi};
    editDateTimeButton = {screenWidth * 0.50f - 40 / ppi, screenHeight * 0.95f - 40 / ppi, (40 * 2) / ppi, (40 * 2) / ppi};
    confirmButton      = {screenWidth * 0.80f - 40 / ppi, screenHeight * 0.95f - 40 / ppi, (40 * 2) / ppi, (40 * 2) / ppi};

    time_t now = time(nullptr);
    static tm *localTime = localtime(&now);
    strftime(dateStr, sizeof(dateStr), "%d %B", localTime);
    strftime(timeStr, sizeof(timeStr), "%I:%M %p", localTime);
}

void UpdateCursor()
{
    cursorTimer += GetFrameTime();
    if (cursorTimer >= cursorBlinkTime)
    {
        cursorTimer = 0.0f;
        showCursor = !showCursor;
    }
}

void UpdateKnowledgePage()
{
    InputUserContent();
    UpdateCursor();
    UpdateSliders();


    if (!IsKeyboardActive)
    {
        if (GetGestureDetected() == GESTURE_SWIPE_LEFT || GetGestureDetected() == GESTURE_SWIPE_RIGHT || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), cancelButton)))
        {
            IsKeyboardActive = false;
            currentPage = HOME;
            StartFadeIn();
            usercontent.clear();
            currentKnowledgePage = -1;
            IsDrawSliders = false;
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && GetMouseY() < screenHeight * 0.90f   && !IsDrawSliders)
    {
        if (!CheckCollisionPointRec(GetMousePosition(), keyboardBackground))
        {
            IsKeyboardActive = !IsKeyboardActive;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition() , confirmButton) && !IsKeyboardActive)
    {
        if (UserdateStr == "Today")
        {
            UserdateStr = dateStr ;    
        }

        if (currentKnowledgePage >= 0 && static_cast<size_t>(currentKnowledgePage) < KnowledgeGroup.size())
        {
            KnowledgeGroup[currentKnowledgePage].memoText = usercontent;
            KnowledgeGroup[currentKnowledgePage].date     = UserdateStr;
            KnowledgeGroup[currentKnowledgePage].time     = UsertimeStr;
        }
        else
        {
            if (UserdateStr == "Today")
            {
                UserdateStr = dateStr ;    
            }

            Knowledge NewKnowledgeGroup
            {
                {static_cast<float>(screenWidth * 0.05), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)},
                {static_cast<float>(screenWidth * 0.33), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)},
                {static_cast<float>(screenWidth * 0.89), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.06), static_cast<float>(screenHeight * 0.033)},
                {static_cast<float>(screenWidth * 0.04), static_cast<float>(screenHeight * 0.25), static_cast<float>(screenWidth * 0.91), static_cast<float>(screenHeight * 0.130)},
                usercontent,
                UserdateStr,
                UsertimeStr,
            };
            KnowledgeGroup.push_back(NewKnowledgeGroup);
        }

        SaveKnowledgeData();
        SortKnowledgeByTimeAscending();

        PlaySound(milestone);
        StartFadeIn();
        currentPage = HOME ;
        usercontent.clear();
        currentKnowledgePage = -1; 
        IsDrawSliders = false ;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), editDateTimeButton) && !IsKeyboardActive)
    {
        IsDrawSliders = !IsDrawSliders ;
        PlaySound(anno1801);
    }

    
        
}

void DrawKnowledgePageText()
{
    float fontSize = 55 / ppi;
    float lineSpacing = fontSize * 1.2f;
    Vector2 textStart = {screenWidth * 0.04f, screenHeight * 0.15f};

    Vector2 cursorPos = textStart;
    float maxLineWidth = screenWidth * 0.91f;

    std::string line;
    std::string wordBuffer; // 当前正在输入的单词

    for (size_t i = 0; i <= usercontent.length(); ++i)
    {
        char c = (i < usercontent.length()) ? usercontent[i] : '\0';

        bool isEnd = (c == '\0');
        bool isNewline = (c == '\n');
        bool isSpace = (c == ' ');
        bool isPunctuation = (c == ',' || c == '.' || c == '!' || c == '?' || c == ';' || c == ':');
        bool isBreak = isEnd || isNewline || isSpace || isPunctuation;

        if (!isBreak)
        {
            wordBuffer += c;
            continue;
        }

        std::string testLine = line + wordBuffer;
        Vector2 testSize = MeasureTextEx(LBRITE, testLine.c_str(), fontSize, 1);

        if (testSize.x > maxLineWidth)
        {
            DrawTextEx(LBRITE, line.c_str(), cursorPos, fontSize, 1, BLACK);
            cursorPos.x = textStart.x;
            cursorPos.y += lineSpacing;

            line = wordBuffer;
        }
        else
        {
            line += wordBuffer;
        }

        wordBuffer.clear();


        if (isSpace || isPunctuation)
        {
            line += c;
        }
        else if (isNewline || isEnd)
        {
            DrawTextEx(LBRITE, line.c_str(), cursorPos, fontSize, 1, BLACK);

            if (isEnd)
            {
                Vector2 lineSize = MeasureTextEx(LBRITE, line.c_str(), fontSize, 1);
                cursorPos.x += lineSize.x;
            }
            else
            {
                cursorPos.x = textStart.x;
                cursorPos.y += lineSpacing;
            }

            line.clear();
        }
    }

    if (showCursor)
    {
        DrawRectangle(cursorPos.x, cursorPos.y, 7 / ppi, fontSize, BLACK);
    }
}

void DrawDate()
{
    if (UserdateStr == "Today")
    DrawTextEx(LBRITED, dateStr, {(screenWidth - MeasureTextEx(LBRITED, dateStr, 40 / ppi, 1).x) * 0.35f, screenHeight * 0.10f}, 40 / ppi, 1, BLACK);
    else
    DrawTextEx(LBRITED, UserdateStr.c_str(), {(screenWidth - MeasureTextEx(LBRITED, dateStr, 40 / ppi, 1).x) * 0.35f, screenHeight * 0.10f}, 40 / ppi, 1, BLACK);
}

void DrawTime()
{
    DrawTextEx(LBRITED, UsertimeStr.c_str(), {(screenWidth - MeasureTextEx(LBRITED, timeStr, 40 / ppi, 1).x) * 0.65f,  screenHeight * 0.10f}, 40 / ppi, 1, BLACK);
}

void DrawKnowledgePage()
{
    ClearBackground(Cream);
    DrawTextEx(LBRITED, "KnowLedge", {(screenWidth - MeasureTextEx(LBRITED , "KnowLedge" , 90/ppi , 1).x) / 2, screenHeight * 0.05f}, 90 / ppi, 1, BLACK);
    DrawLineEx({screenWidth / 2 , screenHeight * 0.10f} , {screenWidth/2 , screenHeight * 0.12f} , 4 / ppi , BLACK);
    DrawDate();
    DrawTime();

    DrawSliders();

    DrawRectangleRounded({screenWidth * 0.075f , screenHeight * 0.92f , screenWidth * 0.85f, screenHeight * 0.06f} ,  0.9f , 38 , HomeButtonColor);
    DrawCircle(cancelButton.x + cancelButton.width / 2, cancelButton.y + cancelButton.height / 2, cancelButton.width / 2, RED);
    DrawCircle(editDateTimeButton.x + editDateTimeButton.width / 2, editDateTimeButton.y + editDateTimeButton.height / 2, editDateTimeButton.width / 2, ORANGE);
    DrawCircle(confirmButton.x + confirmButton.width / 2, confirmButton.y + confirmButton.height / 2, confirmButton.width / 2, GREEN);

    DrawKnowledgePageText();
    DrawKeyboard();

    ScreenFadeIn(0.80f);
}