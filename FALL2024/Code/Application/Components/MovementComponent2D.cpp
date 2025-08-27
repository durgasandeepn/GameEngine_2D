/****************************************************************
// File Name: MovementComponent2D
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn (MovementComponent Core), Jacob Wilburn (360 degree aiming, and death logic)
// Description: Base component for player characters. Contains logic for
// all player inputs, health, reviving, aiming/shooting, movement, etc.
****************************************************************/

#include "precompiled.h"
#include "MovementComponent2D.h"
#include "Math/Vector3.h"
#include "Object/Components/PhysicsComponent.h"
#include "Object/Components/RenderComponent2D.h"
#include "Components/HealthComponent.h"
#include "Components/BulletComponent.h"
#include "Components/EnemyComponent.h"
#include "Object/GameObject.h"
#include "Event/Events/CollisionEvent.h"
#include "Managers/GlobalSoundManager.h"
#include "Managers/GameManager.h"

void MovementComponent2D::Initialize()
{
	moveSpeed = 75.0f;
	maxMoveSpeed = 15.0f;
	jumpForce = 8.0f;
	isHurt = false;
	isDead = false;
	isHealed = false;
	hurtCooldownTime = 0.0f;
	healCooldownTime = 1.0f;
	collisionSoundCooldown = 0.5f;
	lastCollisionTime = 0.0f;
	footstepTimer = 0.0f;
	liveScale = owner->GetLocalScale();
	deadScale = liveScale * 0.5f;
	pointer = GameObject::Instantiate("PlayerCharacter/pointer.json");
	charge_indicator = GameObject::Instantiate("PlayerCharacter/charge_indicator.json");
	if (charge_indicator) {
		charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
	}
	heart_indicator = GameObject::Instantiate("PlayerCharacter/heart_indicator.json");
	if (heart_indicator) {
		heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
	}
	barrier = GameObject::Instantiate("PlayerCharacter/barrier.json");
	barrier->SetIsActive(false);

	full_charge_indicator = GameObject::Instantiate("PlayerCharacter/full_charge_indicator.json");
	if (full_charge_indicator) {
		full_charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
	}

	full_heart_indicator = GameObject::Instantiate("PlayerCharacter/full_heart_indicator.json");
	if (full_heart_indicator) {
		full_heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
	}
	triggerCooldown = false;

	playerInputComponent = owner->FindComponent<InputComponent>();
	if (playerInputComponent == nullptr)
	{
		std::cerr << "Failed to find InputComponent " << std::endl;
	}

	playSoundComponent = owner->FindComponent<PlaySoundComponent>();
	if (playSoundComponent == nullptr)
	{
		std::cerr << "Failed to find playSoundComponent " << std::endl;
	}

	animationComponent = owner->FindComponentInChild<AnimationComponent>();
	if (animationComponent == nullptr)
	{
		std::cerr << "Failed to find AnimationComponent " << std::endl;
	}

	renderComponent = owner->FindComponentInChild<RenderComponent2D>();
	if (!renderComponent) {
		std::cerr << "Failed to find renderComponent " << std::endl;
	}

	eventID = EventManager::Instance().AddListener<CollisionEvent>(
		[this](const CollisionEvent& event) {
			if (event.object1->CompareTag("player") && event.object2->CompareTag("enemy"))
			{
				if (event.object1 == owner) {
					auto healthComponent = event.object1->FindComponent<HealthComponent>();
					if (healthComponent != nullptr)
					{
						auto movementComponent = event.object1->FindComponent<MovementComponent2D>();

						if (movementComponent->GetIsInvincible()) {
							return;
						}

						healthComponent->TakeDamage(1.0f);

						if (!movementComponent->isDead && !movementComponent->isHurt)
						{
							GlobalSoundManager::Instance().Play("URGH.mp3");
						}


						if (movementComponent != nullptr)
						{
							movementComponent->SetIsHurt(true);
						}


						if (healthComponent->GetHealth() <= 0)
						{
							if (movementComponent)
							{
								movementComponent->SetIsDead(true);
							}
						}
					}
				}
			}

			double currentTime = Time::Instance().GetTimeInSeconds();
			if (currentTime - lastCollisionTime < collisionSoundCooldown) {
				return;
			}

			lastCollisionTime = float(currentTime);
		}
	);
}

