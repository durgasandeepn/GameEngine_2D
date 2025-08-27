/****************************************************************
// File Name: RenderComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Component dedicated to handling rendering Objects in the game.
// Creates a renderable object and manages it's lifecycle
****************************************************************/

#include "precompiled.h"
#include "RenderComponent2D.h"
#include "Renderer/RenderManager.h"
#include "ResourceManagement/ResourceManager.h"

RenderComponent2D::RenderComponent2D()
{
    renderable = std::make_unique<Renderable>();
}

void RenderComponent2D::Initialize()
{
    RenderManager::Instance().AddRenderable(renderable.get());
    renderable->SetOwner(owner);
}

void RenderComponent2D::Update(float deltaTime)
{
   
}

void RenderComponent2D::Shutdown()
{
    RenderManager::Instance().RemoveRenderable(renderable.get());
    renderable.reset();
}

void RenderComponent2D::Serialize()
{
}

void RenderComponent2D::Deserialize(const rapidjson::Value& json)
{
    // Validate the JSON structure
    if (!json.IsObject()) {
        throw std::invalid_argument("Invalid JSON for RenderComponent2D: Expected an object.");
    }

    // isVisible
    if (json.HasMember("isVisible") && json["isVisible"].IsBool()) {
        renderable->SetVisible(json["isVisible"].GetBool());
    }
    else {
        throw std::invalid_argument("RenderComponent2D: Missing or invalid 'isVisible' property.");
    }

    // Material
    if (json.HasMember("material") && json["material"].IsObject()) {
        renderable->SetMaterial(ParseMaterial(json["material"]));
    }
    else {
        throw std::invalid_argument("RenderComponent2D: Missing or invalid 'material' property.");
    }

    // Mesh
    if (json.HasMember("mesh") && json["mesh"].IsObject()) {
        renderable->SetMesh(ParseMesh(json["mesh"]));
    }
    else {
        renderable->SetMesh(CreateMesh());
    }
}

void RenderComponent2D::Configure(const std::unordered_map<std::string, std::any>& properties)
{
    // TODO if we need to pass in things, this is how we do it
    for (const auto& [key, value] : properties) {
        if (key == "renderer" && value.type() == typeid(Renderer*)) {
            renderable->SetRender(std::any_cast<Renderer*>(value));
        }
        else if (key == "camera" && value.type() == typeid(CameraComponent*)) {
            renderable->SetCamera(std::any_cast<CameraComponent*>(value));
        }
        else if (key == "material" && value.type() == typeid(std::shared_ptr<Material>)) {
            renderable->SetMaterial(std::any_cast<std::shared_ptr<Material>>(value));
        }
        else if (key == "mesh" && value.type() == typeid(std::shared_ptr<Mesh>)) {
            renderable->SetMesh(std::any_cast<std::shared_ptr<Mesh>>(value));
        }
    }

    if (!renderable->GetMesh())
        renderable->SetMesh(CreateMesh());
}

std::shared_ptr<Material> RenderComponent2D::ParseMaterial(const rapidjson::Value& materialJson) const
{
    if (!materialJson.IsObject()) {
        throw std::invalid_argument("RenderComponent2D: Invalid 'material' object.");
    }

    auto shader = ParseShader(materialJson);
    auto newMaterial = std::make_shared<Material>(shader);

    if (materialJson.HasMember("texture") && materialJson["texture"].IsString()) {
        ApplyTexture(materialJson["texture"].GetString(), newMaterial);
    }

    return newMaterial;
}

std::shared_ptr<Shader> RenderComponent2D::ParseShader(const rapidjson::Value& materialJson) const
{
    if (materialJson.HasMember("shader") && materialJson["shader"].IsString()) {
        std::string shaderPaths = materialJson["shader"].GetString();
        auto shader = ResourceManager::Instance().LoadShader(shaderPaths);

        if (!shader) {
            throw std::runtime_error("RenderComponent2D: Failed to load shader for material.");
        }
        return shader;
    }
    else {
        throw std::invalid_argument("RenderComponent2D: Missing or invalid 'shader' property in material.");
    }
}

void RenderComponent2D::ApplyTexture(const std::string& textureName, std::shared_ptr<Material>& material) const
{
    auto texture = ResourceManager::Instance().LoadTexture(textureName);

    if (texture) {
        material->SetTexture("Texture", texture, 0); // Assuming Material has a SetTexture method
        material->SetProperty("useTexture", 1);
        material->SetProperty("isTransparent", 1);
    }
    else {
        std::cerr << "RenderComponent2D: Failed to load texture: " << textureName << std::endl;
    }
}

std::shared_ptr<Mesh> RenderComponent2D::ParseMesh(const rapidjson::Value& json) const
{
    if (!json.IsObject()) {
        throw std::invalid_argument("ParseMesh: Expected an object.");
    }

    // Validate and parse vertices
    if (!json.HasMember("vertices") || !json["vertices"].IsArray()) {
        throw std::invalid_argument("ParseMesh: Missing or invalid 'vertices' array.");
    }

    const auto& verticesJson = json["vertices"];
    std::vector<float> vertices;

    // Simply add all values from the 'vertices' array directly
    for (const auto& vertexJson : verticesJson.GetArray()) {
        if (!vertexJson.IsNumber()) {
            throw std::invalid_argument("ParseMesh: Invalid vertex value format.");
        }
        vertices.push_back(vertexJson.GetFloat());
    }

    // Validate and parse texture coordinates if present
    std::vector<float> texCoords;
    if (json.HasMember("texCoords") && json["texCoords"].IsArray()) {
        const auto& texCoordsJson = json["texCoords"];
        // Simply add all values from the 'texCoords' array directly
        for (const auto& texCoordJson : texCoordsJson.GetArray()) {
            if (!texCoordJson.IsNumber()) {
                throw std::invalid_argument("ParseMesh: Invalid texCoord value format.");
            }
            texCoords.push_back(texCoordJson.GetFloat());
        }

        // Ensure texCoords size matches vertices count
        if (texCoords.size() / 2 != vertices.size() / 3) {
            throw std::invalid_argument("ParseMesh: Mismatch between vertices and texCoords count.");
        }
    }

    // Validate and parse indices
    if (!json.HasMember("indices") || !json["indices"].IsArray()) {
        throw std::invalid_argument("ParseMesh: Missing or invalid 'indices' array.");
    }

    const auto& indicesJson = json["indices"];
    std::vector<unsigned int> indices;

    for (const auto& indexJson : indicesJson.GetArray()) {
        if (!indexJson.IsUint()) {
            throw std::invalid_argument("ParseMesh: Invalid index format.");
        }
        indices.push_back(indexJson.GetUint());
    }

    // Create the mesh
    auto mesh = std::make_shared<Mesh>(owner->GetName() + "_Mesh");
    std::vector<VertexData> vertexData = {
        {GeometryBuffer::Attribute::Position, vertices, 3}
    };

    if (!texCoords.empty()) {
        vertexData.push_back({ GeometryBuffer::Attribute::TexCoord, texCoords, 2 });
    }

    mesh->SetVertexData(vertexData, indices);
    return mesh;
}

std::shared_ptr<Mesh> RenderComponent2D::CreateMesh()
{
    // This is specific to Squares
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    std::vector<float> texCoords = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    auto mesh = std::make_shared<Mesh>(owner->GetName() + "_Mesh");
    mesh->SetVertexData
    ({
        {GeometryBuffer::Attribute::Position, vertices, 3},
        {GeometryBuffer::Attribute::TexCoord, texCoords, 2}
        }, indices
    );

    return mesh;
}
