#pragma once
#include "StoryManager.h"
#include "MissionManager.h"

class Game {
    StoryManager story;
    MissionManager missions;
    bool running = true;
    
public:
    void run();
    void handleInput(int choice);
    void exitGame() { running = false; }
};