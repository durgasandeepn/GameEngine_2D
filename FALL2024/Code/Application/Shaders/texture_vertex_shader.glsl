#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 offset;

out vec2 TexCoord;

void main() {
    TexCoord = vec2(vTexCoord.x + offset.x, vTexCoord.y + offset.y);
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPos, 1.0);
}