#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "main.h"
#include "font.h"
#include "image.h"
#include "color.h"
#include "input.h"
#include "keyboard.h"

using std::string;
using std::vector;

float keyWidth = 0;
float keyHeight = 0;
float padding = 0;
float startX = 0;
float startY = 0;
int keySize = 0;

bool IsKeyboardActive = false;
bool IsShiftActive = false;
bool IsNumericKeyboardActive = false;
bool IsPersistentShiftActive = false; // New: Tracks persistent Shift mode
float keyboardSlidePos = 0;
float keyboardSlideSpeed = 0;
static double backspaceHeldTime = 0;
static double lastShiftClickTime = 0; // New: Tracks time of last Shift click
static bool backspaceActive = false;

vector<Key> alphaKeys;
vector<Key> numericKeys;
vector<Key> keys;
Rectangle keyboardBackground = {0};

void InitKeyboard()
{
    keyWidth = screenWidth * 0.0999f;
    keyHeight = screenHeight * 0.0700f;
    padding = -screenWidth * 0.0001f;
    startX = (screenWidth - (10 * (keyWidth + padding) - padding)) / 2;
    startY = screenHeight * 0.7f;
    keySize = screenHeight * 0.026f;

    IsKeyboardActive = false;
    IsNumericKeyboardActive = false;
    IsShiftActive = false;
    IsPersistentShiftActive = false; // Initialize persistent Shift
    keyboardSlidePos = screenHeight;
    keyboardSlideSpeed = 0.4f;
    backspaceHeldTime = 0;
    backspaceActive = false;
    lastShiftClickTime = 0; // Initialize Shift click time

    alphaKeys.clear();
    numericKeys.clear();
    keys.clear();

    // --- Alphabetic Keyboard Layout ---
    string rows[] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};

    // First row (qwertyuiop)
    for (size_t i = 0; i < rows[0].length(); i++)
    {
        float x = startX + i * (keyWidth + padding);
        float y = startY;
        string label = string(1, rows[0][i]);
        alphaKeys.push_back({{x, y, keyWidth, keyHeight}, label, (int)rows[0][i], false});
    }

    // Second row (asdfghjkl)
    for (size_t i = 0; i < rows[1].length(); i++)
    {
        float x = startX + (i + 0.5f) * (keyWidth + padding);
        float y = startY + (keyHeight + padding);
        string label = string(1, rows[1][i]);
        alphaKeys.push_back({{x, y, keyWidth, keyHeight}, label, (int)rows[1][i], false});
    }

    // Third row (zxcvbnm)
    alphaKeys.push_back({{startX, startY + 2 * (keyHeight + padding), keyWidth * 1.5f, keyHeight}, "Shf", 0, true});
    for (size_t i = 0; i < rows[2].length(); i++)
    {
        float x = startX + (i + 1.5f) * (keyWidth + padding);
        float y = startY + 2 * (keyHeight + padding);
        string label = string(1, rows[2][i]);
        alphaKeys.push_back({{x, y, keyWidth, keyHeight}, label, (int)rows[2][i], false});
    }
    float backspaceX = startX + (rows[2].length() + 1.5f) * (keyWidth + padding);
    alphaKeys.push_back({{backspaceX, startY + 2 * (keyHeight + padding), keyWidth * 1.5f, keyHeight}, "DEL", 8, false});

    // Fourth row
    float fourthRowY = startY + 3 * (keyHeight + padding);
    float currentX = startX;
    alphaKeys.push_back({{currentX, fourthRowY, keyWidth * 1.5f, keyHeight}, "123", -123, false});
    currentX += keyWidth * 1.5f + padding;
    alphaKeys.push_back({{currentX, fourthRowY, keyWidth, keyHeight}, ",", ',', false});
    currentX += keyWidth + padding;
    float spaceWidth = keyWidth * 5.0f;
    alphaKeys.push_back({{currentX, fourthRowY, spaceWidth, keyHeight}, "", ' ', false});
    currentX += spaceWidth + padding;
    alphaKeys.push_back({{currentX, fourthRowY, keyWidth, keyHeight}, ".", '.', false});
    currentX += keyWidth + padding;
    alphaKeys.push_back({{currentX, fourthRowY, keyWidth * 1.5f, keyHeight}, "Enter", 13, false});

    // --- Numeric Keyboard Layout ---
    string numRows[] = {"1234567890", "@#$&_-( )=%", "\"*':/!?+"};
    float numStartX = startX;
    float numStartY = startY;

    // First row (1234567890)
    for (size_t i = 0; i < 10; i++)
    {
        float x = numStartX + i * (keyWidth + padding);
        float y = numStartY;
        string label = string(1, numRows[0][i]);
        numericKeys.push_back({{x, y, keyWidth, keyHeight}, label, (int)numRows[0][i], false});
    }

    // Second row (@#$&_-( )=%)
    for (size_t i = 0; i < numRows[1].length(); i++)
    {
        float x = numStartX + i * (keyWidth + padding);
        float y = numStartY + (keyHeight + padding);
        string label = string(1, numRows[1][i]);
        int code;
        switch (numRows[1][i])
        {
        case '@':
            code = '@';
            break;
        case '#':
            code = '#';
            break;
        case '$':
            code = '$';
            break;
        case '&':
            code = '&';
            break;
        case '_':
            code = '_';
            break;
        case '-':
            code = '-';
            break;
        case '(':
            code = '(';
            break;
        case ')':
            code = ')';
            break;
        case '=':
            code = '=';
            break;
        case '%':
            code = '%';
            break;
        default:
            code = numRows[1][i];
            break;
        }
        numericKeys.push_back({{x, y, keyWidth, keyHeight}, label, code, false});
    }

    // Third row ("*':/!?+)
    float thirdRowStartX = numStartX;
    for (size_t i = 0; i < numRows[2].length(); i++)
    {
        float x = thirdRowStartX + i * (keyWidth + padding);
        float y = numStartY + 2 * (keyHeight + padding);
        string label = string(1, numRows[2][i]);
        int code;
        switch (numRows[2][i])
        {
        case '"':
            code = '"';
            break;
        case '*':
            code = '*';
            break;
        case '\'':
            code = '\'';
            break;
        case ':':
            code = ':';
            break;
        case '/':
            code = '/';
            break;
        case '!':
            code = '!';
            break;
        case '?':
            code = '?';
            break;
        case '+':
            code = '+';
            break;
        default:
            code = numRows[2][i];
            break;
        }
        numericKeys.push_back({{x, y, keyWidth, keyHeight}, label, code, false});
    }
    backspaceX = numStartX + (numRows[2].length() + 0.5f) * (keyWidth + padding);
    numericKeys.push_back({{backspaceX, numStartY + 2 * (keyHeight + padding), keyWidth * 1.5f, keyHeight}, "DEL", 8, false});

    // Fourth row (ABC, comma, space, dot, enter)
    currentX = numStartX;
    numericKeys.push_back({{currentX, fourthRowY, keyWidth * 1.5f, keyHeight}, "ABC", -123, false});
    currentX += keyWidth * 1.5f + padding;
    numericKeys.push_back({{currentX, fourthRowY, keyWidth, keyHeight}, ",", ',', false});
    currentX += keyWidth + padding;
    spaceWidth = keyWidth * 5.0f;
    numericKeys.push_back({{currentX, fourthRowY, spaceWidth, keyHeight}, "", ' ', false});
    currentX += spaceWidth + padding;
    numericKeys.push_back({{currentX, fourthRowY, keyWidth, keyHeight}, ".", '.', false});
    currentX += keyWidth + padding;
    numericKeys.push_back({{currentX, fourthRowY, keyWidth * 1.5f, keyHeight}, "Enter", 13, false});

    // Set initial keys to alphabetic
    keys = alphaKeys;
}

