#pragma once
#include "Mission.h"
#include "Tools/RaceCondition.h"

class NetworkMission : public Mission {
public:
    NetworkMission(); 
    bool execute(const std::vector<Tool*>& playerTools) override;
};