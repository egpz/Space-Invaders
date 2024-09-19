# Space-Invaders
retro Space Invaders Game built in C++, we use the graphic library of raylib


to run the game, first clone the repo, then follow the steps:


1. for mac, ``` brew install raylib ```
   
   Linux, ```sudo apt-get install raylib-dev```
   
   Windows, download and follow steps from: https://www.raylib.com/

2. mac and Linux: ```make```.

   for Windows: ```g++ -std=c++17 -Wall -I<path_to_raylib_include> src/main.cpp src/spaceship.cpp src/game.cpp src/laser.cpp src/obstacle.cpp -o space_invader -L<path_to_raylib_lib> -lraylib -lopengl32 -lgdi32 -lwinmm```


3. mac and Linux: ```./space_invader```,
   Windows: ```space_invader.exe```

