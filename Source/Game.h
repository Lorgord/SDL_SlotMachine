#pragma once

#include <random>

#include "SDL.h"
#include <vector>

#include "Objects/Reel.h"
#include "Objects/Background.h"
#include "Objects/Button.h"
#include "Objects/FPS_Counter.h"


class Game
{
public:
    
    void Init(const char* title, int width, int height, bool fullscreen);
    
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool IsRunning() const { return bIsRunning; }
    
    void OnCompleteRoll(Reel* reel);
    std::mt19937 GenerateRandomNums();
    
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    
    std::vector<Reel> reels;
    Button button;
    Background background;
    FPS_Counter fps_counter;

private:
    
    bool bIsRunning = false;
    SDL_Window *window = nullptr;
};
