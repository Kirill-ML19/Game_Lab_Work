#include "Missions/FinalMission.h"
#include "Tools/RaceCondition.h"
#include "Tools/ROT13.h"
#include <iostream>

FinalMission::FinalMission() : 
    Mission("Final Hack", "Breach OmniCore's mainframe",
           {ToolType::RaceCondition, ToolType::ROT13}) {}

bool FinalMission::execute(const std::vector<Tool*>& tools) {
    std::cout << "\n=== ФИНАЛЬНАЯ МИССИЯ ===\n";
    bool hasRace = false, hasROT = false;
    
    for(auto tool : tools) {
        if(tool->getType() == ToolType::RaceCondition) hasRace = true;
        if(tool->getType() == ToolType::ROT13) hasROT = true;
    }

    if(!hasRace || !hasROT) {
        std::cout << "Отсутствуют необходимые инструменты!\n";
        return false;
    }

    std::cout << "Объединение эксплойтов ROT13 и Race Condition...\n";
    return true;
}