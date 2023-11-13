#include "Background.h"
#include "../Managers/TextureManager.h"



void Background::Draw(SDL_Renderer* renderer)
{
    TextureManager::DrawTexture(objTexture, nullptr, &objDestR, renderer);
}
