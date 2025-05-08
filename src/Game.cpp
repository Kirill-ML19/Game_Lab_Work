#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>

void Game::run() {
    story.showPrologue();
    story.showIntro(); 
    missions.initMissions();

    while(running) {
        story.showMissionIntro(missions.getCurrentMissionId());
        missions.showAvailableMissions();
        
        int choice;
        std::cout << "\n1. Начать миссию\n2. Показать инструменты\n3. Выход\n> ";
        std::cin >> choice;
        handleInput(choice);
    }
    std::cout << "Конец игры!\n";
}

void Game::handleInput(int choice) {
    switch(choice) {
        case 1: missions.startNextMission(); break;
        case 2: missions.showPlayerTools(); break;
        case 3: exitGame(); break;
        default: std::cout << "Неверный выбор!\n";
    }
}
