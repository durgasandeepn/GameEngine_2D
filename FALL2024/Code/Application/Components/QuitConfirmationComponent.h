/****************************************************************
// File Name: QuitConfirmationComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankaseemporn
// Description: Component to handle the quit confirmation screen
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
class QuitConfirmationComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);


	void No();
	void Yes();

private:
	uint32_t eventID;
};
