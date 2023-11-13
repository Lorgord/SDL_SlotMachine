#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

class Object
{
public:
    
    Object() {}
    virtual ~Object() {}

    virtual void Init(const SDL_Rect& textureRect) { objDestR = textureRect; }
    virtual void Update(float _deltaTime) {}
    virtual void Draw(SDL_Renderer* renderer) {}
    
    void SetTexture(SDL_Texture* texture) { objTexture = texture; }

protected:

    SDL_Rect objSrcR = {};
    SDL_Rect objDestR = {};
    SDL_Texture* objTexture = nullptr;
};
