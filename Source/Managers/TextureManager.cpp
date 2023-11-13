#include "TextureManager.h"

#include <cstdio>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Texture* TextureManager::LoadTexture(char* path, SDL_Renderer* renderer, int& outHeight, int& outWidth)
{
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path);

    if( loadedSurface == nullptr)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        outHeight = loadedSurface->h;
        outWidth = loadedSurface->w;
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

SDL_Texture* TextureManager::LoadTextureFromText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, int& outHeight, int& outWidth)
{
    SDL_Texture* newTexture = nullptr;
    
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( newTexture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            outWidth = textSurface->w;
            outHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    
    return newTexture;
}

void TextureManager::DrawTexture(SDL_Texture* texture, const SDL_Rect* scrR, const SDL_Rect* destR, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, scrR, destR);
}

void TextureManager::GetCenteredTextureXY(int screenW, int screenH, SDL_Rect& outRect)
{
    outRect.x = screenW / 2 - outRect.w / 2;
    outRect.y = screenH / 2 - outRect.h / 2;
}
