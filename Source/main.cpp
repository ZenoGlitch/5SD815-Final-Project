#include "raylib.h"
#include "game.h"

// TODO: Remove unnecessary comments
constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

int main(void)
{    
    InitWindow(screenWidth, screenHeight, "SPACE INVADERS"); // TODO: Make window into an RAII class

    SetTargetFPS(60);

    Game game = { State::STARTSCREEN }; // TODO: if gamestate is going to be used, maybe initialize in the constructor?

    while (!WindowShouldClose())
    {
        game.Update();
        
        BeginDrawing();
        ClearBackground(BLACK);  

        game.Render();

        EndDrawing();
    }

    CloseWindow();

    std::string filename = "level.txt";  

    return 0;
}