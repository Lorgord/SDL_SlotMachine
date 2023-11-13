#include "FPS_Counter.h"
#include "../Managers/TextureManager.h"

void FPS_Counter::Init(const SDL_Rect& textureRect)
{
    Object::Init(textureRect);
    
    UpdateText(0);
}

void FPS_Counter::Update(float _deltaTime)
{
    static int frameCount;
    static Uint32 lastFrame;
    static Uint32 lastTime;
    
    ++frameCount;
    const Uint32 delayTime = SDL_GetTicks()-lastFrame;
    
    if (delayTime < 1000 / targetFrameRate)
    {
        SDL_Delay(1000 / targetFrameRate - delayTime);
    }

    deltaTime = static_cast<float>(SDL_GetTicks() - lastFrame) / 1000.0f;

    
    lastFrame = SDL_GetTicks();
    if (lastFrame >= lastTime + 1000)
    {
        lastTime = lastFrame;
        UpdateText(frameCount);
        frameCount = 0;
    }

}

void FPS_Counter::UpdateText(int fps)
{
    text.str("");
    text << "FPS: " << fps;
}

void FPS_Counter::Draw(SDL_Renderer* renderer)
{
    SDL_Texture* texture = TextureManager::LoadTextureFromText(text.str(), SDL_Color{}, textFont, renderer, objDestR.h, objDestR.w);
    TextureManager::DrawTexture(texture, nullptr, &objDestR, renderer);
    SDL_DestroyTexture(texture);
}

