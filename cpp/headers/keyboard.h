#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>
#include "raylib.h"

extern Rectangle keyboardBackground;

struct Key
{
    Rectangle bounds;
    std::string label;
    int code;
    bool isShifted;
};

extern bool IsKeyboardActive;

void InitKeyboard();
void UpdateKeyboard(std::string &text);
void DrawKeyboard();

#endif