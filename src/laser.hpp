// safety measure to make sure the file is not included more than once.
#pragma once


#include <raylib.h>

class Laser{
    public:
        Laser(Vector2 position, int speed);
        void Update();
        void Draw();
        Rectangle getRect();
        // to know if laser move out of the screen to kill it and save computer memory
        bool active;

    private:
        Vector2 position;
        int speed;
};