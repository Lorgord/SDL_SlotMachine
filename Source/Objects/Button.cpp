#include "Button.h"

#include "../Managers/TextureManager.h"


void Button::Init(const SDL_Rect& textureRect)
{
    objSrcR.h = textureRect.h / 2;
    objSrcR.w = textureRect.w;
    objSrcR.y = objSrcR.h;

    objDestR.h = 100;
    objDestR.w = 400;
    objDestR.x = textureRect.x  - objDestR.w / 2;
    objDestR.y = textureRect.y;
}

void Button::Update(float _deltaTime)
{
    if ( flickeringSpeed <= 0.0f || !isEnabled ) return;
    
    tempDelta += _deltaTime;
    
    if (tempDelta >= flickeringSpeed)
    {
        objSrcR.y = isBlinked ? 0 : objSrcR.h;
        isBlinked = !isBlinked;
        tempDelta = 0.0f;
    }
}

void Button::Draw(SDL_Renderer* renderer)
{
    TextureManager::DrawTexture(objTexture, &objSrcR, &objDestR, renderer);
}

void Button::ChangeState(const bool _isEnabled)
{
    isEnabled = _isEnabled;
    
    objSrcR.y = isEnabled ? objSrcR.h : 0;
}

bool Button::HandleInput()
{
    if (!isEnabled) return false;
    
    int cursorX, cursorY;
    SDL_GetMouseState(&cursorX, &cursorY);

    if (cursorX < objDestR.x || cursorY < objDestR.y)
    {
        return false;
    }
    if (cursorX > objDestR.x + objDestR.w || cursorY > objDestR.y + objDestR.h)
    {
        return false;
    }

    ChangeState(false);
    return true;
}
