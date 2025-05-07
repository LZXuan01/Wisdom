#include "raylib.h"

Font cambriaz = {0};
Font cambriab = {0};
Font micross = {0};
Font terminal = {0};
Font LBRITE = {0};
Font LBRITED = {0};
Font LBRITEDI = {0};
Font LBRITEI = {0};
Font veryla = {0};
Font cartoon = {0};
Font beautiful = {0};

void LoadFontResources()
{
    cambriaz = LoadFontEx("font/cambriaz.ttf", 128, nullptr, 0);
    if (cambriaz.texture.id == 0)
        cambriaz = LoadFontEx("../assets/font/cambriaz.ttf", 128, nullptr, 0);
    SetTextureFilter(cambriaz.texture, TEXTURE_FILTER_BILINEAR);

    cambriab = LoadFontEx("font/cambriab.ttf", 128, nullptr, 0);
    if (cambriab.texture.id == 0)
        cambriab = LoadFontEx("../assets/font/cambriab.ttf", 128, nullptr, 0);
    SetTextureFilter(cambriab.texture, TEXTURE_FILTER_BILINEAR);

    micross = LoadFontEx("font/micross.ttf", 128, nullptr, 0);
    if (micross.texture.id == 0)
        micross = LoadFontEx("../assets/font/micross.ttf", 128, nullptr, 0);
    SetTextureFilter(micross.texture, TEXTURE_FILTER_BILINEAR);

    terminal = LoadFontEx("font/terminal.ttf", 128, nullptr, 0);
    if (terminal.texture.id == 0)
        terminal = LoadFontEx("../assets/font/terminal.ttf", 128, nullptr, 0);
    SetTextureFilter(terminal.texture, TEXTURE_FILTER_BILINEAR);

    LBRITE = LoadFontEx("font/LBRITE.TTF", 128, nullptr, 0);
    if (LBRITE.texture.id == 0)
        LBRITE = LoadFontEx("../assets/font/LBRITE.TTF", 128, nullptr, 0);
    SetTextureFilter(LBRITE.texture, TEXTURE_FILTER_BILINEAR);

    LBRITED = LoadFontEx("font/LBRITED.TTF", 128, nullptr, 0);
    if (LBRITED.texture.id == 0)
        LBRITED = LoadFontEx("../assets/font/LBRITED.TTF", 128, nullptr, 0);
    SetTextureFilter(LBRITED.texture, TEXTURE_FILTER_BILINEAR);

    LBRITEDI = LoadFontEx("font/LBRITEDI.TTF", 128, nullptr, 0);
    if (LBRITEDI.texture.id == 0)
        LBRITEDI = LoadFontEx("../assets/font/LBRITEDI.TTF", 128, nullptr, 0);
    SetTextureFilter(LBRITEDI.texture, TEXTURE_FILTER_BILINEAR);

    LBRITEI = LoadFontEx("font/LBRITEI.TTF", 128, nullptr, 0);
    if (LBRITEI.texture.id == 0)
        LBRITEI = LoadFontEx("../assets/font/LBRITEI.TTF", 128, nullptr, 0);
    SetTextureFilter(LBRITEI.texture, TEXTURE_FILTER_BILINEAR);

    veryla = LoadFontEx("font/veryla.TTF", 128, nullptr, 0);
    if (veryla.texture.id == 0)
        veryla = LoadFontEx("../assets/font/veryla.TTF", 128, nullptr, 0);
    SetTextureFilter(veryla.texture, TEXTURE_FILTER_BILINEAR);

    cartoon = LoadFontEx("font/cartoon.TTF", 128, nullptr, 0);
    if (cartoon.texture.id == 0)
        cartoon = LoadFontEx("../assets/font/cartoon.TTF", 128, nullptr, 0);
    SetTextureFilter(cartoon.texture, TEXTURE_FILTER_BILINEAR);

    beautiful = LoadFontEx("font/beautiful.TTF", 128, nullptr, 0);
    if (beautiful.texture.id == 0)
        beautiful = LoadFontEx("../assets/font/beautiful.TTF", 128, nullptr, 0);
    SetTextureFilter(beautiful.texture, TEXTURE_FILTER_BILINEAR);
}

void UnloadFontResources()
{
    UnloadFont(cambriaz);
    UnloadFont(cambriab);
    UnloadFont(micross);
    UnloadFont(terminal);
    UnloadFont(LBRITE);
    UnloadFont(LBRITED);
    UnloadFont(LBRITEDI);
    UnloadFont(LBRITEI);
    UnloadFont(veryla);
    UnloadFont(cartoon);
    UnloadFont(beautiful);
}