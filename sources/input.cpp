#include <string>
#include <fstream>
#include "raylib.h"
#include "keyboard.h"
#include "loginpage.h"

std::string username = "";
std::string usercontent = "";

static double backspaceHeldTime = 0.0;
static bool   backspaceActive = false;

void InputUserName()
{

    // std::string newText = (std::string)GetSoftKeyboardText();

    // if (newText.length() <= 10)
    // {
    //     username = newText;
    // }

    UpdateKeyboard(username);

    int key = GetCharPressed();

    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && usercontent.length() < 1000)
        {
            username += static_cast<char>(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (!username.empty())
            username.pop_back();
    }

    if (IsKeyDown(KEY_BACKSPACE))
    {
        if (!backspaceActive)
        {
            backspaceHeldTime = GetTime();
            backspaceActive = true;
        }
        else
        {
            double heldDuration = GetTime() - backspaceHeldTime;

            // 超过 0.7 秒后开始每 0.08 秒删除一个字符
            static double lastDeleteTime = 0.0;
            if (heldDuration > 0.7 && (GetTime() - lastDeleteTime > 0.08))
            {
                if (!username.empty())
                {
                    username.pop_back();
                    lastDeleteTime = GetTime();
                }
            }
            else if (heldDuration <= 0.7 && IsKeyPressed(KEY_BACKSPACE))
            {
                if (!username.empty())
                    username.pop_back(); // 初次删除
            }
        }
    }
    else
    {
        // 释放按键时重置状态
        backspaceActive = false;
        backspaceHeldTime = 0.0;
    }
}

void SaveUserName()
{
    std::ofstream file("/storage/emulated/0/Android/data/com.application.wisdom/files/username.txt"); // / storage/emulated/0/Android/data/com.application.wisdom/files/
    if (file.is_open())
    {
        file << username;
        file.close();
    }
}

void LoadUserName()
{
    std::ifstream file("/storage/emulated/0/Android/data/com.application.wisdom/files/username.txt");

    if (file.is_open())
    {
        std::getline(file, username);
        file.close();
    }
}

void InputUserContent()
{
    // std::string newText = (std::string)GetSoftKeyboardText();

    // if (newText.length() <= 800)
    // {

    //     usercontent = newText;
    // }

    UpdateKeyboard(usercontent);

    int key = GetCharPressed();

    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && usercontent.length() < 1000)
        {
            usercontent += static_cast<char>(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        usercontent += "\n";
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (!usercontent.empty())
            usercontent.pop_back();
    }

    if (IsKeyDown(KEY_BACKSPACE))
    {
        if (!backspaceActive)
        {
            backspaceHeldTime = GetTime();
            backspaceActive = true;
        }
        else
        {
            double heldDuration = GetTime() - backspaceHeldTime;

            // 超过 0.7 秒后开始每 0.08 秒删除一个字符
            static double lastDeleteTime = 0.0;
            if (heldDuration > 0.7 && (GetTime() - lastDeleteTime > 0.08))
            {
                if (!usercontent.empty())
                {
                    usercontent.pop_back();
                    lastDeleteTime = GetTime();
                }
            }
            else if (heldDuration <= 0.7 && IsKeyPressed(KEY_BACKSPACE))
            {
                if (!usercontent.empty())
                    usercontent.pop_back(); // 初次删除
            }
        }
    }
    else
    {
        // 释放按键时重置状态
        backspaceActive = false;
        backspaceHeldTime = 0.0;
    }
}
