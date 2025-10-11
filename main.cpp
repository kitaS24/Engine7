#include <iostream>
#include "Core.cpp"
int main() {
    //Engine();
    Engine Game;

    //Game.DebugMode(false);
    Game.DebugMode(true);
    Game.Setup();
    Game.SetSwapInterval(1);

    Game.CompileTrenchBroomMap("PipeMap.obj","PipeMap.map","saves/test1.gems","textures/textures.ini");

    while(Game.Frame()){}

    Game.Cleanup();
    return 0;
}
