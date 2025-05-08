#include "MissionManager.h"
#include "Missions/EmailMission.h"
#include "Missions/DecodeMission.h"
#include "Missions/NetworkMission.h"
#include "Missions/FinalMission.h"
#include "Tools/BruteForce.h"
#include "Tools/Base64.h"
#include "Tools/PcapAnalyzer.h"
#include "Tools/RaceCondition.h"
#include "Tools/ROT13.h"
#include <iostream>

MissionManager::~MissionManager() {
    for(auto m : missions) delete m;
    for(auto t : playerTools) delete t;
}

void MissionManager::initMissions() {
    missions = {
        new EmailMission(),
        new DecodeMission(),
        new NetworkMission(),
        new FinalMission()
    };
    
    playerTools = {
        new BruteForce(),
        new Base64()
    };
}

void MissionManager::startNextMission() {
    if(currentMission >= missions.size()) {
        std::cout << "All missions completed!\n";
        return;
    }
    
    Mission* mission = missions[currentMission];
    if(mission->execute(playerTools)) {
        currentMission++;
        unlockTool(mission->getReward());
    }
}

void MissionManager::unlockTool(Tool* tool) {
    if (tool!=nullptr) {
        playerTools.push_back(tool);
        std::cout << "New tool unlocked: " << tool->getName() << "!\n";
    }
}

void MissionManager::showAvailableMissions() const {
    std::cout << "\nAvailable Missions:\n";
    for(size_t i = 0; i < missions.size(); i++) {
        std::cout << i+1 << ". " << missions[i]->getDescription();
        if(i < currentMission) std::cout << " [COMPLETED]";
        std::cout << "\n";
    }
}

void MissionManager::showPlayerTools() const {
    std::cout << "\nYour Tools:\n";
    for(auto tool : playerTools) {
        std::cout << "- " << tool->getName() << ": " << tool->getDescription() << "\n";
    }
}