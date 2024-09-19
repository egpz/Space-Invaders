#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        Rectangle getRect();
        void Reset();
        std::vector<Laser> lasers;

    private:
        Texture2D image;
        Vector2 position;
        // this attribute will hold the time in seconds when last laser fired so can only fire certain amount in certain seconds so laser won't be crazy long
        double lastFireTime;
        Sound laserSound;
};