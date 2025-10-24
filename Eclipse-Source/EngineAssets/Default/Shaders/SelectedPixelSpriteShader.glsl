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
   if(outTexCoord.x >= 0.1 && outTexCoord.x <= 0.9)
      discard;

   frag_colour = vec4(1.0, 1.0, 1.0, 1.0);
}