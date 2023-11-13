#pragma once


#include <SDL_render.h>
#include <vector>

#include "Object.h"


class Reel : public Object
{
public:

    void Init(const SDL_Rect& textureRect) override;
    void Init(const SDL_Rect& textureRect, int _reelIndex);
    void Update(float _deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void Start(int _rotationSpeed);
    void Stop();
    void UpdateTimer(float _deltaTime);
    int FindClosestStopLocation() const;
    float CalculateVelocity(float _deltaTime);
    void Move(float _velocity);

    void MoveRectFromScreenBottom();
    const SDL_Rect* CopyRectWithOffset(const SDL_Rect* rectToCopy) const;

    void SetOwner(class Game* Owner) { OwningGame = Owner; }
    
    int reelIndex = NULL;

private:
    Game* OwningGame = nullptr;
    
    bool isEnabled = false;
    bool isWantsToStop = false;

    float timeToRotate = 4.0f;
    float elapsedTime = NULL;
    float rotationSpeed = NULL;

    float tempVelocity = NULL;
    
    int initialY = NULL;

    int targetSectionLocationY = NULL;
    int prizeSectionsAmount = 6;
    std::vector<int> prizeSectionsY;
};
