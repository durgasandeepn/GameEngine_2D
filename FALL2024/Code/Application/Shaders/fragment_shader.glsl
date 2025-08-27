#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 final_color;

uniform bool useTexture;
uniform bool isTransparent;
uniform sampler2D Texture;
uniform vec3 special_color;
uniform float Opacity;

void main(){
	if (useTexture) {
		//FragColor = texture(Texture, TexCoord);
		    vec4 texColor = texture(Texture, TexCoord);
			FragColor = vec4(texColor.rgb + special_color, texColor.a * Opacity); 
	}
	else {
		if(isTransparent) {
			FragColor = vec4(final_color, 0.0f);
		}
		else {
			FragColor = vec4(final_color, 1.0f);
		}
	}
}