#include "Mission.h"

Mission::Mission(const std::string& name, const std::string& desc,
               const std::vector<ToolType>& tools, Tool* reward)
    : name(name), description(desc), requiredTools(tools), reward(reward) {}

Mission::~Mission() {
    if(reward) delete reward;
}