#ifndef NAVIGATION_BAR_H
#define NAVIGATION_BAR_H

#include <vector>
#include <string>

using std::vector;
using std::string;

enum class NavigationbarState
{
    HIDDEN,
    SLIDING_IN,
    VISIBLE,
    SLIDING_OUT
};

extern NavigationbarState navState;

extern float barX ;
extern float barWidth     ;
extern float barSlideSpeed;
extern bool  IsNavigationShowing;

extern vector<string> barOptionTexts  ;
extern int            barOptionHeight ;
extern int            barOptionCount  ;

void InitNavigation();
void UpdateNavigation();
void DrawNavigation();

#endif