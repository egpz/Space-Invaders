#include "raylib.h"
#include "game.hpp"
#include <string>


std::string FormatWithLeadingZeros(int number, int width){
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() 
{
    Color yellow = {243, 216, 63, 255};
    // Color green = {0, 255, 0, 255}; 
    int offset = 50;
    int windowWidth = 750;
    int  windowHeight = 700;
    // initialize the window
    InitWindow(windowWidth + offset, windowHeight + 2* offset, "Space Invader");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    // create objects
    Game game;


    // main game loop
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        // DrawText("Welcome to Space Invader", 190, 200, 20, WHITE);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        if(game.run){
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } else{
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50.0;
        for(int i = 0; i < game.lives; i++){
            DrawTexture(spaceshipImage, x, 745, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string highScoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highScoreText.c_str(), {655, 40}, 34, 2, yellow);

        
        game.Draw();
        EndDrawing();
    }

    // destroy window, close window and OpenGL context
    CloseWindow();
    CloseAudioDevice();

    return 0;
}
