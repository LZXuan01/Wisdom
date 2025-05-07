#include "raylib.h"
#include "main.h"

Camera2D camera = {0};
bool IsCameraActive = false;

void InitCamera()
{
    camera.offset   = {screenWidth / 2.0f, screenHeight / 2.0f}; // 画面摆放位置
    camera.target   = {screenWidth / 2.0f, screenHeight / 2.0f}; // 相机瞄准位置
    camera.rotation = 0   ;
    camera.zoom     = 1.0f;

    IsCameraActive  = false;
}

void ResetCamera()
{
    camera.offset   = {screenWidth / 2.0f, screenHeight / 2.0f}; 
    camera.target   = {screenWidth / 2.0f, screenHeight / 2.0f}; 
    camera.rotation = 0   ;
    camera.zoom     = 1.0f;

    IsCameraActive  = false;

}

