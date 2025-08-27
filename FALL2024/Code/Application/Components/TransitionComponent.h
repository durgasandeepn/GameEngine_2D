/****************************************************************
// File Name: TransitionComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component to handle the transitioning between scenes with fade in and fade out effects
****************************************************************/

#pragma once
#include "Object/Components/Component.h"
#include "Object/Components/UIComponent.h"

enum class FadingPhase
{
	FadeIn,
	FadeOut
};

class TransitionComponent : public Component
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json);
	void Configure(const std::unordered_map<std::string, std::any>& properties);

	void StartFading(FadingPhase fadingPhase);
	void UpdateTransition(float deltaTime, FadingPhase fadingPhase);
	bool GetIsTransition() { return isTransition; }

private:
	std::shared_ptr<UIComponent> uiComponent;
	const float fadingSpeed = 1.0f;
	bool isTransition;
	bool isFadeOut;
	FadingPhase currentFadingPhase;
};

