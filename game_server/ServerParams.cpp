#include <inih/INIReader.h>
#include "ServerParams.h"

ServerParams::ServerParams() {
    INIReader config("ServerConfig.ini");

    if (config.ParseError() != 0) {
        throw std::exception("Cannot Load file ServerConfig.ini ");
    }

    port = config.GetInteger("GameServer", "port", 10032);
    tickrate = config.GetInteger("GameServer", "tickrate", 32);

    playerMoveSpeed = config.GetFloat("PhysicsParams", "PlayerMoveSpeed", 4.8f);
    playerDiagonalMoveSpeed = playerMoveSpeed / SQRT_2;
    playerInRotationMoveSpeed = config.GetFloat("PhysicsParams", "PlayerInRotationMoveSpeed", 1.6f);
    playerInRotationDiagonalMoveSpeed = playerInRotationMoveSpeed / SQRT_2;
    playerRotationSpeed = config.GetInteger("PhysicsParams", "PlayerRotationSpeed", 4) * PI;
    playerCatRadius = config.GetFloat("PhysicsParams", "PlayerCatRadius", 0.5f);
    zombieRabbitMoveSpeed = config.GetFloat("PhysicsParams", "ZombieRabbitMoveSpeed", 1.6f);
    zombieRabbitRadius = config.GetFloat("PhysicsParams", "ZombieRabbitRadius", 0.5f);
    highlightFOVAngle = PI / config.GetFloat("PhysicsParams", "HighlightFOVAngle", 3);
    playerKnockBackMaxDistance = config.GetFloat("PhysicsParams", "PlayerKnockBackMaxDistance", 5.0f);
    playerRespawnInvincibleTime = config.GetFloat("PhysicsParams", "PlayerRespawnInvincibleTime", 2.0f);

    // Zombie wave parameters
    waveDefaultNumZombies = config.GetInteger("ZombieWaves", "WaveDefaultNumZombies", 1);
    waveDeltaNumZombies = config.GetInteger("ZombieWaves", "WaveDeltaNumZombies", 2);
    zombieDefaultHealth = config.GetInteger("ZombieWaves", "ZombieDefaultHealth", 100);
    zombieDeltaHealth = config.GetInteger("ZombieWaves", "ZombieDeltaHealth", 20);
    waveStartTime = config.GetFloat("ZombieWaves", "WaveStartTime", 5.0f);

    // Plant Corn
    cornAttackPower = config.GetInteger("Corn", "AttackPower", 50);
    cornBoundingBoxRadius = config.GetFloat("Corn", "BoundingBoxRadius", 1.0f);
    cornAttackInterval = config.GetFloat("Corn", "AttackInterval", 1.0f);
    cornAttackRange = config.GetFloat("Corn", "AttackRange", 3.0f);
    cornGrowExpireTime = config.GetFloat("Corn", "GrowExpireTime", 2.0f);
    cornGrowCooldownTime = config.GetFloat("Corn", "GrowCooldownTime", 2.0f);

    // Plant Cactus
    cactusAttackPower = config.GetInteger("Cactus", "AttackPower", 50);
    cactusBoundingBoxRadius = config.GetFloat("Cactus", "BoundingBoxRadius", 1.0f);
    cactusAttackInterval = config.GetFloat("Cactus", "AttackInterval", 1.0f);
    cactusAttackRange = config.GetFloat("Cactus", "AttackRange", 10.0f);
    cactusGrowExpireTime = config.GetFloat("Cactus", "GrowExpireTime", 2.0f);
    cactusGrowCooldownTime = config.GetFloat("Cactus", "GrowCooldownTime", 2.0f);
    cactusBulletSpeed = config.GetFloat("Cactus", "BulletSpeed", 9.0f);
    cactusBulletRadius = config.GetFloat("Cactus", "BulletRadius", 0.5f);
}