#pragma once
#include <raylib.h>

class Alien{
    public:
        Alien(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        // get the type of aliens
        int GetType();
        static void UnloadImages();
        Rectangle getRect();
        // array of 3 images, common amoung all objects and only will be intialize once, when alien object is created it will load the images in this arrtribute, and each alien object will use these images at one and won't load them again
        static Texture2D alienImages[3];
        int type;
        Vector2 position;

    private:
};