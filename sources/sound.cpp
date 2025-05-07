#include "raylib.h"

Sound paperSound     = {nullptr};
Sound eldenringSound = {nullptr};
Sound anno1800       = {nullptr};
Sound anno1801       = {nullptr};
Sound anno1802       = {nullptr};
Sound anno1803       = {nullptr};
Sound milestone      = {nullptr};
Sound screenshotSound= {nullptr};
Music pureimagination= {nullptr};



void LoadSoundResources()
{
    InitAudioDevice();


    paperSound = LoadSound("sound/paper.wav");
    if (paperSound.stream.buffer == nullptr)
    {
        paperSound = LoadSound("../assets/sound/paper.wav");
    }

    eldenringSound = LoadSound("sound/eldenring.wav");
    if (eldenringSound.stream.buffer == nullptr)
    {
        eldenringSound = LoadSound("../assets/sound/eldenring.wav");
    }

    anno1800 = LoadSound("sound/anno1800.wav");
    if (anno1800.stream.buffer == nullptr)
    {
        anno1800 = LoadSound("../assets/sound/anno1800.wav");
    }

    anno1801 = LoadSound("sound/anno1801.wav");
    if (anno1801.stream.buffer == nullptr)
    {
        anno1801 = LoadSound("../assets/sound/anno1801.wav");
    }

    anno1802 = LoadSound("sound/anno1802.wav");
    if (anno1802.stream.buffer == nullptr)
    {
        anno1802 = LoadSound("../assets/sound/anno1802.wav");
    }

    anno1803 = LoadSound("sound/anno1803.wav");
    if (anno1803.stream.buffer == nullptr)
    {
        anno1803 = LoadSound("../assets/sound/anno1803.wav");
    }

    milestone = LoadSound("sound/milestone.wav");
    if (milestone.stream.buffer == nullptr)
    {
        milestone = LoadSound("../assets/sound/milestone.wav");
    }

    screenshotSound = LoadSound("sound/screenshot.wav");
    if (screenshotSound.stream.buffer == nullptr)
    {
        screenshotSound = LoadSound("../assets/sound/screenshot.wav");
    }

    pureimagination = LoadMusicStream("sound/pure_imagination.wav");
    if (pureimagination.stream.buffer ==nullptr)
    {
        pureimagination = LoadMusicStream("../assets/sound/pure_imagination.wav");
    }

    

}

void UnloadSoundResources()
{
    UnloadSound(paperSound);
    UnloadSound(eldenringSound);
    UnloadSound(anno1800);
    UnloadSound(anno1801);
    UnloadSound(anno1802);
    UnloadSound(anno1803);
    UnloadSound(milestone);
    UnloadSound(screenshotSound);
    UnloadMusicStream(pureimagination);
    CloseAudioDevice();
}