void MovementComponent2D::Update(float deltaTime)
{
	if (playerInputComponent == nullptr)
	{
		return;
	}

	if (renderComponent == nullptr) 
	{
		renderComponent = owner->FindComponentInChild<RenderComponent2D>();
	}

	if (reviveUIComponent != nullptr)
	{
		float ratio = reviveProgress / 1.0f;
		Vector3 newScale = reviveUIComponent->GetOwner()->GetLocalScale();
		newScale.x = ratio * (1.0f / 1.0f * 4.0f);

		reviveUIComponent->GetOwner()->SetLocalScale(newScale);

		Vector3 currentPos = owner->GetLocalPosition();
		currentPos.y += 1.0f;
		reviveUIComponent->GetOwner()->SetLocalPosition(currentPos);
	}

	if (barrier != nullptr) 
	{
		barrier->SetLocalPosition(Vector3(owner->GetLocalPosition().x, owner->GetLocalPosition().y, owner->GetLocalPosition().z));
	}

	if (isInvincible) {
		barrierTimer += deltaTime;

		if (barrierTimer >= barrierDuration && !godMode) {
			DeactivateBarrier();
		}
	}

	coolDownTime += deltaTime;

	if (isHurt) {
		hurtCooldownTime += deltaTime;
		if (hurtCooldownTime >= 1.0f) { 
			if (renderComponent != nullptr)
			{
				renderComponent->GetRenderable()->opacity = 1.0f;
			}
			isHurt = false; 
			hurtCooldownTime = 0.0f; 
		}
	}

	if (isHealed) 
	{
		healCooldownTime += deltaTime;
		if (healCooldownTime >= 1.0f) {
			if (renderComponent != nullptr)
			{
				renderComponent->GetRenderable()->special_color = Vector3(0.0f,0.0f,0.0f);
			}
			isHealed = false;
			healCooldownTime = 0.0f;
		}
	}

	if (isDead) 
	{
		if (animationComponent && animationComponent->GetCurrentState() != "Dead") {
			animationComponent->ChangeAnimationState("Dead");
		}
		owner->SetLocalScale(deadScale);
		moveSpeed = 10.0f;
		pointer->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
	}

	Vector3 inputVelocity(0.0f, 0.0f, 0.0f);
	std::string animToPlay = "Idle";
	bool isMoving = false;

	switch (currentFacingDirection)
	{
	case Down:
		animToPlay = "Idle";
		spawnJitter = Vector3(0.0, -1.0, 0.0);
		break;
	case Up:
		animToPlay = "IdleUp";
		spawnJitter = Vector3(0.0, 1.0, 0.0);
		break;
	case Left:
		animToPlay = "IdleLeft";
		spawnJitter = Vector3(-1.0, 0.0, 0.0);
		break;
	case Right:
		animToPlay = "IdleRight";
		spawnJitter = Vector3(1.0, 0.0, 0.0);
		break;
	default:
		break;
	}


	/*Movement input polling*/
	// Keyboard
	if (playerInputComponent->IsActionHeld("Right")) {
		inputVelocity.x = 1.0f;
		animToPlay = "MoveRight";
		isMoving = true;
		currentFacingDirection = FacingDirection::Right;
	}
	else if (playerInputComponent->IsActionHeld("Left")) {
		inputVelocity.x = -1.0f;
		animToPlay = "MoveLeft";
		isMoving = true;
		currentFacingDirection = FacingDirection::Left;
	}

	if (playerInputComponent->IsActionHeld("Up")) {
		inputVelocity.y = 1.0f;
		animToPlay = "Up";
		isMoving = true;
		currentFacingDirection = FacingDirection::Up;

	}
	else if (playerInputComponent->IsActionHeld("Down")) {
		inputVelocity.y = -1.0f;
		animToPlay = "Down";
		isMoving = true;
		currentFacingDirection = FacingDirection::Down;
	}
	
	

	//Controller
	if (playerInputComponent->GetAxisValue("LeftRightAxis") > 0.5f) {
		inputVelocity.x = 1.0f;
		animToPlay = "MoveRight";
		isMoving = true;
		currentFacingDirection = FacingDirection::Right;
	}
	else if (playerInputComponent->GetAxisValue("LeftRightAxis") < -0.5f) {
		inputVelocity.x = -1.0f;
		animToPlay = "MoveLeft";
		isMoving = true;
		currentFacingDirection = FacingDirection::Left;
	}

	if (playerInputComponent->GetAxisValue("UpDownAxis") < -0.5f ) {
		inputVelocity.y = 1.0f;
		animToPlay = "Up";
		isMoving = true;
		currentFacingDirection = FacingDirection::Up;
	}
	else if (playerInputComponent->GetAxisValue("UpDownAxis") > 0.5f) {
		inputVelocity.y = -1.0f;
		animToPlay = "Down";
		isMoving = true;
		currentFacingDirection = FacingDirection::Down;
	}

	if (!isDead) {
		double aimX = 0.0f;
		double aimY = 0.0f;

		if (!controller) {
			double mouseX;
			double mouseY;
	
			Input::Instance().GetMousePosition(mouseX, mouseY);
			Matrix4 temp = renderComponent->GetRenderable()->GetCamera()->GetProjectionMatrix();

			float left = -(temp.GetElement(3, 0) + 1) / temp.GetElement(0, 0);
			float right = (1 - temp.GetElement(3, 0)) / temp.GetElement(0, 0);
			float bottom = -(temp.GetElement(3, 1) + 1) / temp.GetElement(1, 1);
			float top = (1 - temp.GetElement(3, 1)) / temp.GetElement(1, 1);

			aimX = left + (mouseX + 1) * (right - left) / 2 - owner->GetLocalPosition().x;
			aimY = bottom + (mouseY + 1) * (top - bottom) / 2 + owner->GetLocalPosition().y;
			angleRad = atan2(-aimY, aimX);
		}

		else {
			aimX = playerInputComponent->GetAxisValue("R_LeftRightAxis");
			aimY = playerInputComponent->GetAxisValue("R_UpDownAxis");

				if (abs(aimX) < 0.5f && abs(aimY) < 0.5f) {
				aimX = playerInputComponent->GetAxisValue("LeftRightAxis");
				aimY = playerInputComponent->GetAxisValue("UpDownAxis");
			}
			float magnitude = sqrt(aimX * aimX + aimY * aimY);
			if (magnitude > 0.5f) {
				angleRad = atan2(-aimY, aimX);
			}
		}

		float velocityX = cos(angleRad) * 500.0f;
		float velocityY = sin(angleRad) * 500.0f;
		float offsetX = cos(angleRad) * 1.5f;
		float offsetY = sin(angleRad) * 1.5f;
		pointer->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));

		if (charge_indicator) 
		{
			charge_indicator->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
		}

		if (heart_indicator) 
		{
			heart_indicator->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
		}

		if (full_charge_indicator) 
		{
			full_charge_indicator->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
		}

		if (full_heart_indicator)
		{
			full_heart_indicator->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
		}

		if (playerInputComponent->IsActionPressed("Special"))
		{

			coolDownTime = 0.0f;
		}


		if (!isChargingHeart) 
		{
			 if (playerInputComponent->IsActionHeld("Shoot") || playerInputComponent->GetAxisValue("RightTrigger") > 0.5f) {
				 if (!isChargingBullet)
				 {
					 GlobalSoundManager::Instance().Play("16_Atk_buff_04.mp3");
				 }
				isChargingBullet = true;
				charge_indicator->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
				chargeTimer += deltaTime;
				charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = chargeTimer;
				charge_indicator->SetLocalScale(Vector3(chargeTimer, chargeTimer, 1.0f));
				if (chargeTimer >= maxChargeTime) {
					if (full_charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity != 0.75f)
					{
						GlobalSoundManager::Instance().Play("45_Charge_05.mp3");
					}
					full_charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.75f;
					charge_indicator->SetLocalRotation(Vector3(charge_indicator->GetLocalRotation().x, charge_indicator->GetLocalRotation().y, charge_indicator->GetLocalRotation().z + deltaTime));
					chargeTimer = maxChargeTime;
				}
			}
			 else if (playerInputComponent->IsActionReleased("Shoot") || playerInputComponent->GetAxisValue("RightTrigger") < 0.5f)
			{
				 if (isChargingBullet)
				 {
					 isChargingBullet = false;

					 if (chargeTimer >= minChargeTime) {
						 SpawnBullet(offsetX, offsetY, velocityX, velocityY, deltaTime);
					 }

					 charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
					 full_charge_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
					 charge_indicator->SetLocalScale(Vector3(startingChargeSize, startingChargeSize, 1.0f));
					 chargeTimer = startingChargeSize;
				 }

			}
		}

		if (!isChargingBullet) 
		{
			if (playerInputComponent->IsActionHeld("Special") || playerInputComponent->GetAxisValue("LeftTrigger") > 0.5f) {
				if (!isChargingHeart)
				{
					GlobalSoundManager::Instance().Play("21_Debuff_01.mp3");
				}
				
				isChargingHeart = true;
				heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 1.0f;
				chargeTimer += deltaTime;
				heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = chargeTimer;
				heart_indicator->SetLocalScale(Vector3(chargeTimer, chargeTimer, 1.0f));
				if (chargeTimer >= maxChargeTime) {
					if (full_heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity != 0.75f)
					{
						GlobalSoundManager::Instance().Play("30_Revive_03.mp3");
					}
					chargeTimer = maxChargeTime;
					full_heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.75f;
				}
			}
			else if (playerInputComponent->IsActionReleased("Special") || playerInputComponent->GetAxisValue("LeftTrigger") < 0.5f)
			{
				if (isChargingHeart) 
				{
					isChargingHeart = false;

					if (chargeTimer >= minChargeTime) {
						SpawnHeartBullet(offsetX, offsetY, velocityX, velocityY, deltaTime);
					}

					full_heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
					heart_indicator->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 0.0f;
					heart_indicator->SetLocalScale(Vector3(startingChargeSize, startingChargeSize, 1.0f));
					chargeTimer = startingChargeSize;
				}
			}
		}

	}

	inputVelocity = inputVelocity.Normalized() * moveSpeed * deltaTime;


	/* Animation changing*/
	if (animationComponent && animationComponent->GetCurrentState() != animToPlay && animationComponent->GetCurrentState() != "Dead") {
		animationComponent->ChangeAnimationState(animToPlay);
	}

	/* Footstep sounds */
	if (isMoving) {
		footstepTimer += deltaTime;
		if (footstepTimer >= 0.3f) {
			if (!isDead) {
				GlobalSoundManager::Instance().Play("footstep_snow_004.mp3");
			}
			footstepTimer = 0.0f;

		}
	}

	/* Actual moving */
	auto physics = owner->FindComponent<PhysicsComponent>();
	if (physics) {
		auto body = physics->GetBody();
		if (body) {
			body->SetVelocity(body->GetVelocity() + inputVelocity);
		}
	}
	else {
		owner->SetLocalPosition(owner->GetLocalPosition() + inputVelocity);
	}
}