void UpdateKeyboard(string &text)
{
    float targetY = IsKeyboardActive ? screenHeight * 0.7f : screenHeight;
    keyboardSlidePos += (targetY - keyboardSlidePos) * keyboardSlideSpeed;

    if (!IsKeyboardActive)
        return;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        backspaceActive = false;
        backspaceHeldTime = 0.0;
    }

    if (IsKeyboardActive)
    {
        bool backspacePressed = false;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            for (Key &key : keys)
            {
                if (CheckCollisionPointRec(GetMousePosition(), key.bounds))
                {
                    if (key.code == 8)
                        backspacePressed = true;
                    break;
                }
            }
        }

        // Handle backspace
        if (backspacePressed)
        {
            if (!backspaceActive)
            {
                backspaceActive = true;
                backspaceHeldTime = GetTime();
                if (!text.empty())
                    text.pop_back();
            }
            else
            {
                double heldDuration = GetTime() - backspaceHeldTime;
                if (heldDuration > 0.5)
                {
                    static double lastDeleteTime = 0.0;
                    if (GetTime() - lastDeleteTime > 0.04)
                    {
                        if (!text.empty())
                        {
                            text.pop_back();
                            lastDeleteTime = GetTime();
                        }
                    }
                }
            }
        }
        else
        {
            backspaceActive = false;
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        for (Key &key : keys)
        {
            if (CheckCollisionPointRec(mouse, key.bounds))
            {
                if (key.code == -123) // Toggle keyboard mode
                {
                    IsNumericKeyboardActive = !IsNumericKeyboardActive;
                    keys = IsNumericKeyboardActive ? numericKeys : alphaKeys;
                    IsShiftActive = false;
                    IsPersistentShiftActive = false; // Disable persistent Shift when switching modes
                    for (auto &k : keys)
                    {
                        if (k.code >= 'a' && k.code <= 'z')
                            k.label = tolower(k.label[0]);
                    }
                }
                else if (key.code == 8) // Backspace (already handled above)
                {
                    // No action needed here
                }
                else if (key.isShifted) // Shift key
                {
                    double currentTime = GetTime();
                    if (currentTime - lastShiftClickTime < 0.3) // Double-click within 0.3 seconds
                    {
                        IsPersistentShiftActive = !IsPersistentShiftActive; // Toggle persistent Shift
                        IsShiftActive = IsPersistentShiftActive;            // Sync Shift state
                    }
                    else
                    {
                        IsPersistentShiftActive = false ;
                        if (!IsPersistentShiftActive) // Single-click toggles Shift only if not persistent
                        {
                            IsShiftActive = !IsShiftActive;
                        }
                    }
                    lastShiftClickTime = currentTime; // Update last click time

                    // Update key labels
                    for (auto &k : keys)
                    {
                        if (k.code >= 'a' && k.code <= 'z')
                            k.label = IsShiftActive ? toupper(k.label[0]) : tolower(k.label[0]);
                    }
                }
                else if (key.code == 13) // Enter key
                {
                    if (text != username)
                    {
                        text += "\n";
                    }
                    else
                    {
                        IsKeyboardActive = false;
                    }
                }
                else // Other keys (letters, numbers, symbols)
                {
                    if (text == username)
                    {
                        if (text.length() < 10)
                        {
                            char newChar = IsShiftActive && (key.code >= 'a' && key.code <= 'z') ? toupper((char)key.code) : (char)key.code;
                            text += newChar;
                        }
                    }
                    else
                    {
                        char newChar = IsShiftActive && (key.code >= 'a' && key.code <= 'z') ? toupper((char)key.code) : (char)key.code;
                        text += newChar;
                    }

                    // Only deactivate Shift after key press if not in persistent mode and in alphabetic mode
                    if (!IsPersistentShiftActive && !IsNumericKeyboardActive)
                    {
                        IsShiftActive = false;
                        for (auto &k : keys)
                        {
                            if (k.code >= 'a' && k.code <= 'z')
                                k.label = tolower(k.label[0]);
                        }
                    }
                }
                break;
            }
        }
    }
}

