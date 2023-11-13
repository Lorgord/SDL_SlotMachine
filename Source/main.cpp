#include <string>

#include "Game.h"

Game* game = nullptr;

int main( int argc, char* args[] )
{
    game = new Game();
    game->Init("GameWindow", 1024, 720, false);
    
    while (game->IsRunning())
    {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();
    
    return 0;
}