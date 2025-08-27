/****************************************************************
// File Name: TransitionManager
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: System for managing transitions between game scenes
****************************************************************/

#include "precompiled.h"
#include "TransitionManager.h"

void TransitionManager::CreateFadeOutUI()
{
	GameObject::Instantiate("UI/FadeBlackUI/fadeOutUI.json");
}

void TransitionManager::CreateFadeInUI()
{
	GameObject::Instantiate("UI/FadeBlackUI/fadeInUI.json");
	countDown = 1.0f;
	isFadingInActive = true;
}

void TransitionManager::Update(float deltaTime)
{
	if (isFadingInActive) 
	{
		countDown -= deltaTime;
		if (countDown <= 0) 
		{
			isFadingInActive = false;
			ExecuteQueuedChange();
		}
	}
}