void DrawKeyboard()
{
    float yOffset = keyboardSlidePos - screenHeight * 0.7f;

    for (Key &key : keys)
    {
        key.bounds.y += yOffset;
    }

    float minX = screenWidth, minY = screenHeight;
    float maxX = 0, maxY = 0;

    for (const Key &key : keys)
    {
        if (key.bounds.x < minX)
            minX = key.bounds.x;
        if (key.bounds.y < minY)
            minY = key.bounds.y;
        if (key.bounds.x + key.bounds.width > maxX)
            maxX = key.bounds.x + key.bounds.width;
        if (key.bounds.y + key.bounds.height > maxY)
            maxY = key.bounds.y + key.bounds.height;
    }

    // Draw keyboard background
    float margin = 5.0f;
    keyboardBackground = {minX - margin * 4.8f, minY - margin, (maxX - minX) + margin * 7.5f, (maxY - minY) + margin + screenHeight * 0.04f};
    DrawRectangleRec(keyboardBackground , BLACK);

    bool specialkey = false ;

    // Draw keys
    for (const Key &key : keys)
    {
        

        if (key.code == 13) // Enter key
        {
            DrawTexture(enterTexture, key.bounds.x + 30 / ppi, key.bounds.y + 30 / ppi, WHITE);
            specialkey = true ;
        }
        else if (key.code == 0) // Shift key
        {
            DrawTexture(shiftTexture, key.bounds.x + 30 / ppi, key.bounds.y + 30 / ppi, WHITE);
            specialkey = true ;
        }
        else if (key.code == 8) // Backspace key
        {
            DrawTexture(backspaceTexture, key.bounds.x + 30 / ppi, key.bounds.y + 30 / ppi, WHITE);
            specialkey = true ;
        }
        else if (key.code == -123) // "123" or "ABC" key
        {
            DrawRectangleRounded(key.bounds, 0.2f, 8, BLACK);
            int textWidth = MeasureText(key.label.c_str(), keySize);
            DrawTextEx(LBRITE, key.label.c_str(), {key.bounds.x + (key.bounds.width - textWidth) / 2, key.bounds.y + keySize}, keySize, 0, Cream);
            specialkey = true ;
        }

        if (CheckCollisionPointRec(GetMousePosition(), key.bounds) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleRounded(key.bounds, 0.2f, 8, Fade(Cream, 0.3f)); // Click effect
        }

        if (specialkey)
        {
            specialkey = false ;
            continue; 
        }

        if (key.bounds.width == keyWidth * 5.0f) // Space key
        {
            DrawRectangleRoundedLines(key.bounds, 0.5f, 38, BLACK);
            DrawRectangleRounded(key.bounds, 0.2f, 8, BLACK);
            float symbolHeight = key.bounds.height * 0.05f;
            float symbolWidth = key.bounds.width * 0.5f;
            Rectangle symbolRect = {key.bounds.x + (key.bounds.width - symbolWidth) / 2, key.bounds.y + (key.bounds.height - symbolHeight) / 1.2f, symbolWidth, symbolHeight};
            DrawRectangleRec(symbolRect, Cream);
        }
        else // Regular keys (letters, numbers, symbols)
        {
            DrawRectangleRounded(key.bounds, 0.2f, 8, BLACK);
            int textWidth = MeasureText(key.label.c_str(), keySize);
            DrawTextEx(LBRITE, key.label.c_str(), {key.bounds.x + (key.bounds.width - textWidth) / 2, key.bounds.y + keySize}, keySize, 0, Cream);
        }

        if (CheckCollisionPointRec(GetMousePosition(), key.bounds) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleRounded(key.bounds, 0.2f, 8, Fade(Cream, 0.3f)); // Click effect
        }
    }

    

    // Restore key positions
    for (auto &key : keys)
    {
        key.bounds.y -= yOffset;
    }
}