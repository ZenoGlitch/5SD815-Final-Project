#include "raylib.h"
#include "game.h"
#include "window.h"
#include <iostream>

//TODO: const members are nono. static const is fine. 

int main(void)
{    
    try {
        Window window;
        Game game; 

        while (!window.ShouldClose())
        {
            game.Update();
            game.Render();
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception. Exiting." << std::endl;
    }
    return 0;
}