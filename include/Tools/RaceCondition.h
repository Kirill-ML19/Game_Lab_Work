#pragma once
#include "Tool.h"
#include <atomic>
#include <thread>

class RaceCondition : public Tool {
public:
    RaceCondition();
    bool execute(const std::string& target) override;
};