#version 460 core

uniform sampler2D TextTexture;

uniform vec4 color;

// Ins
in vec2 outTexCoord;

// Outs
out vec4 frag_colour;

void main() 
{
   float textureAlbedoR = texture(TextTexture, outTexCoord).r;

   frag_colour = vec4(color.r, color.g, color.b, textureAlbedoR * color.a);
}