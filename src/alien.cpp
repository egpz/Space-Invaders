#include "alien.hpp"

// define the static varibale and initialize it
Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
    // assign the value we got to the proper attribute
    this -> type = type;
    this -> position = position;

    if(alienImages[type-1].id == 0)

    switch (type){
        case 1:
            alienImages[0]= LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        default:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
    }

}

void Alien::Draw(){
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType(){
    return type;
}

void Alien::UnloadImages(){
    for(int i = 0; i < 4; i++){
    UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::getRect()
{
    return {position.x, position.y,
    float(alienImages[type - 1].width),
    float(alienImages[type - 1].height)
    };
}

// argument direction update the direction
void Alien::Update(int direction){
    position.x += direction;
}