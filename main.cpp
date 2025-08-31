#include <iostream>
#include "Core.cpp"
int main() {
    //std::cout << "Hello, World!" << std::endl;
    //Engine();
    Engine Game;
    Game.Setup();
    while(Game.Frame()){}
    Game.Cleanup();
    return 0;
}
