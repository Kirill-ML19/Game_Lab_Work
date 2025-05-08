#pragma once
#include "Tool.h"

class ROT13 : public Tool {
public:
    ROT13();
    bool execute(const std::string& target) override;
};