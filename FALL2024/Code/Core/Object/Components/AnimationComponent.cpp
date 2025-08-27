/****************************************************************
// File Name: AnimationComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Ju-ve Chankasemporn - base code, Alex Humphries - deserializing
// Description: Component dedicated to handling "animations" for game objects.
// An animation can be a "flipbook" animation, which is a simple 2D animation
// where the texture gets changed depending on the frame of a sprite sheet
// or an affine animation. Both work with this system.
****************************************************************/

#include "precompiled.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent()
{
	animationController = new AnimationController();
}

void AnimationComponent::Initialize()
{
}

void AnimationComponent::Update(float deltaTime)
{
	if (animationController != nullptr) 
	{
		animationController->Update(deltaTime);
	}
}

void AnimationComponent::Shutdown()
{
}

void AnimationComponent::Serialize()
{
}

void AnimationComponent::Deserialize(const rapidjson::Value& json)
{
    try {
        // Validate the JSON structure
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for AnimationComponent: Expected an object.");
        }

        // States
        if (json.HasMember("states") && json["states"].IsArray()) {
            // For each state
            const auto& states = json["states"].GetArray();
            for (const auto& state : states) {
                // These are required for a state
                std::string stateName;
                AnimationClip anim;
                bool isLooping;
                // State's name
                if (state.HasMember("name") && state["name"].IsString()) {
                    stateName = state["name"].GetString();
                }
                else {
                    throw std::invalid_argument("Invalid JSON for AnimationComponent: State is missing 'name'");
                }
                // Affine animation
                if (state.HasMember("affine") && state["affine"].IsObject()) {
                    const auto& affineJSON = state["affine"].GetObject();
                    AffineAnimation affine;

                    // isTransformFromOrigin
                    if (affineJSON.HasMember("isTransformFromOrigin") && affineJSON["isTransformFromOrigin"].IsBool()) {
                        affine.isTransformFromOrigin = affineJSON["isTransformFromOrigin"].GetBool();
                    }
                    else {
                        affine.isTransformFromOrigin = false;
                    }

                    // originTransform
                    if (affineJSON.HasMember("originTransform") && affineJSON["originTransform"].IsObject()) {
                        if (affine.isTransformFromOrigin) {
                            AffineTransformation originTransform = GetAffineTransformationFromJSON(affineJSON["originTransform"].GetObject());
                            affine.originTransform = originTransform;
                        }
                        else {
                            throw std::invalid_argument("Invalid JSON for AnimationComponent: Affine animation set isTransformOrigin to false, but contains a originTransform");
                        }
                    }
                    else {
                        // Use the default from owner
                        Vector3 originalPos = owner->GetLocalPosition();
                        Vector3 originalRotation = owner->GetLocalRotation();
                        Vector3 originalScale = owner->GetLocalScale();
                        affine.originTransform = { originalPos, originalRotation, originalScale };
                    }

                    // Key Frames
                    if (affineJSON.HasMember("keyFramesTransformation") && affineJSON["keyFramesTransformation"].IsArray()) {
                        std::vector<AffineTransformation> keyFrames;
                        const auto& frames = affineJSON["keyFramesTransformation"].GetArray();
                        for (const auto& frame : frames) {
                            AffineTransformation frameTransform = GetAffineTransformationFromJSON(frame);
                            keyFrames.push_back(frameTransform);
                        }
                        if (!keyFrames.empty()) {
                            affine.keyframesTransformation = keyFrames;
                        }
                        else {
                            throw std::invalid_argument("Invalid JSON for AnimationComponent: Affine animation has empty list for keyFramesTransformation");
                        }
                    }
                    else {
                        throw std::invalid_argument("Invalid JSON for AnimationComponent: Affine animation has missing or invalid keyFramesTransformation");
                    }

                    anim.affineAnimation = affine;
                }
                // Flipbook animation
                if (state.HasMember("flipbook") && state["flipbook"].IsObject()) {
                    const auto& flipbookJSON = state["flipbook"].GetObject();
                    FlipBookAnimation flipbook;
                    if (flipbookJSON.HasMember("animIndex") && flipbookJSON["animIndex"].IsNumber()) {
                        flipbook.animIndex = flipbookJSON["animIndex"].GetInt();
                    }
                    else {
                        throw std::invalid_argument("Invalid JSON for AnimationComponent: Flipbook animation has missing or invalid animIndex.");
                    }
                    if (flipbookJSON.HasMember("frameCount") && flipbookJSON["frameCount"].IsNumber()) {
                        flipbook.frameCount = flipbookJSON["frameCount"].GetInt();
                    }
                    else {
                        throw std::invalid_argument("Invalid JSON for AnimationComponent: Flipbook animation has missing or invalid frameCount.");
                    }
                    if (flipbookJSON.HasMember("frameWidth") && flipbookJSON["frameWidth"].IsNumber()) {
                        flipbook.frameWidth = flipbookJSON["frameWidth"].GetFloat();
                    }
                    else {
                        throw std::invalid_argument("Invalid JSON for AnimationComponent: Flipbook animation has missing or invalid frameWidth.");
                    }
                    if (flipbookJSON.HasMember("frameHeight") && flipbookJSON["frameHeight"].IsNumber()) {
                        flipbook.frameHeight = flipbookJSON["frameHeight"].GetFloat();
                    }
                    else {
                        throw std::invalid_argument("Invalid JSON for AnimationComponent: Flipbook animation has missing or invalid frameHeight.");
                    }
                    if (flipbookJSON.HasMember("frameScale") && flipbookJSON["frameScale"].IsBool()) {
                        flipbook.frameScale = flipbookJSON["frameScale"].GetBool();
                    }
                    anim.flipBookAnimation = flipbook;
                }
                if (state.HasMember("timePerFrame") && state["timePerFrame"].IsNumber()) {
                    anim.timePerFrame = state["timePerFrame"].GetFloat();
                }
                else {
                    throw std::invalid_argument("Invalid JSON for AnimationComponent: Animation has missing or invalid timePerFrame.");
                }
                if (state.HasMember("totalFrames") && state["totalFrames"].IsNumber()) {
                    anim.totalFrames = state["totalFrames"].GetInt();
                }
                else {
                    throw std::invalid_argument("Invalid JSON for AnimationComponent: Animation has missing or invalid totalFrames.");
                }
                if (state.HasMember("isLoop") && state["isLoop"].IsBool()) {
                    isLooping = state["isLoop"].GetBool();
                }
                else {
                    throw std::invalid_argument("Invalid JSON for AnimationComponent: Animation has missing or invalid isLoop.");
                }

                AnimationPlayer* animState = new AnimationPlayer(anim, owner, isLooping);
                animationController->AddAnimationState(stateName, animState);
            }
        }
        else {
            throw std::invalid_argument("AnimationComponent::Deserialize - Missing or invalid 'states'");
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing AnimationComponent: " << e.what() << std::endl;
        throw; // Re-throw the exception after logging
    }
}

void AnimationComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

void AnimationComponent::ChangeAnimationState(std::string animationState)
{
	animationController->ChangeAnimationState(animationState);
}

std::string AnimationComponent::GetCurrentState()
{
	return animationController->GetCurrentState();
}

AffineTransformation AnimationComponent::GetAffineTransformationFromJSON(const rapidjson::Value& transformationJSON)
{
    Vector3 position, rotation, scale(1, 1, 1); // Default transform values

    if (transformationJSON.HasMember("position") && transformationJSON["position"].IsObject()) {
        const auto& pos = transformationJSON["position"];
        position = Vector3(pos["x"].GetFloat(), pos["y"].GetFloat(), pos["z"].GetFloat());
    }

    if (transformationJSON.HasMember("rotation") && transformationJSON["rotation"].IsObject()) {
        const auto& rot = transformationJSON["rotation"];
        rotation = Vector3(rot["x"].GetFloat(), rot["y"].GetFloat(), rot["z"].GetFloat());
    }

    if (transformationJSON.HasMember("scale") && transformationJSON["scale"].IsObject()) {
        const auto& sc = transformationJSON["scale"];
        scale = Vector3(sc["x"].GetFloat(), sc["y"].GetFloat(), sc["z"].GetFloat());
    }

    AffineTransformation transformation = { position, rotation, scale };
    return transformation;
}
