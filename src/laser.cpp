#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
    this->position = position;
    this->speed = speed;
    active = true;
}

void Laser::Draw(){
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, {0, 255, 0, 255});
}

// create a new rectangle object, set the x and y position it's width and height, return the rectangle
Rectangle Laser::getRect()
{   
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update(){
    // move the laser up by provide a negative value
    position.y += speed;
    if(active){
        if(position.y > GetScreenHeight() - 100 || position.y <  25){
            active = false;
            std::cout << "Laser is not active" << std::endl;
        }
    }
}