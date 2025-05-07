#ifndef IMAGE_H
#define IMAGE_H

#include "raylib.h"

extern Image SnapFinger;
extern Image quill     ;
extern Image checkmark ;
extern Image correct   ;
extern Image enter     ; 
extern Image shift     ;
extern Image backspace ;

extern Texture2D SnapFingerTexture;
extern Texture2D quillTexture     ;
extern Texture2D checkmarkTexture ;
extern Texture2D correctTexture   ;
extern Texture2D enterTexture     ;
extern Texture2D shiftTexture     ;
extern Texture2D backspaceTexture ;

void LoadImageResources();
void UnloadImageResources();


#endif