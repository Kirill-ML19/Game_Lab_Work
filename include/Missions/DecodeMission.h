#pragma once
#include "Mission.h"
#include "Tools/ROT13.h"

class DecodeMission : public Mission {
public:
    DecodeMission();
    bool execute(const std::vector<Tool*>& playerTools) override;
};