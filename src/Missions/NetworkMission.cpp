#include "Missions/NetworkMission.h"
#include "Tools/PcapAnalyzer.h"
#include "Tools/RaceCondition.h"
#include <iostream>

NetworkMission::NetworkMission() : 
    Mission(
        "Network Analysis",
        "Analyze OmniCore's network traffic",
        {ToolType::PcapAnalyzer},
        new RaceCondition()
    ) {}

bool NetworkMission::execute(const std::vector<Tool*>& tools) {
    std::cout << "\n=== МИССИЯ АНАЛИЗА СЕТИ ===\n";
    
    for(auto tool : tools) {
        if(tool->getType() == ToolType::PcapAnalyzer) {
            return tool->execute("traffic.pcap");
        }
    }
    
    std::cout << "Требуемый инструмент недоступен!\n";
    return false;
}