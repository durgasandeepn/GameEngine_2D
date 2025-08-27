/****************************************************************
// File Name: CreditsMenuComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component to handle the credits menu screen, with the ability to speed it up
****************************************************************/

#include "precompiled.h"
#include "CreditsMenuComponent.h"
#include "SceneManagement/SceneManager.h"

void CreditsMenuComponent::Initialize()
{
}

void CreditsMenuComponent::Update(float deltaTime)
{
	if (!hasInitialized) {
		auto* creditsTitleNode = owner->FindChildNodeFast("CreditsTitle");
		if (creditsTitleNode) {
			creditsTitle = dynamic_cast<GameObject*>(creditsTitleNode);
		}

		auto* knightlyBuildNode = owner->FindChildNodeFast("KnightlyBuildLogo");
		if (knightlyBuildNode) {
			knightlyBuild = dynamic_cast<GameObject*>(knightlyBuildNode);
		}

		auto* creditsTextNode = owner->FindChildNodeFast("CreditsText");
		if (creditsTextNode) {
			creditsText = dynamic_cast<GameObject*>(creditsTextNode);
		}

		auto* digipenLogoNode = owner->FindChildNodeFast("DigiPenLogo");
		if (digipenLogoNode) {
			digipenLogo = dynamic_cast<GameObject*>(digipenLogoNode);
		}

		auto* thanksForPlayingNode = owner->FindChildNodeFast("ThanksForPlaying");
		if (thanksForPlayingNode) {
			thanksForPlaying = dynamic_cast<GameObject*>(thanksForPlayingNode);
		}
		hasInitialized = true;
	}
	if (creditsTitle) {
		Vector3 pos = creditsTitle->GetLocalPosition();
		pos.y += scrollSpeed * deltaTime;
		creditsTitle->SetLocalPosition(pos);
	}

	if (knightlyBuild) {
		Vector3 pos = knightlyBuild->GetLocalPosition();
		pos.y += scrollSpeed * deltaTime;
		knightlyBuild->SetLocalPosition(pos);
	}

	if (creditsText) {
		Vector3 pos = creditsText->GetLocalPosition();
		pos.y += scrollSpeed * deltaTime;
		creditsText->SetLocalPosition(pos);
	}

	if (digipenLogo) {
		Vector3 pos = digipenLogo->GetLocalPosition();
		pos.y += scrollSpeed * deltaTime;
		digipenLogo->SetLocalPosition(pos);
	}

	if (thanksForPlaying) {
		Vector3 pos = thanksForPlaying->GetLocalPosition();
		pos.y += scrollSpeed * deltaTime;
		thanksForPlaying->SetLocalPosition(pos);
	}

	if (thanksForPlaying->GetLocalPosition().y > 15) {
		SceneManager::Instance().PopScene();
	}

	if (Input::Instance().IsKeyPressed(KeyCode::Space) ||
		Input::Instance().IsKeyPressed(KeyCode::Enter) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 0) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 1) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 2) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 3)) {
		scrollSpeed = 4.0;
	}
	if (Input::Instance().IsKeyReleased(KeyCode::Space) ||
		Input::Instance().IsKeyReleased(KeyCode::Enter) ||
		Input::Instance().IsGamepadButtonReleased(GamepadButton::Button_A, 0) ||
		Input::Instance().IsGamepadButtonReleased(GamepadButton::Button_A, 1) ||
		Input::Instance().IsGamepadButtonReleased(GamepadButton::Button_A, 2) ||
		Input::Instance().IsGamepadButtonReleased(GamepadButton::Button_A, 3)) {
		scrollSpeed = 1.0f;
	}

	if (Input::Instance().IsKeyPressed(KeyCode::Escape) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 0) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 1) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 2) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_B, 3))
	{
		SceneManager::Instance().PopScene();
	}
}

void CreditsMenuComponent::Shutdown()
{
}

void CreditsMenuComponent::Serialize()
{
}

void CreditsMenuComponent::Deserialize(const rapidjson::Value& json)
{
}

void CreditsMenuComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}
