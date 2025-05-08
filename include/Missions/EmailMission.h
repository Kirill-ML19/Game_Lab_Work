#pragma once
#include "Mission.h"

class EmailMission : public Mission {
public:
    EmailMission();  
    bool execute(const std::vector<Tool*>& tools) override;
};