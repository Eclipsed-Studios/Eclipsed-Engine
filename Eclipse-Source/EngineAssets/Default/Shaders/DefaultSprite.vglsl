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
uniform vec2 spriteScaleMultiplier;

uniform vec2 cameraPosition;
uniform float cameraRotation;
uniform vec2 cameraScale;
uniform float resolutionRatio;
uniform Transform transform;
uniform vec2 mirrored;

void main()
{
   outTexCoord = TexCoord * 0.98 + vec2(0.01, 0);
   
   float totalRotation = transform.rotation + cameraRotation;
   mat2 rotationMatrix = mat2(cos(totalRotation), -sin(totalRotation), 
                              sin(totalRotation), cos(totalRotation));

   // ORIGINAL TRANSFORMATION (for collision compatibility)
   vec2 scaledVertex = VertexPosition * (transform.size * 0.01 * mirrored) * spriteScaleMultiplier;
   vec2 rotatedVertex = scaledVertex * rotationMatrix;
   
   vec2 worldPosition = transform.position + rotatedVertex;
   vec2 cameraRelative = worldPosition - cameraPosition;
   
   mat2 camRot = mat2(cos(cameraRotation), -sin(cameraRotation),
                      sin(cameraRotation), cos(cameraRotation));
   vec2 logicalPosition = cameraRelative * camRot;
   
   logicalPosition *= cameraScale;
   
   // Apply aspect ratio correction only for display
   logicalPosition.x *= resolutionRatio;
   
   gl_Position = vec4(logicalPosition, 0.0, 1.0);
}