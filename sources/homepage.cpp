#include <algorithm> 
#include <fstream>
#include <sstream>
#include <ctime> 
#include <string>
#include <vector>
#include "raylib.h"
#include "main.h"
#include "font.h"
#include "sound.h"
#include "color.h"
#include "icon.h"
#include "effect.h"
#include "input.h"
#include "keyboard.h"
#include "scroll.h"
#include "navigation.h"
#include "homepage.h"


std::vector<Knowledge> KnowledgeGroup ;
Rectangle AddButton      = {0} ;
int currentKnowledgePage = -1 ;
int currentEditButton    = -1 ;
static char tempDate[20], tempTime[20];

const std::string SAVE_FILE = "/storage/emulated/0/Android/data/com.application.wisdom/files/knowledge_data.txt";
const std::string FIRST_LAUNCH_FILE = "/storage/emulated/0/Android/data/com.application.wisdom/files/first_launch.txt";
const std::string TUTORIAL_FILE = "/storage/emulated/0/Android/data/com.application.wisdom/files/tutorial.txt";

void SortKnowledgeByTimeAscending()
{
    std::sort(KnowledgeGroup.begin(), KnowledgeGroup.end(), [](const Knowledge &a, const Knowledge &b)
              { return a.GetTimestamp() < b.GetTimestamp(); });
}

void SaveKnowledgeData()
{
    SortKnowledgeByTimeAscending();

    std::ofstream outFile(SAVE_FILE);
    for (const auto &knowledge : KnowledgeGroup)
    {
        outFile << knowledge.Serialize() << "\n";
    }
    outFile.close();
}

void LoadKnowledgeData()
{
    KnowledgeGroup.clear();

    std::ifstream inFile(SAVE_FILE);
    std::string line;
    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            Knowledge k = Knowledge::Deserialize(line);
            if (k.memoText.find("Welcome to Wisdom + Knowledge!") != 0)
            {
                KnowledgeGroup.push_back(k);
            }
        }
    }
    inFile.close();

    for (auto &knowledge : KnowledgeGroup)
    {
        knowledge.dateButton = {static_cast<float>(screenWidth * 0.05), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)};
        knowledge.timeButton = {static_cast<float>(screenWidth * 0.33), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)};
        knowledge.editButton = {static_cast<float>(screenWidth * 0.89), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.06), static_cast<float>(screenHeight * 0.033)};
        knowledge.memoButton = {static_cast<float>(screenWidth * 0.04), static_cast<float>(screenHeight * 0.25), static_cast<float>(screenWidth * 0.91), static_cast<float>(screenHeight * 0.130)};
    }

    SortKnowledgeByTimeAscending();
}

void LoadTutorial()
{

    time_t now = time(nullptr);
    static tm *localTime = localtime(&now);
    strftime(tempDate, sizeof(tempDate), "%d %B", localTime);
    strftime(tempTime, sizeof(tempTime), "%I:%M %p", localTime);

    std::ifstream inFile(TUTORIAL_FILE);
    std::string line;
    Knowledge tutorial;

    if (std::getline(inFile, line) && !line.empty())
    {
        tutorial = Knowledge::Deserialize(line);
    }
    else
    {
        // Fallback: Create default tutorial if file is missing
        tutorial.memoText = "Welcome Traveler, Please come in to the world of secrets and magic.\nVenture forth, and unlock knowledge hidden in the shadows.\n\n\n\nThe enchanted keyboard appears with a simple touch.\nAt the screen's bottom, three runes await:\n- First: Exit\n- Second: Adjust time\n- Third: Confirm\n\nSlide left or right to exit but without saving your progress.";
        tutorial.date = tempDate;
        tutorial.time = tempTime;
    }
    inFile.close();

    // Set button rectangles
    tutorial.dateButton = {static_cast<float>(screenWidth * 0.05), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)};
    tutorial.timeButton = {static_cast<float>(screenWidth * 0.33), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)};
    tutorial.editButton = {static_cast<float>(screenWidth * 0.89), static_cast<float>(screenHeight * 0.19), static_cast<float>(screenWidth * 0.06), static_cast<float>(screenHeight * 0.033)};
    tutorial.memoButton = {static_cast<float>(screenWidth * 0.04), static_cast<float>(screenHeight * 0.25), static_cast<float>(screenWidth * 0.91), static_cast<float>(screenHeight * 0.130)};

    KnowledgeGroup.push_back(tutorial);
}

