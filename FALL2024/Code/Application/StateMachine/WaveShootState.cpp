/****************************************************************
// File Name: WaveShootState
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: An enemy state that handles shooting in a spiral /
// wave pattern
****************************************************************/

#include "precompiled.h"
#include "WaveShootState.h"
#include "AIEntity.h" 
#include "Components/EnemyComponent.h" 
#include "Managers/GlobalSoundManager.h"

void WaveShootState::Enter()
{
    GetEntity().currentStateName = "WaveShoot";

    GetEntity().ChangeAnimationState("Shoot");

    GlobalSoundManager::Instance().Play("mob10atk.mp3");

    shootTimer = 0.0f;
    wavesFired = 0;
    waveShootIndex = 0;
}

void WaveShootState::Update(float deltaTime)
{
    shootTimer += deltaTime;

    if (shootTimer >= shootInterval)
    {
        GlobalSoundManager::Instance().Play("15_Impact_flesh_02.mp3");

        WaveShoot(shootSpeed, waveShootIndex);

        shootTimer = 0.0f;
        waveShootIndex++;

        if (waveShootIndex % 12 == 0) // One full circular wave completed
        {
            wavesFired++;

            if (wavesFired >= maxWaves) {
                if (GetEntity().DoesStateExist("Idle")) {
                    GetEntity().ChangeState("Idle");
                }
				else if (GetEntity().DoesStateExist("BossIdle")) {
					GetEntity().ChangeState("BossIdle");
				}
            }
        }
    }
}

void WaveShootState::Exit()
{
}

void WaveShootState::Deserialize(const rapidjson::Value& json)
{
    try
    {
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for WaveShootState: Expected an object.");
        }

        if (json.HasMember("maxWaves") && json["maxWaves"].IsNumber()) {
            maxWaves = json["maxWaves"].GetInt();
        }
        if (json.HasMember("shootSpeed") && json["shootSpeed"].IsNumber()) {
            shootSpeed = json["shootSpeed"].GetFloat();
        }
        if (json.HasMember("shootInterval") && json["shootInterval"].IsNumber()) {
            shootInterval = json["shootInterval"].GetFloat();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing WanderState: " << e.what() << std::endl;
        throw;
    }
}
