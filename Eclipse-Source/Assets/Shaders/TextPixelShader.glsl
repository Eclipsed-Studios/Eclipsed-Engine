#version 460 core

uniform sampler2D TextTexture;

// Ins
in vec2 outTexCoord;

// Outs
out vec4 frag_colour;

void main() 
{
   vec4 textureAlbedo = texture(TextTexture, outTexCoord);

   frag_colour = vec4(textureAlbedo.r, textureAlbedo.r, textureAlbedo.r, textureAlbedo.r);
}