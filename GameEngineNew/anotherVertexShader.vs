
#version 410 core

//---------------------------------------------------------------------------
// Stuff that should not have to change between vertex shaders
//---------------------------------------------------------------------------

// INPUTS FROM VERTEX DATA
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCo;
layout (location = 3) in vec3 inColor;

// OUTPUTS TO FRAGMENT SHADER
layout (location = 0) smooth out vec4 vPosition; // World position
layout (location = 1) smooth out vec4 vNormal; // Normal vector
layout (location = 2) smooth out vec2 vTexCo; // texture coordinate
layout (location = 3) smooth out vec4 vColor; // Color of the vertex interpolated across the triangle face

// UNIFORMS (GLOBAL VARIABLES)
uniform mat4 uObjectPerpsectM;      // object-world-view-perspect transform
uniform mat4 uObjectWorldM;         // object-world transform
uniform mat4 uObjectWorldInverseM;  // inverse object-world transform

//---------------------------------------------------------------------------
// Main shader code
//---------------------------------------------------------------------------

void main()
{
	// COMPUTE POSITION OF VERTEX IN WINDOW AND SEND
	gl_Position = uObjectPerpsectM * vec4(inPosition, 1.5);
    
	// COMPUTE VALUES THAT WILL BE SENT TO NEXT STAGE
	vPosition = uObjectWorldM * vec4(inPosition, 1.5);
	vNormal = normalize(vec4(inNormal,0.0) * uObjectWorldInverseM);
	vTexCo = inTexCo;
	if (dot(inColor,inColor) == 0) vColor = vec4(1,1,1,0);
	else vColor = vec4(inColor, 1.0);
}
