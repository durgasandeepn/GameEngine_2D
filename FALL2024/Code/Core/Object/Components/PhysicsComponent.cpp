/****************************************************************
// File Name: PhysicsComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Component dedicated to handling physics. Currently, this simply
// holds reference to a PhysicsBody that gets updated by the PhysicsManager.
// TODO determine if a better solution exists
****************************************************************/

#include "precompiled.h"
#include "PhysicsComponent.h"
#include "Physics/PhysicsManager.h"
#include "Physics/OBB.h"
#include "Physics/AABB.h"
#include "Physics/Circle.h"
#include "Object/GameObject.h"

PhysicsComponent::PhysicsComponent()
{
	body = std::make_unique<PhysicsBody>();
}

void PhysicsComponent::Initialize()
{
    PhysicsManager::Instance().AddBody(body.get());
    body->SetOwner(owner);
}

void PhysicsComponent::Update(float deltaTime)
{
	// Update anything necessary before integration phase
}

void PhysicsComponent::Shutdown()
{
    PhysicsManager::Instance().RemoveBody(body.get());
    body.reset();
}

void PhysicsComponent::Serialize()
{
}

void PhysicsComponent::Deserialize(const rapidjson::Value& json)
{
    try {
        // Validate the JSON structure
        if (!json.IsObject()) {
            throw std::invalid_argument("Invalid JSON for RenderComponent2D: Expected an object.");
        }

        // Mass
        if (json.HasMember("mass") && json["mass"].IsNumber()) {
            body->SetMass(json["mass"].GetFloat());
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'mass'");
        }

        // Is Kinematic
        if (json.HasMember("isKinematic") && json["isKinematic"].IsBool()) {
            body->SetKinematic(json["isKinematic"].GetBool());
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'isKinematic'");
        }

        // Is Trigger
        if (json.HasMember("isTrigger") && json["isTrigger"].IsBool()) {
            body->SetTrigger(json["isTrigger"].GetBool());
        }

        // Use Gravity
        if (json.HasMember("useGravity") && json["useGravity"].IsBool()) {
            body->SetUseGravity(json["useGravity"].GetBool());
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'isKinematic'");
        }

        // Restitution
        if (json.HasMember("restitution") && json["restitution"].IsNumber()) {
            body->SetRestitution(json["restitution"].GetFloat());
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'restitution'");
        }

        // Friction
        if (json.HasMember("friction") && json["friction"].IsNumber()) {
            body->SetFriction(json["friction"].GetFloat());
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'friction'");
        }

        // Terminal velocity
        if (json.HasMember("terminalVelocity") && json["terminalVelocity"].IsNumber()) {
            body->SetTerminalVelocity(json["terminalVelocity"].GetFloat());
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'friction'");
        }

        // Drag
        if (json.HasMember("drag") && json["drag"].IsNumber()) {
            body->SetDrag(json["drag"].GetFloat());
        }

        // Velocity
        if (json.HasMember("velocity") && json["velocity"].IsObject()) {
            const auto& velocity = json["velocity"];
            if (velocity.HasMember("x") && velocity["x"].IsNumber() &&
                velocity.HasMember("y") && velocity["y"].IsNumber() &&
                velocity.HasMember("z") && velocity["z"].IsNumber()) {
                body->SetVelocity(Vector3(
                    velocity["x"].GetFloat(),
                    velocity["y"].GetFloat(),
                    velocity["z"].GetFloat()
                ));
            }
            else {
                throw std::invalid_argument("PhysicsComponent::Deserialize - Invalid 'velocity'");
            }
        }

        // Acceleration
        if (json.HasMember("acceleration") && json["acceleration"].IsObject()) {
            const auto& acceleration = json["acceleration"];
            if (acceleration.HasMember("x") && acceleration["x"].IsNumber() &&
                acceleration.HasMember("y") && acceleration["y"].IsNumber() &&
                acceleration.HasMember("z") && acceleration["z"].IsNumber()) {
                body->SetAcceleration(Vector3(
                    acceleration["x"].GetFloat(),
                    acceleration["y"].GetFloat(),
                    acceleration["z"].GetFloat()
                ));
            }
            else {
                throw std::invalid_argument("PhysicsComponent::Deserialize - Invalid 'acceleration'");
            }
        }

        // Force
        if (json.HasMember("force") && json["force"].IsObject()) {
            const auto& force = json["force"];
            if (force.HasMember("x") && force["x"].IsNumber() &&
                force.HasMember("y") && force["y"].IsNumber() &&
                force.HasMember("z") && force["z"].IsNumber()) {
                body->ApplyForce(Vector3(
                    force["x"].GetFloat(),
                    force["y"].GetFloat(),
                    force["z"].GetFloat()
                ));
            }
            else {
                throw std::invalid_argument("PhysicsComponent::Deserialize - Invalid 'force'");
            }
        }

        // Collision layer
        if (json.HasMember("layer") && json["layer"].IsString()) {
            body->SetLayer(StringToCollisionLayer(json["layer"].GetString()));
        }

        // CollisionMask
        if (json.HasMember("collisionMask") && json["collisionMask"].IsArray()) {
            const auto& maskArray = json["collisionMask"].GetArray();
            uint32_t newMask = 0;
            for (const auto& mask : maskArray) {
                if (mask.IsString()) {
                    newMask |= static_cast<uint32_t>(StringToCollisionLayer(mask.GetString()));
                }
            }
            body->SetCollisionMask(newMask);
        }

        // Shape
        if (json.HasMember("shape") && json["shape"].IsObject()) {
            const auto& shape = json["shape"];

            if (shape.HasMember("type") && shape["type"].IsString()) {
                std::string shapeType = shape["type"].GetString();

                if (shapeType == "OBB") {
                    if (shape.HasMember("center") && shape["center"].IsObject() &&
                        shape.HasMember("halfExtents") && shape["halfExtents"].IsObject()) {
                        const auto& center = shape["center"];
                        const auto& halfExtents = shape["halfExtents"];

                        Vector3 centerVec = Vector3(center["x"].GetFloat(), center["y"].GetFloat(), center["z"].GetFloat());
                        Vector3 halfExtentsVec = Vector3(halfExtents["x"].GetFloat(), halfExtents["y"].GetFloat(), halfExtents["z"].GetFloat());

                        body->SetShape(std::make_shared<OBB>(centerVec, halfExtentsVec));
                    }
                    else {
                        throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid OBB parameters");
                    }
                }
                else if (shapeType == "AABB") {
                    if (shape.HasMember("min") && shape["min"].IsObject() &&
                        shape.HasMember("max") && shape["max"].IsObject()) {
                        const auto& min = shape["min"];
                        const auto& max = shape["max"];

                        Vector3 minVec = Vector3(min["x"].GetFloat(), min["y"].GetFloat(), min["z"].GetFloat());
                        Vector3 maxVec = Vector3(max["x"].GetFloat(), max["y"].GetFloat(), max["z"].GetFloat());

                        body->SetShape(std::make_shared<AABB>(minVec, maxVec));
                    }
                    else {
                        throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid AABB parameters");
                    }
                }
                else if (shapeType == "Circle") {
                    if (shape.HasMember("center") && shape["center"].IsObject() &&
                        shape.HasMember("radius") && shape["radius"].IsFloat()) {
                        const auto& center = shape["center"];

                        Vector3 centerVec = Vector3(center["x"].GetFloat(), center["y"].GetFloat(), center["z"].GetFloat());
                        float radius = shape["radius"].GetFloat();

                        body->SetShape(std::make_shared<Circle>(centerVec, radius));
                    }
                    else {
                        throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid Circle parameters");
                    }
                }
                else {
                    throw std::invalid_argument("PhysicsComponent::Deserialize - Unsupported 'shape' type: " + shapeType);
                }
            }
            else {
                throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'type' field");
            }
        }
        else {
            throw std::invalid_argument("PhysicsComponent::Deserialize - Missing or invalid 'shape' field");
        }

        
    }
    catch (const std::exception& e) {
        std::cerr << "Error deserializing PhysicsComponent: " << e.what() << std::endl;
        throw; // Re-throw the exception after logging
    }
}

void PhysicsComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{

	for (const auto& [key, value] : properties) {
		if (key == "mass" && value.type() == typeid(float)) {
			body->SetMass(std::any_cast<float>(value));
		}
		else if (key == "isKinematic" && value.type() == typeid(bool)) {
			body->SetKinematic(std::any_cast<bool>(value));
		}
		else if (key == "velocity" && value.type() == typeid(Vector3)) {
			body->SetVelocity(std::any_cast<Vector3>(value));
		}
		else if (key == "acceleration" && value.type() == typeid(Vector3)) {
			body->SetAcceleration(std::any_cast<Vector3>(value));
		}
		if (key == "force" && value.type() == typeid(Vector3)) {
			body->ApplyForce(std::any_cast<Vector3>(value));
		}
		else if (key == "restitution" && value.type() == typeid(float)) {
			body->SetRestitution(std::any_cast<float>(value));
		}
		else if (key == "friction" && value.type() == typeid(float)) {
			body->SetFriction(std::any_cast<float>(value));
		}
		else if (key == "useGravity" && value.type() == typeid(bool)) {
			body->SetUseGravity(std::any_cast<bool>(value));
		}
		else if (key == "collisionShape" && value.type() == typeid(std::shared_ptr<Shape>)) {
			body->SetShape(std::any_cast<std::shared_ptr<Shape>>(value));
		}
	}
}

CollisionLayer PhysicsComponent::StringToCollisionLayer(const std::string& collisionString)
{
    if (collisionString == "Default" || collisionString == "default") {
        return CollisionLayer::Default;
    }
    else if (collisionString == "Player" || collisionString == "player") {
        return CollisionLayer::Player;
    }
    else if (collisionString == "Enemy" || collisionString == "enemy") {
        return CollisionLayer::Enemy;
    }
    else if (collisionString == "Environment" || collisionString == "environment") {
        return CollisionLayer::Environment;
    }
    else if (collisionString == "Projectile" || collisionString == "projectile") {
        return CollisionLayer::Projectile;
    }
    else {
        std::cerr << "Cannot recognize the following collision layer: " << collisionString << ", setting to Default." << std::endl;
        return CollisionLayer::Default;
    }
}
