#pragma once
#include "Mission.h"

class FinalMission : public Mission {
public:
    FinalMission();
    bool execute(const std::vector<Tool*>& playerTools) override;
};