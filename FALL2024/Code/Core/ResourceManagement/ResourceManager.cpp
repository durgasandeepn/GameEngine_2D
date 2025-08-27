/****************************************************************
// File Name: ResourceManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Tool used to get external data, things like JSON files, Shaders, and meshes.
****************************************************************/

#include "precompiled.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <unordered_map>
#include <algorithm>
#include "Engine.h"

void ResourceManager::Initialize(Renderer* renderer, AudioManager* audioManager, GameWindow* window)
{
	this->renderer = renderer;
	this->audioManager = audioManager;
	this->window = window;

	ComponentCreator::Instance().RegisterComponent<RenderComponent2D>("RenderComponent2D");
	ComponentCreator::Instance().RegisterComponent<PhysicsComponent>("PhysicsComponent");
	ComponentCreator::Instance().RegisterComponent<AudioSourceComponent>("AudioSourceComponent");
	ComponentCreator::Instance().RegisterComponent<InputComponent>("InputComponent");
	ComponentCreator::Instance().RegisterComponent<UIComponent>("UIComponent");
	ComponentCreator::Instance().RegisterComponent<DebugRenderComponent>("DebugRenderComponent");

	ComponentCreator::Instance().RegisterComponent<CameraComponent>("CameraComponent");
	ComponentCreator::Instance().RegisterComponent<AnimationComponent>("AnimationComponent");
	ComponentCreator::Instance().RegisterComponent<UIButtonComponent>("UIButtonComponent");
	ComponentCreator::Instance().RegisterComponent<UISliderComponent>("UISliderComponent");
	ComponentCreator::Instance().RegisterComponent<UIElementManagerComponent>("UIElementManagerComponent");
}

GameObject* ResourceManager::LoadGameObjectFromJSON(const std::string& filename)
{
	std::string jsonPath = "Code/Application/JSONObjects/" + filename;
	// Open and read JSON file
	std::ifstream file(jsonPath);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return nullptr;
	}

	rapidjson::IStreamWrapper isw(file);
	rapidjson::Document doc;
	if (doc.ParseStream(isw).HasParseError()) {
		std::cerr << "Error parsing JSON file: " << filename << std::endl;
		return nullptr;
	}

	// Create game object using factory
	auto gameObject = GameObjectFactory::Instance().CreateFromJSON(doc);

	if (!gameObject) {
		std::cerr << "Failed to create GameObject from: " << filename << std::endl;
		return nullptr;
	}

	// Configure engine-level components
	if (auto renderComp = gameObject->FindComponent<RenderComponent2D>()) {
		renderComp->GetRenderable()->SetRender(renderer);
	}

	if (auto UIComp = gameObject->FindComponent<UIComponent>()) {
		UIComp->GetRenderable()->SetRender(renderer);
	}

	if (auto DebugRenderComp = gameObject->FindComponent<DebugRenderComponent>()) {
		DebugRenderComp->GetRenderable()->SetRender(renderer);
	}

	if (auto audioComp = gameObject->FindComponent<AudioSourceComponent>()) {
		audioComp->SetAudioSystem(audioManager);
	}

	if (auto cameraComp = gameObject->FindComponent<CameraComponent>()) {
		cameraComp->SetWindow(window);
	}

	return gameObject;
}


std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& shaderPaths)
{
	std::istringstream pathStream(shaderPaths);
	std::string shaderPath;
	std::unordered_map<GLenum, std::string> shaderSources;

	while (std::getline(pathStream, shaderPath))
	{
		std::string shaderFilePath = "Code/Application/Shaders/" + shaderPath;
		std::string shaderCode = ReadTextFile(shaderFilePath);
		GLenum shaderType = GetShaderType(shaderPath);

		if (shaderType != GL_INVALID_ENUM)
		{
			shaderSources[shaderType] = shaderCode;
		}
		else
		{
			std::cerr << "Unrecognized shader type for file: " << shaderPath << std::endl;
		}
	}

	return std::make_shared<Shader>(shaderSources);
}


std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& texturePath, Texture::TextureType type)
{
	// Check if the texture is already loaded
	/*auto it = textureCache.find(filepath);
	if (it != textureCache.end()) {
		return it->second;
	}*/

	// Read file and load the texture
	int width, height, channels;
	unsigned char* data = LoadImageFile(texturePath, width, height, channels);
	if (!data) {
		std::cerr << "Failed to load texture: " << texturePath << std::endl;
		return nullptr;
	}

	// Create the texture using the raw data
	auto texture = std::make_shared<Texture>(data, width, height, channels, type);
	//textureCache[filepath] = texture;

	// Free raw data after uploading to GPU
	stbi_image_free(data);

	return texture;
}

std::string ResourceManager::ReadTextFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return "";
	}
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	file.close();
	return fileStream.str();
}

unsigned char* ResourceManager::LoadImageFile(const std::string& filepath, int& width, int& height, int& channels)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
	if (!data) {
		std::cerr << "Error loading texture file: " << filepath << " - " << stbi_failure_reason() << std::endl;
	}
	return data;
}

// Determines type of shader using file path
GLenum ResourceManager::GetShaderType(const std::string& filepath)
{
	std::string lowercasePath = ToLowerCase(filepath);
	if (lowercasePath.find("vertex") != std::string::npos) return GL_VERTEX_SHADER;
	if (lowercasePath.find("fragment") != std::string::npos) return GL_FRAGMENT_SHADER;
	if (lowercasePath.find("geometry") != std::string::npos) return GL_GEOMETRY_SHADER;
	if (lowercasePath.find("compute") != std::string::npos) return GL_COMPUTE_SHADER;
	return GL_INVALID_ENUM;
}

std::string ResourceManager::ToLowerCase(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
}

void ResourceManager::Shutdown()
{
	renderer = nullptr;
	audioManager = nullptr;
	window = nullptr;
}
