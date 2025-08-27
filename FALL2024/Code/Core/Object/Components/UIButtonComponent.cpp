/****************************************************************
// File Name: UIButtonComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Alex Humphries
// Description: Component relating to a button on the UI
// Extends from UIElementComponent
****************************************************************/

#include "precompiled.h"
#include "UIButtonComponent.h"
#include "Event/Events/UIButtonPressedEvent.h"
#include "Object/GameObject.h"
#include "Managers/GlobalSoundManager.h"

void UIButtonComponent::Update(float deltaTime)
{
	UIElementComponent::Update(deltaTime);
	timeSinceLastInput += deltaTime;
}

void UIButtonComponent::HandleInput(float deltaTime)
{
	if (timeSinceLastInput >= inputDelay &&
		(Input::Instance().IsKeyPressed(KeyCode::Enter) ||
		Input::Instance().IsKeyPressed(KeyCode::Space) ||
		Input::Instance().IsGamepadButtonPressed(GamepadButton::Button_A, 0) ||
		Input::Instance().IsMouseButtonPressed(MouseButton::Left)
		)
		) {
		Activate();
		timeSinceLastInput = 0.0f;
	}
}
void UIButtonComponent::SetIsHovered(bool newIsHovered)
{
	isHovered = newIsHovered;
	if (isHovered && animationComponent->GetCurrentState() != "Hovered") {
		animationComponent->ChangeAnimationState("Hovered");
	}
	else if (!isHovered && animationComponent->GetCurrentState() != "Normal") {
		animationComponent->ChangeAnimationState("Normal");
	}
}

void UIButtonComponent::Activate()
{
	std::cout << owner->GetName() << " has activated." << std::endl;
	UIButtonPressedEvent event(uiTag);
	EventManager::Instance().BroadcastEvent(event);

	// Todo: Fix
	GlobalSoundManager::Instance().Play("switch_001.mp3");
}
