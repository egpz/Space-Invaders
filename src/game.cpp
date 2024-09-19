#include "game.hpp"
#include <iostream>
#include <fstream>


Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game(){
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

//update function run 60 times per second
//  the random interval (like 15 seconds) remains fixed during each frame until the MysteryShip spawns
void Game::Update(){
    if(run){

    // GetTime is a raylib function tha return the total time has passed since the program began running
    double currentTime = GetTime();  // Get the current time (in seconds since the game started)
    double elapsedTime = currentTime - gameStartTime;  // Calculate elapsed time since game started

    if (elapsedTime - timeLastSpawn > mysteryShipSpawnInterval) {
        mysteryship.Spawn();  // Spawn the MysteryShip
        timeLastSpawn = elapsedTime;  // Reset the last spawn time to the current time
        mysteryShipSpawnInterval = GetRandomValue(10, 20);  // Set a new random interval for the next spawn
    }
    
    for(auto& laser: spaceship.lasers){
        laser.Update();
    }

    MoveAliens();

    AlienShootLaser();

    for(auto& laser: alienLasers){
        laser.Update();
    }

    DeleteInactiveLasers(); 
    mysteryship.Update();

    CheckForCollisions();
    } else{
        if(IsKeyDown(KEY_ENTER)){
            Reset();
            InitGame();
        }
    }
    // std::cout << "Vecotor Size: " <<  spaceship.lasers.size() << std::endl;
}

void Game::Draw(){
    spaceship.Draw();

    for(auto& laser: spaceship.lasers){
        laser.Draw();
    }

    for(auto& obstacle: obstacles){
        obstacle.Draw();
    }

    for(auto& alien: aliens){
        alien.Draw();
    }

    for(auto& laser: alienLasers){
        laser.Draw();
    }

    mysteryship.Draw();

}

void Game::HandleInput(){
    if(run){
        if(IsKeyDown(KEY_LEFT)){
            spaceship.MoveLeft();
        }
        else if(IsKeyDown(KEY_RIGHT)){
            spaceship.MoveRight();
        }
        else if(IsKeyDown(KEY_SPACE)){
            spaceship.FireLaser();
        }
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it !=spaceship.lasers.end();){
        if(!it ->active){
            it = spaceship.lasers.erase(it);
    }
        else{
            ++it;
        }
    }

    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if(!it ->active){
            it = alienLasers.erase(it);
    }
        else{
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles(){
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for(int i = 0; i < 4; i++){
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;

}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row = 0; row < 5; row++){
        for(int column = 0; column < 11; column++){

            int alienType;
            if(row == 0){
                alienType = 3;
            }else if (row == 1 || row ==2){
                alienType =2;
            }else{
                alienType =1;
            }

            float x = column * 55 + 75;
            float y = row * 55 + 110;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }   
    return aliens;
}

void Game::MoveAliens(){
    for(auto& alien: aliens){
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25){
            aliensDirection = -1;
            MoveDownAliens(4); 
        }
        if(alien.position.x < 25){
            aliensDirection = 1;
            MoveDownAliens(4); 
        }
        alien.Update(aliensDirection);
    }
}

// method to move down aliens
void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens){
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{   
    double currentTime = GetTime();
    if(currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        // indexing the vector contain all aliens
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        // get random alien object
        Alien & alien = aliens[randomIndex];
        // center of the alien image in x ais and bottom of the alien image in y axis
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                                    alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{
    //spaceship lasers

    // use an iterator to check for GetCollisions
    for(auto& laser: spaceship.lasers){
        // iterator point to the beginning of the aliens vector
        auto iterator = aliens.begin();
        // until we reach the end of the vector
        while(iterator != aliens.end()){
            //we need to check if the laser collides with the alien the iterator points to
            if(CheckCollisionRecs(iterator -> getRect(), laser.getRect())){
               PlaySound(explosionSound);
               if(iterator ->type == 1){
                score += 100;
               } else if(iterator ->type == 2){
                   score += 200;
               } else if(iterator ->type == 3){
                   score += 300;
               }
               CheckForHighScore();
               
               // this line removes the alien in which the iterator is pointing and updates the iterator to point to the next element in the vector
                iterator = aliens.erase(iterator);
                laser.active = false;
            }//if there was no collision we move the iterator to point to next alien in the vector
            else{
                ++iterator;
            }
        }

        for(auto& obstacle: obstacles){
            auto iterator = obstacle.blocks.begin();
            while(iterator != obstacle.blocks.end()){
                if(CheckCollisionRecs(iterator -> getRect(), laser.getRect())){
                    iterator = obstacle.blocks.erase(iterator);
                    laser.active = false;
                } else{
                    ++iterator;
                }
            }
        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            CheckForHighScore();
            PlaySound(explosionSound);
        }   
    }

    // alien lasers, we loop through all the aliens lasers that are stored in alienlasers vector
    for(auto& laser: alienLasers){
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            std::cout << "Spaceship hit by Alien Laser!" << std::endl;
            lives --;
            if(lives == 0){
                GameOver();
            }
        }
           for(auto& obstacle: obstacles){
            auto iterator = obstacle.blocks.begin();
            while(iterator != obstacle.blocks.end()){
                if(CheckCollisionRecs(iterator -> getRect(), laser.getRect())){
                    iterator = obstacle.blocks.erase(iterator);
                    laser.active = false;
                } else{
                    ++iterator;
                }
            }
        }
    }

    //alien collision with obstacle

    for(auto& alien: aliens){
        for(auto& obstacle: obstacles){
            auto iterator = obstacle.blocks.begin();
            while(iterator != obstacle.blocks.end()){
                if(CheckCollisionRecs(iterator -> getRect(), alien.getRect())){
                        iterator = obstacle.blocks.erase(iterator);
                } else{
                        iterator ++;
                }
            }
        }

        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())){
            std::cout << "Spaceship hit directly by Alien!" << std::endl;
            GameOver();
        }
    } 
}

void Game::GameOver()
{
    run = false;
    std::cout << "Game Over!" << std::endl;
}
void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    timeLastSpawn = 0.0;

    gameStartTime = GetTime();  // Save the game start time
    timeLastSpawn = 0.0;  // Ensure timeLastSpawn starts from 0

    lives = 3;
    score = 0;
    highscore = LoadHighScoreFromFile();
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    mysteryship.alive = false;

}

void Game::CheckForHighScore()
{
    if(score > highscore){
        highscore = score;
        SaveHighScoreToFile(highscore);
    }
}

void Game::SaveHighScoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cout << "Failed to open highscore file" << std::endl;
    }
}

int Game::LoadHighScoreFromFile(){
    int loadedHighScore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile >> loadedHighScore;
        highscoreFile.close();
    } else {
        std::cout << "Failed to open highscore file" << std::endl;
    }
    return loadedHighScore;
}

void Game::Reset(){
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    // Reset MysteryShip's spawn timer
    timeLastSpawn = 0.0;  // Reset the spawn time to the beginning
    mysteryship.alive = false;  
}
