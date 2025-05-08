#pragma once
#include <vector>
#include "Mission.h"
#include "Tools/Tool.h"

class MissionManager {
    std::vector<Mission*> missions;
    std::vector<Tool*> playerTools;
    size_t currentMission = 0;
    
    void unlockTool(Tool* tool);
    
public:
    void initMissions();
    void startNextMission();
    void showAvailableMissions() const;
    void showPlayerTools() const;
    ~MissionManager();
    size_t getCurrentMissionId() const { return currentMission; }
};