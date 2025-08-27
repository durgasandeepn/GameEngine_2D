/****************************************************************
// File Name: AnimationController
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - upgrades and refactors
// Description: Handles playing a given animation from the AnimationClip data
****************************************************************/

#include "precompiled.h"
#include "AnimationPlayer.h"
#include "Object/Components/RenderComponent2D.h"
#include "Object/Components/UIComponent.h"
#include <algorithm>

AnimationPlayer::AnimationPlayer(const AnimationClip& anim, GameObject* _owner, bool _isLoop) :
                                                                            animationClip(anim), isLoop(_isLoop),
																			isPlaying(false), currentFrame(0), elapsedTime(0.0f),
                                                                            owner(_owner)
{

    ownerOriginalTransform.SetPosition(owner->GetLocalPosition());
    ownerOriginalTransform.SetRotation(owner->GetLocalRotation());
    ownerOriginalTransform.SetScale(owner->GetLocalScale());
}

void AnimationPlayer::Update(float deltaTime)
{
    if (material == nullptr) {
        std::shared_ptr<RenderComponent2D> renderComponent = owner->FindComponent<RenderComponent2D>();
        if (renderComponent)
            material = renderComponent->GetRenderable()->GetMaterial();
        else {
            std::shared_ptr<UIComponent> uiRenderComponent = owner->FindComponent<UIComponent>();
            if (uiRenderComponent) {
                material = uiRenderComponent->GetRenderable()->GetMaterial();
            }
            else return;
        }
    }
    if (isPlaying)
    {
        if (animationClip.totalFrames > 0) 
        {
            elapsedTime += deltaTime;

            if (elapsedTime >= animationClip.timePerFrame) 
            {
                elapsedTime -= animationClip.timePerFrame;
                currentFrame = (currentFrame + 1) % animationClip.totalFrames;

                if (currentFrame == animationClip.totalFrames - 1)
                {
                    isPlaying = isLoop;
                }
            }

            UpdateAffine(deltaTime);
            UpdateFlipbook();
        }
    }
}

void AnimationPlayer::SetAnimationClip(const AnimationClip& anim, bool _isLoop)
{
	animationClip = anim;
	isLoop = _isLoop;
}

void AnimationPlayer::Play()
{
	isPlaying = true;
}

void AnimationPlayer::Stop()
{
	isPlaying = false;
}

void AnimationPlayer::Reset()
{
    elapsedTime = 0;
    currentFrame = 0;

    if (!animationClip.affineAnimation.keyframesTransformation.empty()) {
        owner->SetLocalPosition(ownerOriginalTransform.GetPosition());
        owner->SetLocalRotation(ownerOriginalTransform.GetRotation());
        owner->SetLocalScale(ownerOriginalTransform.GetScale());
    }
}

void AnimationPlayer::SetLoop(bool loop)
{
	isLoop = loop;
}

int AnimationPlayer::GetCurrentFrame() const
{
	return currentFrame;
}

void AnimationPlayer::UpdateFlipbook()
{
    if (currentFrame <= animationClip.flipBookAnimation.frameCount) 
    {
        float left = currentFrame * animationClip.flipBookAnimation.frameWidth;
        float top = 1.0f - (animationClip.flipBookAnimation.frameHeight * animationClip.flipBookAnimation.animIndex);
        Vector3 offset = Vector3(left, top, 0);

        if (material != nullptr)
        {
            // DO NOT REMOVE THIS.
            // Unless you want your animations to **not work**
            material->Apply();
            material->SetTextureOffset(offset);
            if (animationClip.flipBookAnimation.frameScale) {
                material->SetFrameSize(Vector3(animationClip.flipBookAnimation.frameWidth, animationClip.flipBookAnimation.frameHeight, 0.0f));
            }
        }
    }
}

void AnimationPlayer::UpdateAffine(float deltaTime)
{
    if (!animationClip.affineAnimation.keyframesTransformation.empty()) {
        int keyFrameCount{ int(animationClip.affineAnimation.keyframesTransformation.size()) }; // Num affine frames
        int framesPerKeyframe = animationClip.totalFrames / keyFrameCount;

        int currFrame = std::min(currentFrame / framesPerKeyframe, keyFrameCount - 1);
        int nextFrame = (currFrame + 1) % keyFrameCount;

        AffineTransformation currentKeyframe = animationClip.affineAnimation.keyframesTransformation[currFrame];
        AffineTransformation nextKeyframe = animationClip.affineAnimation.keyframesTransformation[nextFrame];

        float t = elapsedTime / animationClip.timePerFrame;
        t = std::clamp(t, 0.0f, 1.0f);

        // Lerp position, rotation, and scale.
        Vector3 interpolatedPosition = currentKeyframe.position.Lerp(nextKeyframe.position, t);
        Vector3 interpolatedRotation = currentKeyframe.rotation.Lerp(nextKeyframe.rotation, t);
        Vector3 interpolatedScale = currentKeyframe.scale.Lerp(nextKeyframe.scale, t);

        if (animationClip.affineAnimation.isTransformFromOrigin)
        {
            AffineTransformation originTransform = animationClip.affineAnimation.originTransform;
            interpolatedPosition += originTransform.position;
            interpolatedRotation += originTransform.rotation;
            interpolatedScale += originTransform.scale;
        }

        owner->SetLocalPosition(interpolatedPosition);
        owner->SetLocalRotation(interpolatedRotation);
        owner->SetLocalScale(interpolatedScale);
    }
}
