#version 460 core

struct Material 
{
   sampler2D albedo;
   vec4 color;
   vec4 spriteRect; // x, y, width, height
};

// Uniforms
uniform Material material;

// Ins
in vec2 outTexCoord;

// Outs
out vec4 frag_colour;

void main() 
{
   vec2 modifiedUV = vec2(
      material.spriteRect.x + outTexCoord.x * material.spriteRect.z,
      material.spriteRect.y + outTexCoord.y * material.spriteRect.w - 0.01f
   );

   vec4 textureAlbedo = texture(material.albedo, modifiedUV);
   vec4 colorAlbedo = textureAlbedo * material.color;

   frag_colour = colorAlbedo;
}