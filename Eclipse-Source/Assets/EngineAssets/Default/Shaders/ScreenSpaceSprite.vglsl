#version 460 core

struct Transform
{
   vec2 position;
   vec2 size;
   float rotation;
};

// Layout Ins
layout(location=0) in vec2 VertexPosition;
layout(location=1) in vec2 TexCoord;

// Outs
out vec2 outTexCoord;

uniform float resolutionRatio;
uniform Transform transform;

uniform vec2 canvasScaleRelationOneDiv;

void main()
{
   outTexCoord = TexCoord * 0.98 + vec2(0.01, 0);
   
   float totalRotation = transform.rotation;
   mat2 rotationMatrix = mat2(cos(totalRotation), -sin(totalRotation), 
                              sin(totalRotation), cos(totalRotation));

   vec2 scaledVertex = VertexPosition * transform.size * canvasScaleRelationOneDiv;
   vec2 rotatedVertex = scaledVertex * rotationMatrix;
   
   vec2 worldPosition = (transform.position * canvasScaleRelationOneDiv) + rotatedVertex;
   
   // Apply aspect ratio correction only for display
   //worldPosition.x *= resolutionRatio;
   
   gl_Position = vec4(worldPosition, 0.0, 1.0);
}