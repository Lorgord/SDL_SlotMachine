#pragma once
#include <iosfwd>
#include <SDL_ttf.h>
#include <sstream>

#include "Object.h"

class FPS_Counter : Object
{
public:

    void Init(const SDL_Rect& textureRect) override;
    void Update(float _deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetFont(TTF_Font* font) { textFont = font; }
    void UpdateText(int fps);
    float GetDeltaTime() const { return deltaTime; }

private:

    Uint32 targetFrameRate = 120;

    float deltaTime = 0.0f;

    TTF_Font* textFont = nullptr;
    std::stringstream text{};
};