void InitHomePage()
{
    std::ifstream firstLaunchFile(FIRST_LAUNCH_FILE);
    bool isFirstLaunch = !firstLaunchFile.good();
    firstLaunchFile.close();

    if (isFirstLaunch)
    {
        LoadTutorial();
        SaveKnowledgeData();
        std::ofstream outFile(FIRST_LAUNCH_FILE);
        outFile << "1";
        outFile.close();
    }
    else
    {
        LoadKnowledgeData(); 
    }

    if (KnowledgeGroup.empty())
    {
        time_t now = time(nullptr);
        tm *localTime = localtime(&now);
        char dateStr[20], timeStr[20];
        strftime(dateStr, sizeof(dateStr), "%d %B", localTime);
        strftime(timeStr, sizeof(timeStr), "%I:%M %p", localTime);

        Knowledge initKnowledge = {
            {static_cast<float>(screenWidth * 0.05), static_cast<float>(screenHeight * 0.19),
             static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)},
            {static_cast<float>(screenWidth * 0.33), static_cast<float>(screenHeight * 0.19),
             static_cast<float>(screenWidth * 0.22), static_cast<float>(screenHeight * 0.033)},
            {static_cast<float>(screenWidth * 0.89), static_cast<float>(screenHeight * 0.19),
             static_cast<float>(screenWidth * 0.06), static_cast<float>(screenHeight * 0.033)},
            {static_cast<float>(screenWidth * 0.04), static_cast<float>(screenHeight * 0.25),
             static_cast<float>(screenWidth * 0.91), static_cast<float>(screenHeight * 0.130)},
            "",
            dateStr,
            timeStr};
        KnowledgeGroup.push_back(initKnowledge);
    }
}

void UpdateHomePage()
{
    UpdateScroll();
    UpdateIcon();
    UpdateNavigation();

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !IsNavigationShowing)
    {
        if (CheckCollisionPointRec(GetMousePosition(), AddButton))
        {
            PlaySound(anno1803);
            currentPage = KNOWLEDGE;
            StartFadeIn();
        }
    }
        
    IsKeyboardActive = false;
}


// Draw

void DrawUpperBar()
{
    DrawTextEx(LBRITED, "Wisdom + Knowledge", {static_cast<float>(GetScreenWidth() * 0.02), static_cast<float>(GetScreenHeight() * 0.12)}, 100 / ppi, 1, HomeButtonColor);
    
    std::string halo = "Hi , " + username;
    DrawTextEx(LBRITEDI, halo.c_str(), {static_cast<float>(GetScreenWidth() - MeasureTextEx(LBRITEDI, halo.c_str(), 40 / ppi, 0).x - 20 /ppi ) , static_cast<float>(GetScreenHeight() * 0.075), }, 40 / ppi, 0, HomeButtonColor);

    DrawHomeIcon();
    DrawDocumentIcon();
}

void DrawLowerBar()
{
    DrawExitIcon();
    DrawMenuIcon();
    DrawPlayIcon();
    DrawRecordIcon();
}

void DrawDateButton(const Knowledge &k, float yOffset)
{
    Rectangle db = k.dateButton;
    db.y += yOffset;

    Vector2 textSize = MeasureTextEx(LBRITEI, k.date.c_str(), 35 / ppi, 1);
    DrawRectangleRounded(db, 0.9, 38, Cream);
    DrawRectangleRoundedLinesEx(db, 0.9, 38, 2 / ppi, FontColor);
    DrawTextEx(LBRITEI, k.date.c_str(), {db.x + (db.width - textSize.x) / 2, db.y + (db.height - textSize.y) / 2}, 35 / ppi, 1, FontColor);
}

void DrawTimeButton(const Knowledge &k, float yOffset)
{
    Rectangle tb = k.timeButton;
    tb.y += yOffset;

    std::string buttonText = "   " + k.time + "   ";
    Vector2 textSize = MeasureTextEx(LBRITEI, buttonText.c_str(), 35 / ppi, 1);

    DrawRectangleRounded(tb, 0.9, 38, HomeButtonColor);
    DrawRectangleRoundedLinesEx(tb, 0.9, 38, 3 / ppi, FontColor);
    DrawTextEx(LBRITEI, buttonText.c_str(), {tb.x + (tb.width - textSize.x) / 2, tb.y + (tb.height - textSize.y) / 2}, 35 / ppi, 1, Cream);
}

