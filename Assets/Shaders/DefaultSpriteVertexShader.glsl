#version 460 core

struct Transform
{
   vec2 position;
   vec2 pixelSize;
   float rotation;
};

// Layout Ins
layout(location=0)in vec2 VertexPosition;
layout(location=1)in vec2 TexCoord;

// Outs
out vec2 outTexCoord;

// Uniforms
uniform vec2 resolutionMultiplier;
uniform float resolutionRatio;
uniform Transform transform;

void main()
{
   outTexCoord=TexCoord;
   
   mat2 rotationMatrix=mat2(cos(transform.rotation),-sin(transform.rotation),sin(transform.rotation),cos(transform.rotation));
   
   vec2 position_WS = VertexPosition * rotationMatrix;
   vec2 position_WSPixelScale = position_WS * resolutionMultiplier;
   vec2 position_WSRealScale = position_WSPixelScale * transform.pixelSize;
   
   vec2 position = transform.position * resolutionMultiplier;
   
   vec2 positionNDC = position_WSRealScale+position;
   
   gl_Position=vec4(positionNDC,0,1.);
}