void MovementComponent2D::Shutdown()
{
	EventManager::Instance().RemoveListener<CollisionEvent>(eventID);
	RenderManager::Instance().RemoveRenderable(renderable.get());
}

void MovementComponent2D::Serialize()
{
}

void MovementComponent2D::Deserialize(const rapidjson::Value& json)
{
	try {
		// Validate the JSON structure
		if (!json.IsObject()) {
			throw std::invalid_argument("Invalid JSON for MovementComponent2D: Expected an object.");
		}

		// actions array
		if (json.HasMember("moveSpeed") && json["moveSpeed"].IsFloat()) {
			moveSpeed = json["moveSpeed"].GetFloat();
		}

		if (json.HasMember("controller") && json["controller"].IsBool()) {
			controller = json["controller"].GetBool();
		}

		else {
			throw std::invalid_argument("MovementComponent2D::Deserialize - Missing or invalid 'actions'");
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error deserializing MovementComponent2D: " << e.what() << std::endl;
		throw; // Re-throw the exception after logging
	}
}

void MovementComponent2D::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void MovementComponent2D::DeactivateBarrier()
{
	if (barrier) {
		barrier->SetIsActive(false);
		isInvincible = false;
	}
}

void MovementComponent2D::SetIsHurt(bool hurt)
{
	if (!isHurt) {
		if (renderComponent != nullptr) 
		{
			renderComponent->GetRenderable()->opacity = 0.5f;
		}

		isHurt = hurt;
		hurtCooldownTime = 0.0f;

		ActivateBarrier();
	}
}

void MovementComponent2D::ActivateBarrier()
{
	if (barrier) {
		barrier->SetIsActive(true);
		isInvincible = true;
		barrierTimer = 0.0f;
	}
}

void MovementComponent2D::SetIsHeal(bool heal)
{
	if (!isHealed) {
		if (renderComponent != nullptr)
		{
			renderComponent->GetRenderable()->special_color = Vector3(1.0,0.0,0.0);
		}

		isHealed = heal;
		hurtCooldownTime = 0.0f;
	}
}

void MovementComponent2D::SetIsDead(bool dead)
{
	isDead = dead;
}

void MovementComponent2D::SetReviveProgress(float progress)
{
	if (!isDead)
		return;

	reviveProgress += progress;

	if (reviveProgress >= 1.0f)
	{
		RevivePlayer();
	}
}

float MovementComponent2D::GetReviveProgress() const
{
	return reviveProgress;
}

void MovementComponent2D::RevivePlayer()
{
	GlobalSoundManager::Instance().Play("Iamalive.mp3");

	isDead = false;
	isReviving = false;
	reviveProgress = 0.0f;
	moveSpeed = 75.0f;
	owner->SetLocalScale(liveScale);
	pointer->FindComponent<RenderComponent2D>()->GetRenderable()->opacity = 1.0f;

	if (animationComponent)
	{
		animationComponent->ChangeAnimationState("Idle"); 
	}

	if (renderComponent)
	{
		renderComponent->GetRenderable()->opacity = 1.0f;
	}

	auto healthComponent = owner->FindComponent<HealthComponent>();
	if (healthComponent)
	{
		healthComponent->ResetHealth(); 
	}

	GameManager::Instance().AddPlayerAfterRevived(owner);
}

void MovementComponent2D::SpawnBullet(float offsetX, float offsetY, float velocityX, float velocityY, float deltaTime)
{
	float powerRatio;

	if (chargeTimer >= maxChargeTime) {
		powerRatio = chargeTimer * bonusDamage;
		GlobalSoundManager::Instance().Play("13_Ice_explosion_01.mp3");
	}
	else
	{
		powerRatio = std::min(chargeTimer / maxChargeTime, 1.0f);
		GlobalSoundManager::Instance().Play("Magic Spell_Simple Swoosh_6.mp3");
	}
	
	auto* bullet = GameObject::Instantiate("BossBattle/ranger_bullet.json");
	bullet->FindComponent<BulletComponent>()->SetSpawner(owner);
	if (instantKillOn) {
		bullet->FindComponent<BulletComponent>()->SetPlayerBulletDamage(1000.0f);
	} if (!instantKillOn) {
		bullet->FindComponent<BulletComponent>()->SetPlayerBulletDamage(powerRatio);
	}
	bullet->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
	bullet->SetLocalScale(Vector3(chargeTimer, chargeTimer, 1.0f));
	bullet->Update(deltaTime);
	bullet->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(Vector3(velocityX, velocityY, 0.0f));
}

void MovementComponent2D::SpawnHeartBullet(float offsetX, float offsetY, float velocityX, float velocityY, float deltaTime)
{
	float powerRatio = std::min(chargeTimer / maxChargeTime, 1.0f);

	GlobalSoundManager::Instance().Play("029_Decline_09.mp3");
	auto* bullet = GameObject::Instantiate("BossBattle/healer_bullet.json");
	bullet->FindComponent<BulletComponent>()->SetSpawner(owner);
	bullet->FindComponent<BulletComponent>()->SetPlayerBulletDamage(powerRatio);
	bullet->SetLocalPosition(Vector3(owner->GetLocalPosition().x + offsetX, owner->GetLocalPosition().y + offsetY, owner->GetLocalPosition().z));
	bullet->SetLocalScale(Vector3(chargeTimer, chargeTimer, 1.0f));
	bullet->Update(deltaTime);
	bullet->FindComponent<PhysicsComponent>()->GetBody()->SetVelocity(Vector3(velocityX, velocityY, 0.0f));

}
