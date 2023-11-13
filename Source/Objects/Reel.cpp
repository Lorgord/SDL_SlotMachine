#include "Reel.h"


#include "../Game.h"
#include "../Managers/TextureManager.h"


void Reel::Init(const SDL_Rect& textureRect)
{
    Object::Init(textureRect);
    initialY = textureRect.y;

    const int prizeSectionOffsetY = objDestR.h / prizeSectionsAmount;
    const int initialPrizeSectionY = prizeSectionOffsetY / 2;
    
    prizeSectionsY.reserve(prizeSectionsAmount);
    
    for (int i = 0; i < prizeSectionsAmount; ++i)
    {
        prizeSectionsY.push_back(initialPrizeSectionY + prizeSectionOffsetY * i);
    }
}

void Reel::Init(const SDL_Rect& textureRect, int _reelIndex)
{
    Init(textureRect);

    reelIndex = _reelIndex; 
    timeToRotate += _reelIndex * 0.3f;
}

void Reel::Start(const int _rotationSpeed)
{
    rotationSpeed = static_cast<float>(_rotationSpeed);
    
    targetSectionLocationY = NULL;
    isWantsToStop = false;
    isEnabled = true;
}

void Reel::Stop()
{
    isEnabled = false;

    if (OwningGame != nullptr)
    {
        OwningGame->OnCompleteRoll(this);
    }
}

void Reel::Update(float _deltaTime)
{
    if (!isEnabled) return;

    UpdateTimer(_deltaTime);
    
    Move(CalculateVelocity(_deltaTime));

    MoveRectFromScreenBottom();
}


void Reel::UpdateTimer(float _deltaTime)
{
    if (isWantsToStop) return;
    
    elapsedTime += _deltaTime;
    
    if (elapsedTime >= timeToRotate)
    {
        isWantsToStop = true;
        elapsedTime = 0.0f;
    }
}

float Reel::CalculateVelocity(float _deltaTime)
{
    float vector = 1.0f;
    
    if (isWantsToStop)
    {
        if (targetSectionLocationY == NULL)
        {
            targetSectionLocationY = FindClosestStopLocation();
        }
        
        const int distance = targetSectionLocationY - objDestR.y;
        vector = distance * 0.005f;
    }
    
    return vector * (rotationSpeed * _deltaTime);
}

void Reel::Move(float _velocity)
{
    if (_velocity == 0.0f && isWantsToStop)
    {
        Stop();
        return;
    }
    
    tempVelocity += _velocity;

    if (abs(tempVelocity) >= 1.0f)
    {
        const int pixelsToMove = tempVelocity;
        
        tempVelocity -= pixelsToMove;
        objDestR.y += pixelsToMove;
    }
}


int Reel::FindClosestStopLocation() const
{
    const bool isNegative = objDestR.y < initialY;

    const int tempSign = isNegative ? -1 : 1;
    const int offset = isNegative ? -initialY : initialY;
    
    const int prizeSectionOffsetY = objDestR.h / prizeSectionsAmount / 2;
    const int currentSection = abs(objDestR.y - offset)  / prizeSectionOffsetY;
    int sectionIndex = currentSection / 2;

    if (sectionIndex >= prizeSectionsY.size())
    {
        sectionIndex = 0;
    }
    return prizeSectionsY[sectionIndex] * tempSign;
}


void Reel::MoveRectFromScreenBottom()
{
    if (objDestR.y > initialY + objDestR.h)
    {
        objDestR.y -= objDestR.h * 2;
    }
}

const SDL_Rect* Reel::CopyRectWithOffset(const SDL_Rect* rectToCopy) const
{
    static SDL_Rect copyRect;
    copyRect = *rectToCopy;
    
    if (copyRect.y > initialY)
    {
        copyRect.y -= copyRect.h;
        return &copyRect;
    }
    
    copyRect.y += copyRect.h;
    return &copyRect;
}

void Reel::Draw(SDL_Renderer* renderer)
{
    TextureManager::DrawTexture(objTexture, nullptr, &objDestR, renderer);
    TextureManager::DrawTexture(objTexture, nullptr, CopyRectWithOffset(&objDestR), renderer);
}

