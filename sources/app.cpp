#include <cstdlib>
#include "raylib.h"
#include "main.h"

int main()
{

    InitPage();
    InitWindow(screenWidth , screenHeight  , "Wisdom");
    SetTargetFPS(60);


    LoadResources();


    while (!WindowShouldClose()) 
    {
        UpdatePage();

        BeginDrawing();

        DrawPage();

        if ( currentPage == CLOSE )
        {
            DrawClosePage();
            UnloadResources();
            CloseWindow();
            exit(0);
        }
        EndDrawing();
    }

    UnloadResources();
    CloseWindow();

    return 0;

}