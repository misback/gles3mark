
#pragma once

#include <string>
#include <glm/glm.hpp>

#include "texture.h"

// http://docs.unity3d.com/Documentation/ScriptReference/Material.html
// http://assimp.sourceforge.net/lib_html/materials.html
class Material {
public:
    glm::vec4 diffuseColor;
    glm::vec4 ambientColor;
    glm::vec4 specularColor;
    glm::vec4 emissiveColor;
    // glm::vec4 reflectColor
    float shininess; // specularExponent: describes the shininess of the material and is used to control the shininess of the specular highlight

    // Shader program? http://docs.unity3d.com/Documentation/ScriptReference/Shader.html
    // Textures? texture database + index? map<path,Texture> ?
    bool hasTexture;
    Texture *texture;      // The material's texture. - main, normal, ..., another material can have same texture - TextureDatabase - index: path?
    //ShaderProgram *shader; //The shader used by the material. - only one,            - || -             shader  - ShaderDatabase  - index: -||-?

    unsigned id;

public:
    Material(const glm::vec4& diffuse, const glm::vec4& ambient, const glm::vec4& specular,
             const glm::vec4& emissive, float shininess, const std::string& texturePath = std::string()) :
             diffuseColor(diffuse), ambientColor(ambient), specularColor(specular),
             emissiveColor(emissive), shininess(shininess), texture(nullptr)
    {
        hasTexture = !texturePath.empty();

        if (hasTexture) {
            texture = new Texture(texturePath);
        }
    }


};