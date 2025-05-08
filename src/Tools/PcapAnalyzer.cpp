#include "Tools/PcapAnalyzer.h"
#include <fstream>
#include <sstream>
#include <iostream>

PcapAnalyzer::PcapAnalyzer() : 
    Tool(ToolType::PcapAnalyzer, "PCAP Analyzer", "Network traffic analyzer") {}

bool PcapAnalyzer::execute(const std::string& filename) {
    std::ifstream file("data/" + filename);
    if(!file) return false;

    std::cout << "\nAnalyzing network traffic...\n";
    std::string line;
    while(std::getline(file, line)) {
        if(line.find("OmniCore") != std::string::npos) {
            std::cout << "Found suspicious packet: " << line << "\n";
            return true;
        }
    }
    return false;
}