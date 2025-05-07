#include "raylib.h"

Image SnapFinger = {nullptr};
Image quill      = {nullptr};
Image checkmark  = {nullptr};
Image correct    = {nullptr};
Image enter      = {nullptr};
Image shift      = {nullptr};
Image backspace  = {nullptr};

Texture2D SnapFingerTexture = {0};
Texture2D quillTexture      = {0};
Texture2D checkmarkTexture  = {0};
Texture2D correctTexture    = {0};
Texture2D enterTexture      = {0};
Texture2D shiftTexture      = {0};
Texture2D backspaceTexture  = {0};

void LoadImageResources()
{
    SnapFinger = LoadImage("image/SnapFinger.png");
    quill      = LoadImage("image/quill.png")     ;
    checkmark  = LoadImage("image/checkmark.png") ;
    correct    = LoadImage("image/correct.png")   ;
    enter      = LoadImage("image/enter.png")     ;
    shift      = LoadImage("image/shift.png")     ;
    backspace  = LoadImage("image/backspace.png") ;

    if (SnapFinger.data == nullptr)
    {
        SnapFinger = LoadImage("../assets/image/SnapFinger.png");
        ImageResize(&SnapFinger, GetScreenWidth() * 0.85f, GetScreenHeight() * 0.35f);
    }
    if (quill.data == nullptr)
    {
        quill = LoadImage("../assets/image/quill.png");
        ImageResize(&quill, GetScreenWidth() * 0.075, GetScreenHeight() * 0.025);
    }
    if (checkmark.data == nullptr)
    {
        checkmark = LoadImage("../assets/image/checkmark.png");
        ImageResize(&checkmark, GetScreenWidth() * 0.075, GetScreenHeight() * 0.025);
    }
    if (correct.data == nullptr)
    {
        correct = LoadImage("../assets/image/correct.png");
        ImageResize(&correct, GetScreenWidth() * 0.075, GetScreenHeight() * 0.025);
    }
    if (enter.data == nullptr)
    {
        enter = LoadImage("../assets/image/enter.png");
        ImageResize(&enter, GetScreenWidth() * 0.075, GetScreenHeight() * 0.025);
    }
    if (shift.data == nullptr)
    {
        shift = LoadImage("../assets/image/shift.png");
        ImageResize(&shift, GetScreenWidth() * 0.075, GetScreenHeight() * 0.025);
    }
    if (backspace.data == nullptr)
    {
        backspace = LoadImage("../assets/image/backspace.png");
        ImageResize(&backspace, GetScreenWidth() * 0.075, GetScreenHeight() * 0.025);
    }

    SnapFingerTexture = LoadTextureFromImage(SnapFinger);
    quillTexture      = LoadTextureFromImage(quill)     ;
    checkmarkTexture  = LoadTextureFromImage(checkmark) ;
    correctTexture    = LoadTextureFromImage(correct)   ;
    enterTexture      = LoadTextureFromImage(enter)     ;
    shiftTexture      = LoadTextureFromImage(shift)     ;
    backspaceTexture  = LoadTextureFromImage(backspace) ;

    UnloadImage(SnapFinger);
    UnloadImage(quill)     ;
    UnloadImage(checkmark) ;
    UnloadImage(correct)   ;
    UnloadImage(enter)     ;
    UnloadImage(shift)     ;
    UnloadImage(backspace) ;
}

void UnloadImageResources()
{
    UnloadTexture(SnapFingerTexture);
    UnloadTexture(quillTexture)     ;
    UnloadTexture(checkmarkTexture) ;
    UnloadTexture(correctTexture)   ;
    UnloadTexture(enterTexture)     ;
    UnloadTexture(shiftTexture)     ;
    UnloadTexture(backspaceTexture) ;
}
