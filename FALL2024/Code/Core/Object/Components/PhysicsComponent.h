/****************************************************************
// File Name: PhysicsComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Component dedicated to handling physics. Currently, this simply
// holds reference to a PhysicsBody that gets updated by the PhysicsManager.
// TODO determine if a better solution exists
****************************************************************/

#pragma once
#include "Component.h"
#include "Physics/PhysicsBody.h"


class PhysicsComponent : public Component {
public:
	PhysicsComponent();
	~PhysicsComponent() = default;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json) override;
	void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	std::shared_ptr<PhysicsBody> GetBody() { return body; }

private:
	CollisionLayer StringToCollisionLayer(const std::string& collisionString);
	std::shared_ptr<PhysicsBody> body;
};