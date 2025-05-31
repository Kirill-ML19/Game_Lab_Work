#include <iostream>
#include "Game.h"

int main() {
    std::cout << "Welcome to the game!\n";

    Game game;  
    game.run();   

    std::cout << "Thanks for playing!\n";
    return 0;
}
