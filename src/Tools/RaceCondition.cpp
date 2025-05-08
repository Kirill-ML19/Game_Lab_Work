#include "Tools/RaceCondition.h"
#include <iostream>
#include <atomic>    
#include <thread>    

RaceCondition::RaceCondition() : 
    Tool(ToolType::RaceCondition, "Race Exploit", "Timing attack tool") {}

bool RaceCondition::execute(const std::string& target) {
    std::cout << "\nTarget: " << target << std::endl; 
    std::atomic<bool> success{false};
    std::atomic<bool> running{true};
    
    std::cout << "Атака состояния гонки началась!\n";
    std::cout << "Быстро нажмите Enter, чтобы воспользоваться...\n";
    
    std::thread server([&]{
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if(running) {
            std::cout << "Сервер заблокирован!\n";
            success = false;
        }
    });

    std::cin.ignore();
    running = false;
    server.join();
    
    success = true;
    return success;
}