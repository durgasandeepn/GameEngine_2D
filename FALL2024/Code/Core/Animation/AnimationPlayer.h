/****************************************************************
// File Name: AnimationController
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - upgrades and refactors
// Description: Handles playing a given animation from the AnimationClip data
****************************************************************/

#pragma once
#include "AnimationClip.h"
#include "Object/GameObject.h"

class AnimationPlayer
{
public:
	AnimationPlayer(const AnimationClip& anim, GameObject* _owner, bool _isLoop = false);
	void Update(float deltaTime);
	void SetAnimationClip(const AnimationClip& anim, bool _isLoop = false);
	void Play();
	void Stop();
	void Reset();
	void SetLoop(bool loop);
	int GetCurrentFrame() const;


private:
	AnimationClip animationClip;
	bool isLoop;
	bool isPlaying;
	int currentFrame;
	float elapsedTime;
	GameObject* owner;
	std::shared_ptr<Material> material{nullptr};
	Transform ownerOriginalTransform;

	void UpdateFlipbook();
	void UpdateAffine(float deltaTime);
};

