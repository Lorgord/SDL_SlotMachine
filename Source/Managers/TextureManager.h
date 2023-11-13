#pragma once
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>

class TextureManager
{
public:

    static SDL_Texture* LoadTexture(char* path, SDL_Renderer* renderer, int& outHeight, int& outWidth);
    static SDL_Texture* LoadTextureFromText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, int& outHeight, int& outWidth);
    static void DrawTexture(SDL_Texture* texture, const SDL_Rect* scrR, const SDL_Rect* destR, SDL_Renderer* renderer);

    static void GetCenteredTextureXY(int screenW, int screenH, SDL_Rect& outRect);
}; 
