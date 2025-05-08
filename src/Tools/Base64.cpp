#include "Tools/Base64.h"
#include <stdexcept>
#include <iostream>

Base64::Base64() : 
    Tool(ToolType::Base64, "Base64", "Encoding/decoding tool") {}

bool Base64::execute(const std::string& target) {
    try {
        std::string decoded = base64_decode(target);
        std::cout << "Decoded message: " << decoded << "\n";
        return true;
    } catch(...) {
        std::cout << "Decoding failed!\n";
        return false;
    }
}

std::string Base64::base64_decode(const std::string& in) {
    const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        
    std::string out;
    int val = 0, valb = -8;
    
    for(unsigned char c : in) {
        if(c == '=') break;
        size_t pos = base64_chars.find(c);
        if(pos == std::string::npos) throw std::runtime_error("Invalid base64");
        
        val = (val << 6) + (int)pos;
        valb += 6;
        
        if(valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}