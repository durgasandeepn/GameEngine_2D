/****************************************************************
// File Name: UIComponent
// © 2025 DigiPen (USA) Corporation
// Authors: Durga Sandeep - Created the base, Ju-ve Chankasemporn - advised in development
// Description: Component for rendering the UI
****************************************************************/

#include "precompiled.h"
#include "UIComponent.h"
#include "Renderer/RenderManager.h"
#include "ResourceManagement/ResourceManager.h"

UIComponent::UIComponent()
{
    renderable = std::make_unique<Renderable>();
}

void UIComponent::Initialize()
{
    RenderManager::Instance().AddUIRenderable(renderable.get());
    renderable->SetOwner(owner);
}

void UIComponent::Update(float deltaTime)
{

}

void UIComponent::Shutdown()
{
    RenderManager::Instance().RemoveUIRenderable(renderable.get());
    renderable.reset();
}

void UIComponent::Serialize()
{
}

void UIComponent::Deserialize(const rapidjson::Value& json)
{
    // Validate the JSON structure
    if (!json.IsObject()) {
        throw std::invalid_argument("Invalid JSON for UIComponent: Expected an object.");
    }

    // isVisible
    if (json.HasMember("isVisible") && json["isVisible"].IsBool()) {
        renderable->SetVisible(json["isVisible"].GetBool());
    }
    else {
        throw std::invalid_argument("UIComponent: Missing or invalid 'isVisible' property.");
    }

    // Material
    if (json.HasMember("material") && json["material"].IsObject()) {
        renderable->SetMaterial(ParseMaterial(json["material"]));
    }
    else {
        throw std::invalid_argument("UIComponent: Missing or invalid 'material' property.");
    }

    // Mesh
    if (json.HasMember("mesh") && json["mesh"].IsObject()) {
        renderable->SetMesh(ParseMesh(json["mesh"]));
    }
    else {
        renderable->SetMesh(CreateMesh());
    }
}

void UIComponent::Configure(const std::unordered_map<std::string, std::any>& properties)
{
}

std::shared_ptr<Material> UIComponent::ParseMaterial(const rapidjson::Value& materialJson) const
{
    if (!materialJson.IsObject()) {
        throw std::invalid_argument("UIComponent: Invalid 'material' object.");
    }

    auto shader = ParseShader(materialJson);
    auto newMaterial = std::make_shared<Material>(shader);

    if (materialJson.HasMember("texture") && materialJson["texture"].IsString()) {
        ApplyTexture(materialJson["texture"].GetString(), newMaterial);
    }

    return newMaterial;
}

std::shared_ptr<Shader> UIComponent::ParseShader(const rapidjson::Value& materialJson) const
{
    if (materialJson.HasMember("shader") && materialJson["shader"].IsString()) {
        std::string shaderPaths = materialJson["shader"].GetString();
        auto shader = ResourceManager::Instance().LoadShader(shaderPaths);

        if (!shader) {
            throw std::runtime_error("UIComponent: Failed to load shader for material.");
        }
        return shader;
    }
    else {
        throw std::invalid_argument("UIComponent: Missing or invalid 'shader' property in material.");
    }
}

void UIComponent::ApplyTexture(const std::string& textureName, std::shared_ptr<Material>& material) const
{
    auto texture = ResourceManager::Instance().LoadTexture(textureName);

    if (texture) {
        material->SetTexture("Texture", texture, 0); // Assuming Material has a SetTexture method
        material->SetProperty("useTexture", 1);
        material->SetProperty("isTransparent", 1);
    }
    else {
        std::cerr << "UIComponent: Failed to load texture: " << textureName << std::endl;
    }
}

std::shared_ptr<Mesh> UIComponent::ParseMesh(const rapidjson::Value& json) const
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

std::shared_ptr<Mesh> UIComponent::CreateMesh()
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
