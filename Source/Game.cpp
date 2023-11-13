#include "Game.h"

#include <iostream>
#include <random>
#include <SDL_ttf.h>

#include "Objects/Reel.h"
#include "Managers/TextureManager.h"


void Game::Init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 120, 120, 120,255);
        }

        bIsRunning = true;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "Error : SDL_TTF" << std::endl;
    }

    //Objects initialize//

    //reels init//
    SDL_Rect reelRect;
    SDL_Texture* reelTexture = TextureManager::LoadTexture("Content/Textures/Pattern.png", renderer, reelRect.h, reelRect.w);
    TextureManager::GetCenteredTextureXY(width, height, reelRect);
    
    const int reelsAmount = 5;
    const int initialRealPosX = reelRect.w * reelsAmount / 2 - reelRect.w / 2;
    reelRect.x -= initialRealPosX;
    
    reels.reserve(reelsAmount);
    for (int i = 0; i < reelsAmount; ++i)
    {
        Reel newReel;
        newReel.SetTexture(reelTexture);
        newReel.SetOwner(this);
        newReel.Init(reelRect, i);
        reelRect.x += reelRect.w;
        reels.push_back(newReel);
    }

    
    //button init//
    SDL_Rect buttonRect{};
    button.SetTexture(TextureManager::LoadTexture("Content/Textures/PlayButton.png", renderer, buttonRect.h, buttonRect.w));
    buttonRect.x = width / 2;
    buttonRect.y = 560;
    button.Init(buttonRect);


    //fps counter init//
    const SDL_Rect fps_rect {100, 600, 0, 0};
    fps_counter.SetFont(TTF_OpenFont("Content/Fonts/font.ttf", 28));
    fps_counter.Init(fps_rect);

    
    //background init//
    SDL_Rect backgroundRect{};
    background.SetTexture(TextureManager::LoadTexture("Content/Textures/Background.png", renderer, backgroundRect.h, backgroundRect.w));
    background.Init(backgroundRect);
}

void Game::OnCompleteRoll(Reel* reel)
{
    if (reels.size() -1 == reel->reelIndex)
    {
        button.ChangeState(true);
    }
}

void Game::HandleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        {
            bIsRunning = false;
            break;
        }
    case SDL_MOUSEBUTTONDOWN:
        {
            if (button.HandleInput()) //or add observer and subscribe button
            {
                std::uniform_int_distribution<> distribution(500, 1200);
                auto randomNums = GenerateRandomNums();
                
                for (auto& reel : reels)
                {
                    reel.Start(distribution(randomNums));
                }
            }
            break;
        }
        
    default:
        {
            break;
        }
    }
}

void Game::Update()
{
    const float deltaTime = fps_counter.GetDeltaTime();
    
    fps_counter.Update(deltaTime);
    button.Update(deltaTime);
    
    for (auto& reel : reels)
    {
        reel.Update(deltaTime);
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    
    for (auto& reel : reels)
    {
        reel.Draw(renderer);
    }

    background.Draw(renderer);

    button.Draw(renderer);
    fps_counter.Draw(renderer);
    
    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

std::mt19937 Game::GenerateRandomNums()
{
    std::random_device device;
    const std::mt19937 rng(device());
    return rng;
}
