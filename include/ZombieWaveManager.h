#ifndef _ZOMBIE_WAVE_MANAGER_H
#define _ZOMBIE_WAVE_MANAGER_H

#include "Zombie.hpp"
#include "Floor.hpp"

class GameState;

class ZombieWaveManager {
public:
    ZombieWaveManager();
    ZombieWaveManager(GameState* state);

    void spawn();

    void handleZombieWaves();

    GameState* gameState;

    int zombiesInWave;  // number of zombies in current wave
    int zombiesSpawned; // number of zombies spawned in current wave
    int zombieHealth;
    int waveNum;

    float currTime; // How long until wave
    bool inWave;
};

#endif