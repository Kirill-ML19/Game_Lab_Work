#include "Missions/EmailMission.h"
#include "Mission.h"
#include "Tools/BruteForce.h"
#include "Tools/ROT13.h"
#include <iostream>

EmailMission::EmailMission() : 
    Mission(
        "Email Server Hack",
        "Breach OmniCore's email system",
        {ToolType::BruteForce},
        new ROT13()
    ) {}

bool EmailMission::execute(const std::vector<Tool*>& tools) {
    std::cout << "\n=== МИССИЯ СЕРВЕРА ЭЛЕКТРОННОЙ ПОЧТЫ ===\n";
    
    for(auto tool : tools) {
        if(tool->getType() == ToolType::BruteForce) {
            return tool->execute("smtp.omnicore.com");
        }
    }
    
    std::cout << "Требуемый инструмент недоступен!\n";
    return false;
}