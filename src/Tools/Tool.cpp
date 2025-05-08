#include "Tools/Tool.h"

Tool::Tool(ToolType t, std::string n, std::string d) 
    : type(t), name(std::move(n)), description(std::move(d)) {}