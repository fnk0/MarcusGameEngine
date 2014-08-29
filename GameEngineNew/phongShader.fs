/*
 
 Phong shader
 
*/

#version 410 core

// Inputs from the vertex shader stage
layout (location = 0) smooth in vec4 vPosition;
layout (location = 0) smooth in vec4 vNormal;
layout (location = 0) smooth in vec2 vTexCo;
layout (location = 0) smooth in vec4 vColor;

// Output Fragment color
out vec4 fColor;

// Transform Matrices
uniform mat4 uObjectPerspectM;
uniform mat4 uObjectWorldM;
uniform mat4 uObjectWorldInverseM;

// Light properties
uniform vec4 uLightDirection = normalize(vec4(1.0, 1.0, 1.0, 0.0));
uniform vec4 uLightColor = vec4(1.5, 1.5, 1.5, 1.0);
uniform vec4 uAmbientLight = vec4(0.2, 0.2, 0.2, 1.0);

// Surface properties (diffuse only)
uniform float uTextureScale = 1.0;
uniform vec4 uDiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D uDiffuseTex;

// Users perspective
uniform vec4 userViewDirection = normalize(vec4(0.0, 0.0, 1.0, 0.0));

uniform vec4 phong;

// hardcoded gloss color
uniform vec4 uGLossColor = vec4(0.0, 0.8, 0.0, 10.0);


// Main Shader cpde

void main() {
    // Get a normalize version of the surface normal
    vec4 N = normalize(vNormal);
    vec4 diffuseColor = uDiffuseColor;
    diffuseColor *= vColor;
    diffuseColor *= texture(uDiffuseTex, vTexCo * uTextureScale);
    
    float normalDotLight = max(0.0, dot(uLightDirection, N));
    
    fColor = diffuseColor * uLightColor * normalDotLight;
    
    // GLoss
    vec3 reflection = reflect(-userViewDirection.xyz, N.xyz);
    float reflectionDotLight = max(0.0, dot(reflection, uLightDirection.xyz));
    
    // Phow effect
    fColor += pow(reflectionDotLight, uGLossColor.a) * uGLossColor * uLightColor;
    fColor.w = 1.0;
                
    
}
