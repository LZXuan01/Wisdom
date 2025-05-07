#ifndef MAIN_H
#define MAIN_H

enum ScreenPage
{
    LOADING   ,
    START     ,
    LOGIN     ,
    HOME      ,
    KNOWLEDGE ,
    SETTINGS  ,
    ABOUT     ,
    CLOSE     ,
};

extern ScreenPage currentPage ; 
extern ScreenPage previousPage;

extern float screenWidth ;
extern float screenHeight;
extern float ppi         ;


// follow sequence
void InitPage();
void DrawLoadingPage();
void UpdatePage();
void DrawPage();
void LoadResources();
void DrawClosePage();
void UnloadResources();

#endif 
