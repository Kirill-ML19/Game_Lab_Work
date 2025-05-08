#include "Tools/BruteForce.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <iostream>

BruteForce::BruteForce() : 
    Tool(ToolType::BruteForce, "Brute Force", "Password cracking using dictionary attacks") {}

bool BruteForce::execute(const std::string& target) {
    std::cout << "\n[BRUTE FORCE] Starting attack on " << target << "...\n";
    
    for(int i = 0; i < 5; ++i) {
        std::cout << "█" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    
    std::ifstream dict("data/passwords.txt");
    if(!dict) {
        std::cout << "\n[ERROR] Dictionary file not found!\n";
        return false;
    }
    
    std::string password;
    while(std::getline(dict, password)) {
        if(password == "0mn1C0r3_P@ss") {
            std::cout << "\n[SUCCESS] Password found: " << password << "\n";
            return true;
        }
    }
    
    std::cout << "\n[FAILURE] Password not found in dictionary\n";
    return false;
}