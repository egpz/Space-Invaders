// game class header file
#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"


class Game{
    public:
        // if we need to access to if from game.coo file later on, make it public method
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        // run determine if the game should run, if dies after 3 times no run
        bool run;
        int lives;
        int score; 
        int highscore;
        Music music;

    
    private:
        void DeleteInactiveLasers();
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        //select a random alien to shoot laser
        void AlienShootLaser();
        void CheckForCollisions();
        void GameOver();
        void Reset();
        void InitGame();
        void CheckForHighScore();
        void SaveHighScoreToFile(int highScore);
        int LoadHighScoreFromFile();    
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        // a vector that hold all the aliens
        std::vector<Alien> aliens;
        int aliensDirection;
        //vector hold all aliens lasers
        std::vector<Laser> alienLasers;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeLastAlienFired; 
        MysteryShip mysteryship;
        //hold the interval at which the mystery ship will appear, won't be constant will change
        float mysteryShipSpawnInterval;
        // hold the time mysteryship was spawned
        float timeLastSpawn;
        Sound explosionSound;
        double gameStartTime;
};