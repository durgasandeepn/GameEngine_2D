/****************************************************************
// File Name: ResourceManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Tool used to get external data, things like JSON files, Shaders, and meshes.
****************************************************************/

#pragma once
#include <memory>
#include <fstream>
#include "document.h"
#include "istreamwrapper.h"
#include "Object/Components/Component.h"
#include "Object/Components/RenderComponent2D.h"
#include "Object/Components/UIComponent.h"
#include "Object/Components/PhysicsComponent.h"
#include "Object/Components/AudioSourceComponent.h"
#include "Object/Components/InputComponent.h"
#include "Object/Components/CameraComponent.h"
#include "Object/Components/AnimationComponent.h"
#include "Object/Components/DebugRenderComponent.h"
#include "Object/Components/UIButtonComponent.h"
#include "Object/Components/UISliderComponent.h"
#include "Object/Components/UIElementManagerComponent.h"
#include "SceneManagement/SceneGraph.h"
#include "Object/ComponentCreator.h"
#include "Object/GameObjectFactory.h"
#include <glew.h>
#include "Sound/AudioManager.h"

class ResourceManager {

public:
	static ResourceManager& Instance() {
		static ResourceManager instance;
		return instance;
	}

	/**
	* @brief Initializes references to Engine level systems to be passed in to engine
	* level components. Also registers engine level components with the ComponentCreator
	* @param renderer - Reference to the renderer system to be passed into RenderComponents
	*/
	void Initialize(Renderer* renderer, AudioManager* audioManager, GameWindow* window);

	/**
	* @brief Given a JSON file name, return the relative GameObject. 
	* to parse the correlating JSON file from the filename and turn it into a GameObject
	* @param filename - name of the JSON file object (contained in Application/JSONObjects)
	* @return a shared pointer to the returned GameObject
	*/
	GameObject* LoadGameObjectFromJSON(const std::string& filename);

	/**
	* @brief Given a Shader file name, return the relative Shader object.
	* @param filename - name of the Shader file(s) to load (contained in Application/Shaders) Ex. "vertex_shader.glsl\nfragment_shader.glsl"
	* @return a shared pointer to the returned Shader
	*/
	std::shared_ptr<Shader> LoadShader(const std::string& shaderPaths);
	GLenum GetShaderType(const std::string& filepath);

	/**
	* @brief Given a Texture file name, return the relative Texture object.
	* @param filename - name of the Texture file to load (contained in Assets/Textures) Ex. "Assets/Textures/moonrock.png"
	* @return a shared pointer to the returned Shader
	*/
	std::shared_ptr<Texture> LoadTexture(const std::string& texturePath, Texture::TextureType type = Texture::TextureType::Texture2D);

	/**
	* NOT IMPLEMENTED YET
	* @brief Given a Mesh file name, return the relative Mesh object.
	* @param filename - name of the Mesh file to load (contained in) Ex. ""
	* @return a shared pointer to the returned Mesh
	*/
	std::shared_ptr<Mesh> LoadMesh(const std::string& meshPath);
	
	// Cleanup resources
	void Shutdown();

private:
	Renderer* renderer{ nullptr };
	GameWindow* window{ nullptr };
	AudioManager* audioManager{ nullptr };

	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	/* Utility functions */
	/**
	* @brief Given a file path to a text file, return the relative text as a string
	* @param filePath - name of the text file to load
	* @return std::string representing the text from the file
	*/
	std::string ReadTextFile(const std::string& filePath);
	/**
	* @brief Given a file path to an image file, return the relative image data
	* @param filePath - name of the image file to load
	* @param width - stores the width of the image in this param
	* @param height - stores the height of the image in this param
	* @param channels - stores the channels of the image in this param
	* @return unsigned char* representing the data of the image
	*/
	unsigned char* LoadImageFile(const std::string& filepath, int& width, int& height, int& channels);
	std::string ToLowerCase(const std::string& str);
};