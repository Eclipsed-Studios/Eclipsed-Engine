#version 460 core

struct Material 
{
   sampler2D albedo;
   vec4 color;
   vec4 spriteRect; // x, y, width, height
};

// Uniforms
uniform Material material;

uniform int notOverrideColor;
uniform vec4 pixelPickColor;

// Ins
in vec2 outTexCoord;

// Outs
out vec4 frag_colour;

void main() 
{
   vec2 modifiedUV = vec2(
      material.spriteRect.x + outTexCoord.x * material.spriteRect.z,
      material.spriteRect.y + outTexCoord.y * material.spriteRect.w
   );

   vec4 textureAlbedo = texture(material.albedo, modifiedUV);
   vec4 colorAlbedo = textureAlbedo * material.color;

   float Override = float(notOverrideColor);
   float notOverride = float(!bool(notOverrideColor));

   vec4 colorOverride = colorAlbedo * Override;
   colorOverride += pixelPickColor * notOverride;

   frag_colour = vec4(colorOverride.r, colorOverride.g, colorOverride.b, textureAlbedo.a);
}