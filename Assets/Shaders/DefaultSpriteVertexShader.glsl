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

uniform vec2 resolutionMultiplier;
uniform float resolutionRatio;
uniform Transform transform;
uniform vec2 mirrored;

void main()
{
   outTexCoord = TexCoord * 0.98 + vec2(0.01, 0);
   
   float totalRotation = transform.rotation + cameraRotation;

   mat2 rotationMatrix = mat2(cos(totalRotation), -sin(totalRotation), sin(totalRotation), cos(totalRotation));

   mat2 cameraRotationMat = mat2(cos(cameraRotation), -sin(cameraRotation), sin(cameraRotation), cos(cameraRotation));

   vec2 scaledVertex = VertexPosition * (transform.size * 0.01 * mirrored);
   
   
   vec2 rotatedVertex = scaledVertex * rotationMatrix * vec2(resolutionRatio, 1.0);
   
   vec2 position = (transform.position * cameraRotationMat - cameraPosition) * vec2(resolutionRatio, 1.0);
   
   vec2 positionNDC = rotatedVertex + position;
   

   gl_Position=vec4(positionNDC * cameraScale, 0, 1.0);
}