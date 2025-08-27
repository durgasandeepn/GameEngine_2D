/****************************************************************
// File Name: AnimationComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - deserializing
// Description: Component dedicated to handling "animations" for game objects.
// An animation can be a "flipbook" animation, which is a simple 2D animation
// where the texture gets changed depending on the frame of a sprite sheet
// or an affine animation. Both work with this system.
****************************************************************/
#pragma once
#include "Component.h"
#include "Animation/AnimationController.h"

class AnimationComponent : public Component {
public:
	AnimationComponent();

	void Initialize() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
	void Serialize() override;
	void Deserialize(const rapidjson::Value& json) override;
	void Configure(const std::unordered_map<std::string, std::any>& properties) override;

	void ChangeAnimationState(std::string animationState);
	std::string GetCurrentState();

private:
	AnimationController* animationController{nullptr};

	AffineTransformation GetAffineTransformationFromJSON(const rapidjson::Value& transformationJSON);
};