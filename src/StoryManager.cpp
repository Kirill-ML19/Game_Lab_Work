#include "StoryManager.h"
#include <iostream>
#include <thread>

void StoryManager::showPrologue() {
    std::cout << R"(
    ░██████╗░██╗░░██╗░█████╗░██████╗░██╗░░██╗  ░█████╗░░█████╗░██████╗░███████╗
    ██╔════╝░██║░░██║██╔══██╗██╔══██╗██║░██╔╝  ██╔══██╗██╔══██╗██╔══██╗██╔════╝
    ██║░░██╗░███████║███████║██████╔╝█████═╝░  ██║░░╚═╝██║░░██║██████╔╝█████╗░░
    ██║░░╚██╗██╔══██║██╔══██║██╔══██╗██╔═██╗░  ██║░░██╗██║░░██║██╔══██╗██╔══╝░░
    ╚██████╔╝██║░░██║██║░░██║██║░░██║██║░╚██╗  ╚█████╔╝╚█████╔╝██║░░██║███████╗
    ░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝  ░╚════╝░░╚════╝░╚═╝░░╚═╝╚══════╝
    )" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\n[Система] Год 2049. Миром правят корпорации.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "[Система] OmniCore Corporation контролирует 83% населения...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void StoryManager::showMissionIntro(size_t missionId) {
    if(missionId >= missionIntros.size()) return;
    
    std::cout << "\n════════════════════════════════════\n";
    std::cout << missionIntros[missionId] << std::endl;
    std::cout << "════════════════════════════════════\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void StoryManager::showChapter() {
    std::cout << "\n[СЮЖЕТ] " << missionIntros[currentChapter] << "\n";
}

void StoryManager::nextChapter() {
    if(currentChapter < missionIntros.size()-1) currentChapter++;
}

void StoryManager::showIntro() {
    std::cout << "Добро пожаловать в игру!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Начинаем приключение...\n";
}

size_t StoryManager::getCurrentChapter() const {
    return currentChapter;
}
