 #pragma once
 #include <raylib.h>

//  constructor, destructor, update method, draw method, spawn method
class MysteryShip{
    public:
        MysteryShip();
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        Rectangle getRect();
        bool alive;

    private:
        Vector2 position;
        Texture2D image;
        int speed;
};