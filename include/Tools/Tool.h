#pragma once
#include <string>
#include <utility>

enum class ToolType { BruteForce, Base64, ROT13, PcapAnalyzer, RaceCondition };

class Tool {
protected:
    ToolType type;
    std::string name;
    std::string description;
    
public:
    Tool(ToolType t, std::string n, std::string d);
    virtual ~Tool() = default;
    
    virtual bool execute(const std::string& target) = 0;
    ToolType getType() const { return type; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
};