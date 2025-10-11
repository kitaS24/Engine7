//
// Created by kitaS24 on 11.10.2025.
//


void CreateEntsOnStartup(){
    // creates entities on engine startup

    LevelEnt.push_back(std::make_unique<Ent>());
    LevelEnt.push_back(std::make_unique<Ent>());
    LevelEnt.push_back(std::make_unique<Ent>());
    LevelEnt.push_back(std::make_unique<WorldRender>());
    LevelEnt.push_back(std::make_unique<Particle>());
    LevelEnt.push_back(std::make_unique<LightFlood>());
    LevelEnt.push_back(std::make_unique<Player>());


}