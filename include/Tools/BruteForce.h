#pragma once
#include "Tool.h"

class BruteForce : public Tool {
public:
    BruteForce();
    bool execute(const std::string& target) override;
};