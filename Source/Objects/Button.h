#pragma once
#include <SDL_rect.h>

#include "Object.h"

class Button : public Object
{
public:

    void Init(const SDL_Rect& textureRect) override;
    void Update(float _deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void ChangeState(const bool _isEnabled);
    bool HandleInput();


private:

    float tempDelta = 0;
    float flickeringSpeed = 0.5f;

    bool isEnabled = true;
    bool isBlinked = false;
};
