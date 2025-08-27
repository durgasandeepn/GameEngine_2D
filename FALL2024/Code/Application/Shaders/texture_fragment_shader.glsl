#version 330 core
out vec4 FragColor;

in vec3 final_color;
in vec2 TexCoord;
uniform sampler2D Texture; // Texture sampler

void main() {
    FragColor = texture(Texture, TexCoord);
}