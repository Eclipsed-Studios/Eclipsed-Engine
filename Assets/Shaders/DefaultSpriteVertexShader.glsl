#version 460 core

struct Transform 
{
   vec2 position;
   float rotation;
};

// Layout Ins
layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 TexCoord;

// Outs
out vec2 outTexCoord;

// Uniforms
uniform Transform transform;

void main()
{
   outTexCoord = TexCoord;

   mat2 rotationMatrix = mat2(cos(transform.rotation), -sin(transform.rotation), sin(transform.rotation), cos(transform.rotation));

   vec2 position_WS = VertexPosition * rotationMatrix;
   vec2 position_WSScale = position_WS * vec2(0.5625, 1);
   
   vec2 positionNDC = position_WSScale + transform.position;

   gl_Position = vec4(positionNDC, 0, 1.0 );
}