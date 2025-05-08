#pragma once
#include "Tool.h"

class PcapAnalyzer : public Tool {
public:
    PcapAnalyzer();
    bool execute(const std::string& target) override;
};