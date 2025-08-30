#version 460 core

struct Material 
{
   sampler2D albedo;
   vec4 color;
};

// Uniforms
uniform Material material;

// Ins
in vec2 outTexCoord;

// Outs
out vec4 frag_colour;

void main() 
{
   vec4 textureAlbedo = texture(material.albedo, outTexCoord);
   vec4 colorAlbedo = textureAlbedo * material.color;

   //frag_colour = colorAlbedo;
   frag_colour = vec4(1, 1, 0, 1);
}