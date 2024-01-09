#include "raylib.h"
#include "game.h"
#include "window.h"

int main(void)
{    
    Window window;

    SetTargetFPS(60);

    Game game = { State::STARTSCREEN }; // TODO: if gamestate is going to be used, maybe initialize in the constructor?

    while (!window.ShouldClose())
    {
        game.Update();
        
        BeginDrawing();
        ClearBackground(BLACK);  

        game.Render();

        EndDrawing();
    }

    std::string filename = "level.txt";  

    return 0;
}