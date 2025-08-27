/****************************************************************
// File Name: MovementComponent2D
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (MovementComponent Core), Jacob Wilburn (360 degree aiming, and death logic)
// Description: Base component for player characters. Contains logic for
// all player inputs, health, reviving, aiming/shooting, movement, etc.
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/InputComponent.h"
#include "Object/Components/AnimationComponent.h"
#include "Object/Components/RenderComponent2D.h"
#include "Object/Components/UIComponent.h"
#include "PlaySoundComponent.h"


enum FacingDirection
{
	Down,
	Up,
	Left,
	Right
};

enum Class
{
	Ranger,
	Tank,
	Healer
};

class MovementComponent2D : public Component {
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	void SetHealthReviveUIComponent(std::shared_ptr < UIComponent> _healthUIComponent) { reviveUIComponent = _healthUIComponent; }
	void SetClass(Class newClass) { currentClass = newClass; }
	void SetIsHurt(bool hurt);
	void SetIsHeal(bool heal);
	void SetIsDead(bool dead);

	void setInstantKill() { instantKillOn = !instantKillOn; }
	void setGodMode() { godMode = !godMode; }
	void SetReviveProgress(float progress);
	float GetReviveProgress() const;
	void RevivePlayer();
	void ActivateBarrier();
	void DeactivateBarrier();
	bool isDead;
	bool isHurt;
	std::shared_ptr<Renderable> GetRenderable() { return renderable; }
	bool GetIsInvincible() { return isInvincible; }

	void SpawnBullet(float offsetX, float offsetY, float velocityX, float velocityY, float deltaTime);
	void SpawnHeartBullet(float offsetX, float offsetY, float velocityX, float velocityY, float deltaTime);

private:
	float moveSpeed;
	float maxMoveSpeed;
	float jumpForce;

	bool isHealed;

	float hurtCooldownTime;
	float healCooldownTime;

	float collisionSoundCooldown;
	float lastCollisionTime;
	float footstepTimer;

	float coolDownTime;
	float reviveProgress;  
	float reviveSpeed;
	bool isReviving;

	bool triggerCooldown;
	bool controller;
	float angleRad;

	bool isChargingBullet = false;
	bool isChargingHeart = false;
	float chargeTimer = 0.0f;
	float maxChargeTime = 0.75f;
	float minChargeTime = 0.25f;
	float startingChargeSize = 0.1f;
	float bonusDamage = 1.5f;
	float barrierDuration = 3.0f;  
	float barrierTimer = 0.0f;
	bool isInvincible = false;

	bool instantKillOn = false;
	bool godMode = false;

	Vector3 liveScale;
	Vector3 deadScale;

	Vector3 spawnJitter;

	FacingDirection currentFacingDirection;
	Class currentClass;
	GameObject* pointer;
	GameObject* charge_indicator;
	GameObject* heart_indicator;
	GameObject* full_charge_indicator;
	GameObject* full_heart_indicator;
	GameObject* barrier;

	std::shared_ptr<InputComponent> playerInputComponent;
	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<RenderComponent2D> renderComponent;
	std::shared_ptr<PlaySoundComponent> playSoundComponent;
	std::shared_ptr<UIComponent> reviveUIComponent;
	std::shared_ptr<Renderable> renderable;

	uint32_t eventID;
};