#pragma once
#include <vector>
#include <string>
#include "Tools/Tool.h"

class Mission {
protected:
    std::string name;
    std::string description;
    std::vector<ToolType> requiredTools;
    bool completed = false;
    Tool* reward = nullptr;

public:
    Mission(const std::string& name, 
           const std::string& desc,
           const std::vector<ToolType>& requiredTools,
           Tool* reward = nullptr);
    virtual ~Mission();

    virtual bool execute(const std::vector<Tool*>& playerTools) = 0;
    bool isCompleted() const { return completed; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    Tool* getReward() const { return reward; }
};