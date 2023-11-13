#pragma once
#include "Object.h"

class Background : public Object
{
public:

    void Draw(SDL_Renderer* renderer) override;
};
