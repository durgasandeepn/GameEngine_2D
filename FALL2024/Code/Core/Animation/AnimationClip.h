/****************************************************************
// File Name: AnimationClip
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn
// Description: Handles data relating to an animation.
// Things like the different frames of the AffineTransformation animation
// As well as the frame count, width, and height for a flipbook animation
****************************************************************/

#pragma once
#include "Math/Vector3.h"
#include <vector>

struct AffineTransformation 
{
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

struct AffineAnimation
{
    bool isTransformFromOrigin;
    AffineTransformation originTransform;
    std::vector<AffineTransformation> keyframesTransformation;
};

struct FlipBookAnimation
{
    int animIndex;
    int frameCount;
    float frameWidth;
    float frameHeight;

    bool frameScale = false;
};

struct AnimationClip
{
    AffineAnimation affineAnimation;
    FlipBookAnimation flipBookAnimation;
    float timePerFrame;
    int totalFrames;
};