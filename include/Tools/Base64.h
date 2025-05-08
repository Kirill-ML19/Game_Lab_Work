#pragma once
#include "Tool.h"
#include <string>

class Base64 : public Tool {
public:
    Base64();
    bool execute(const std::string& target) override;
    static std::string base64_decode(const std::string& in);
};