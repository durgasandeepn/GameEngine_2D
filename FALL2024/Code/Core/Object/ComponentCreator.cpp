/****************************************************************
// File Name: ComponentCreator
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez
// Description: A singleton class used to both dynamically register new component types
// (coming from a Gameplay programmer), as well as add components to a GameObject.
// This is sort of a black box for me, here's how I think it works.
// Since we're using Templates, we need a unique function for adding a templated Component to a GameObject
// (gameObject->AddComponent<MovementComponent2D> for example).
// This component holds a map of component name to the function needed to add that component to a GameObject.
// (
// "MovementComponent2D" : [](std::shared_ptr<GameObject> gameObject) -> std::shared_ptr<Component> {
//			return gameObject->AddComponent<MovementComponent2D>();
//		};
//	)
// So you first register the component name and add function to the map, then later on you can add the Component without trouble.
****************************************************************/

#include "precompiled.h"
#include "ComponentCreator.h"

std::shared_ptr<Component> ComponentCreator::CreateAndAddComponent(const std::string& typeName, GameObject* gameObject)
{
    auto iterator = creators.find(typeName); // Search for creator function
    if (iterator != creators.end()) {
        // Call the creator's add component function for typename
        // remember; first is typename of the component (i.e. PhysicsComponent)
        // second is the creator function (AddComponent())
        return iterator->second(gameObject);
    }

    return nullptr;
}
