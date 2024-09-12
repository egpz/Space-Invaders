#include "raylib.h"
#include "game.hpp"


int main() 
{

    // initialize the window
    InitWindow(800, 600, "Space Invader");
    SetTargetFPS(60);

    // create objects
    Game game;

    // main game loop
    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.Draw();
        DrawText("Welcome to Space Invader", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // destroy window, close window and OpenGL context
    CloseWindow();

    return 0;
}
