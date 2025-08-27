/****************************************************************
// File Name: TransitionComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Component to handle the transitioning between scenes with fade in and fade out effects
****************************************************************/

#include "precompiled.h"
#include "TransitionComponent.h"
#include "Object/GameObject.h"

void TransitionComponent::Initialize()
{
	if (uiComponent == nullptr)
	{
		uiComponent = owner->FindComponent<UIComponent>();
		return;
	}
}

void TransitionComponent::Update(float deltaTime)
{
	if (uiComponent == nullptr)
	{
		uiComponent = owner->FindComponent<UIComponent>();
		return;
	}

	UpdateTransition(deltaTime, currentFadingPhase);
}

void TransitionComponent::Shutdown()
{

}

void TransitionComponent::Serialize()
{

}

void TransitionComponent::Deserialize(const rapidjson::Value& json)
{
	if (json.HasMember("isFadeOut") && json["isFadeOut"].IsBool()) {
		isFadeOut = json["isFadeOut"].GetBool();

		if (isFadeOut)
		{
			currentFadingPhase = FadingPhase::FadeOut;
		}
		else 
		{
			currentFadingPhase = FadingPhase::FadeIn;
		}

		StartFading(currentFadingPhase);
	}
}

void TransitionComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{

}

void TransitionComponent::StartFading(FadingPhase fadingPhase)
{
	if (uiComponent == nullptr)
	{
		uiComponent = owner->FindComponent<UIComponent>();
	}

	if (fadingPhase == FadingPhase::FadeIn)
	{
		uiComponent->GetRenderable()->opacity = 0;
	}
	else
	{
		uiComponent->GetRenderable()->opacity = 1;
	}

	isTransition = true;
}

void TransitionComponent::UpdateTransition(float deltaTime, FadingPhase fadingPhase)
{
	if (fadingPhase == FadingPhase::FadeIn)
	{
		//Increase Opacity
		uiComponent->GetRenderable()->opacity += deltaTime * fadingSpeed;
		if (uiComponent->GetRenderable()->opacity >= 1.0f)
		{
			isTransition = false;
		}
	}
	else
	{
		//Decrease Opacity
		uiComponent->GetRenderable()->opacity -= deltaTime * fadingSpeed;
		if (uiComponent->GetRenderable()->opacity <= 0.0f)
		{
			isTransition = false;
		}
	}
}