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

// Uniforms
uniform vec2 cameraPosition;
uniform float cameraRotation;
uniform vec2 cameraScale;
uniform float resolutionRatio;

uniform Transform transform;

uniform vec2 size;
uniform vec2 offset;

void main()
{
   outTexCoord = vec2(TexCoord.x, 1 - TexCoord.y);
   
   float totalRotation = transform.rotation + cameraRotation;
   mat2 rotationMatrix = mat2(cos(totalRotation), -sin(totalRotation), 
                              sin(totalRotation), cos(totalRotation));

   vec2 scaledVertex = VertexPosition * (transform.size * 0.01) * size;
   vec2 rotatedVertex = scaledVertex * rotationMatrix;
   
   vec2 worldPosition = (transform.position + offset) + rotatedVertex;
   vec2 cameraRelative = worldPosition - cameraPosition;
   
   mat2 camRot = mat2(cos(cameraRotation), -sin(cameraRotation),
                      sin(cameraRotation), cos(cameraRotation));
   vec2 logicalPosition = cameraRelative * camRot;
   
   logicalPosition *= cameraScale;
   
   // Apply aspect ratio correction only for display
   logicalPosition.x *= resolutionRatio;
   
   gl_Position = vec4(logicalPosition, 0.0, 1.0);
}