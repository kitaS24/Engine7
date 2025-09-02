#include <iostream>
#include "Core.cpp"
int main() {
    //Engine();
    Engine Game;

    Game.Setup();
    Game.SetSwapInterval(1);

    while(Game.Frame()){}

    Game.Cleanup();
    return 0;
}
