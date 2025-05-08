#include "Tools/ROT13.h"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>  

ROT13::ROT13() : Tool(ToolType::ROT13, "ROT13", "Caesar cipher decoder") {}

bool ROT13::execute(const std::string& target) {
    std::string result;
    
    std::transform(target.begin(), target.end(), std::back_inserter(result),
        [](char c) {
            if(!isalpha(c)) return c;
            char base = isupper(c) ? 'A' : 'a';
            return static_cast<char>((c - base + 13) % 26 + base);
        });
    
    std::cout << "Декодированный: " << result << "\n";
    return result.find("OmniCore") != std::string::npos;
}