void DrawEditButton(const Knowledge &k, float yOffset)
{
    Rectangle eb = k.editButton;
    eb.y += yOffset;

    DrawCircle(eb.x + eb.width / 2, eb.y + eb.height / 2, eb.height / 2, HomeButtonColor);
    float cx = eb.x + eb.width / 2, cy = eb.y + eb.height / 2, spacing = eb.width * 0.2f, r = eb.height * 0.2f;
    for (int j = -1; j <= 1; j++) DrawCircle(cx + j * spacing, cy, r / 3, WHITE);

    if (IsEditButton && currentEditButton >= 0 && (size_t)currentEditButton < KnowledgeGroup.size())
    {
        Rectangle currentEB = KnowledgeGroup[currentEditButton].editButton;
        currentEB.y += float(currentEditButton) * (screenHeight * 0.22f) + scrollOffset;

        Vector2 editPos  = {screenWidth  * 0.45f, currentEB.y + screenHeight * 0.04f};
        Vector2 editSize = {screenHeight * 0.23f, screenHeight * 0.105f};

        DrawRectangleRounded({editPos.x, editPos.y, editSize.x, editSize.y}, 0.4f, 38, HomeButtonColor);

        // 中线
        DrawLine(editPos.x, editPos.y + editSize.y / 2, editPos.x + editSize.x, editPos.y + editSize.y / 2, DARKGRAY);

        // 文本：根据 editPos 偏移
        DrawTextEx(LBRITED , "Duplicate", {editPos.x + screenHeight * 0.02f, editPos.y + screenHeight * 0.020f}, 40 / ppi, 0, WHITE);
        DrawTextEx(LBRITED , "Delete"   , {editPos.x + screenHeight * 0.02f, editPos.y + screenHeight * 0.07f }, 40 / ppi, 0, WHITE);

        // 圆点：相对于 editPos 计算
        DrawCircle(editPos.x + editSize.x - 35 / ppi, editPos.y + screenHeight * 0.028f, 12 / ppi, GREEN);
        DrawCircle(editPos.x + editSize.x - 35 / ppi, editPos.y + screenHeight * 0.078f, 12 / ppi, RED);
  
    }
}

void DrawMemoButton(const Knowledge &k, float yOffset)
{
    Rectangle mb = k.memoButton;
    mb.y += yOffset;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition() , mb))
    {
        DrawRectangleRounded(mb, 0.4, 38, Fade(YELLOW, 0.05f));
    }


    DrawRectangleRoundedLinesEx(mb, 0.4, 38, 3 / ppi, BLACK);
    float fontSize = 55 / ppi;
    float lineSpacing = fontSize * 1.5f;
    float padding = 40 / ppi;

    Vector2 pos = {mb.x + padding, mb.y + padding};
    float maxWidth = mb.width - 2 * padding;

    std::string line, wordBuffer;
    for (size_t i = 0; i <= k.memoText.length(); ++i)
    {
        char c = (i < k.memoText.length()) ? k.memoText[i] : '\0';
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
        Vector2 testSize = MeasureTextEx(LBRITED, testLine.c_str(), fontSize, 1);

        if (testSize.x > maxWidth)
        {
            DrawTextEx(LBRITED, line.c_str(), pos, fontSize, 1, BLACK);
            pos.y += lineSpacing;
            if (pos.y + lineSpacing > mb.y + mb.height - padding)
            {
                DrawTextEx(LBRITED, "...", pos, fontSize, 1, BLACK);
                break;
            }
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
            DrawTextEx(LBRITED, line.c_str(), pos, fontSize, 1, BLACK);
            pos.y += lineSpacing;
            if (pos.y + lineSpacing > mb.y + mb.height - padding)
            {
                if (!isEnd)
                    DrawTextEx(LBRITED, "...", pos, fontSize, 1, BLACK);
                break;
            }
            line.clear();
        }
    }
}

void DrawAddButton()
{
    float lastYOffset = float(KnowledgeGroup.size() - 1) * (screenHeight * 0.22f) + scrollOffset;
    const Knowledge &lastK = KnowledgeGroup.back();
    Rectangle lastMemo = lastK.memoButton;
    lastMemo.y += lastYOffset;

    AddButton = { screenWidth * 0.04f, lastMemo.y + lastMemo.height + screenHeight * 0.02f,screenWidth * 0.30f, screenHeight * 0.04f };
    if (KnowledgeGroup.empty())
    {
        AddButton = { screenWidth * 0.04f, screenHeight * 0.20f ,screenWidth * 0.30f, screenHeight * 0.04f };
    }

    DrawRectangleRoundedLinesEx(AddButton, 1, 38 , 3 / ppi , BLACK);
    Vector2 addTextSize = MeasureTextEx(LBRITEI, "add section +", 40 / ppi, 1);
    DrawTextEx(LBRITE, "add section +", {AddButton.x + (AddButton.width - addTextSize.x) / 2, AddButton.y + (AddButton.height - addTextSize.y) / 2}, 40 / ppi, 1, BLACK);
}

void DrawKnowledgeButtonGroup()
{
    BeginScissorMode(0 , screenHeight * 0.185f , screenWidth , screenHeight * 0.70f);

    for (size_t i = 0; i < KnowledgeGroup.size(); i++)
    {
        float yOffset = float(i) * (screenHeight * 0.22f) + scrollOffset;
        const Knowledge &k = KnowledgeGroup[i];

        DrawDateButton(k, yOffset);
        DrawTimeButton(k, yOffset);
        
        DrawMemoButton(k, yOffset);
        DrawEditButton(k, yOffset); 
    }

    DrawAddButton();  

    EndScissorMode();
}

void DrawHomePage()
{
    ClearBackground(Cream);
    DrawUpperBar();
    DrawKnowledgeButtonGroup();
    DrawLowerBar();
    DrawNavigation();
    ScreenFadeIn();
}