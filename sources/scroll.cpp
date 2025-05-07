// 只属于homepage.cpp 用来滑动时不误差按钮，所有滑动区域里的按钮逻辑在这里检测除了add section

#include "raylib.h"
#include "raymath.h"
#include "main.h"
#include "sound.h"
#include "icon.h"
#include "input.h"
#include "scroll.h"
#include "effect.h"
#include "navigation.h"
#include "homepage.h"

float   scrollOffset   = 0.0f ;
float   scrollVelocity = 0.0f ;
bool    isDragging     = false;
Vector2 lastTouchPos   = {0}  ;
bool    IsEditButton   = false;

void UpdateScroll()
{
    Rectangle scrollArea = {0 , screenHeight * 0.19f , screenWidth , screenHeight * 0.70f};

    static Vector2 initialTouchPos; 

    if (CheckCollisionPointRec(GetMousePosition(), scrollArea) && !IsNavigationShowing)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isDragging      = true;
            lastTouchPos    = GetMousePosition();
            initialTouchPos = GetMousePosition(); 
            scrollVelocity  = 0;
        }
        else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && isDragging)
        {
            float deltaY = GetMousePosition().y - lastTouchPos.y;
            if  (deltaY != 0.0f)
            {
                scrollOffset  += deltaY;
                scrollVelocity = deltaY;
                lastTouchPos   = GetMousePosition();
            }
        }
        else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
        { 
            if (Vector2Distance(initialTouchPos, GetMousePosition()) < 1.0f) 
            {
                for (size_t i = 0; i < KnowledgeGroup.size(); i++)
                {
                    float yOffset = float(i) * (screenHeight * 0.22f) + scrollOffset;
                    Rectangle mb = KnowledgeGroup[i].memoButton;
                    Rectangle eb = KnowledgeGroup[i].editButton;
                    mb.y += yOffset;
                    eb.y += yOffset;
            
                    if (CheckCollisionPointRec(GetMousePosition(), mb) && !IsEditButton ) // 点击 memo button
                    {
                        currentKnowledgePage = i; 
                        usercontent = KnowledgeGroup[i].memoText;
                        //CreateEditText(screenWidth * 0.04f, screenHeight * 0.15f, screenWidth * 0.92f, screenHeight * 0.75f, usercontent.c_str(), false);
                        currentPage = KNOWLEDGE;
                        SetSoundVolume(paperSound , 0.5f);
                        PlaySound(paperSound);
                        StartFadeIn();
                        break;
                    }

                    if (CheckCollisionPointRec(GetMousePosition(), eb)) // 点击 edit button
                    {
                        PlaySound(anno1803);
                        currentEditButton = i ;
                        IsEditButton = !IsEditButton ;
                    }

                    if (IsEditButton == true && (size_t)currentEditButton == i) // delete buton 和 duplicate button
                    {

                        Rectangle deleteRect    = { screenWidth * 0.45f, eb.y + screenHeight * 0.085f, screenHeight * 0.23f, screenHeight * 0.06f};
                        Rectangle duplicateRect = { screenWidth * 0.45f, eb.y + screenHeight * 0.040f, screenHeight * 0.23f, screenHeight * 0.06f};

                        if (CheckCollisionPointRec(GetMousePosition(), deleteRect))
                        {
                            KnowledgeGroup.erase(KnowledgeGroup.begin() + i);
                            SaveKnowledgeData();
                            PlaySound(anno1802);
                            IsEditButton = false;
                            currentEditButton = -1;
                            break;
                        }

                        if (CheckCollisionPointRec(GetMousePosition(), duplicateRect))
                        {
                            Knowledge copy = KnowledgeGroup[i]; // 复制当前项
                            KnowledgeGroup.insert(KnowledgeGroup.begin() + i + 1, copy);
                            SaveKnowledgeData();
                            PlaySound(anno1801);
                            IsEditButton = false;
                            currentEditButton = -1;
                            break;
                        }

                        if (!CheckCollisionPointRec(GetMousePosition(), duplicateRect) && !CheckCollisionPointRec(GetMousePosition(), deleteRect) && !CheckCollisionPointRec(GetMousePosition(), eb))
                        {
                            IsEditButton = false ;
                            currentEditButton = -1 ;
                        }
                    }

                  
                    
                }
            }
            isDragging = false;
        }
    }

    // 惯性滚动
    if (!isDragging && fabs(scrollVelocity) > 0.1f)
    {
        scrollOffset   += scrollVelocity;
        scrollVelocity *= 0.90f;
    }

    // 限制 scrollOffset 范围
    float contentHeight = KnowledgeGroup.size() * screenHeight * 0.23f;
    float minOffset     = std::min(0.0f, screenHeight * 0.70f - contentHeight);
    float maxOffset     = 0.0f;

    if (scrollOffset > maxOffset) { scrollOffset = maxOffset ; scrollVelocity = 0; }
    if (scrollOffset < minOffset) { scrollOffset = minOffset ; scrollVelocity = 0; }
}