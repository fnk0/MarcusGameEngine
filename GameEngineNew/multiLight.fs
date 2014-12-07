
#version 410 core

//---------------------------------------------------------------------------
// Stuff that should not have to change between vertex shaders
//---------------------------------------------------------------------------

// LIGHT TYPES
#define NO_LIGHT 0
#define AMBIENT_LIGHT 1
#define DIRECTIONAL_LIGHT 2
#define POINT_LIGHT 3
#define SPOT_LIGHT 4
#define HEAD_LIGHT 5
#define RIM_LIGHT 6

// INPUTS FROM VERTEX SHADER STAGE
layout (location = 0) smooth in vec4 vPosition;
layout (location = 1) smooth in vec4 vNormal;
layout (location = 2) smooth in vec2 vTexCo;
layout (location = 3) smooth in vec4 vColor;

// OUTPUT FRAGMENT COLOR
out vec4 fColor;

//---------------------------------------------------------------------------
// Global inputs (uniforms)
//---------------------------------------------------------------------------

// TRANSFORM MATRICES
uniform mat4 uObjectPerpsectM;      // object-world-view-perspect transform
uniform mat4 uObjectWorldM;         // object-world transform
uniform mat4 uObjectWorldInverseM;  // inverse object-world transform

#define MAX_LIGHTS 10
struct Light
{
    // type is in attenuation.w
    vec4 position, direction, color, attenuation, coneAngles;
};

layout(std140) uniform Lights
{
    Light L[MAX_LIGHTS];
};

// SURFACE PROPERTIES (diffuse only)
uniform float uTextureScale = 1.0;
uniform vec4 uDiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D uDiffuseTex; // diffuse texture

uniform sampler2D uOtherTex;

//---------------------------------------------------------------------------
// Main shader code
//---------------------------------------------------------------------------

void main()
{
    // get a normalized version of the surface normal
    vec4 N = normalize(vNormal);
    
    // compute the diffuse color (uniformDiffuseColor * vertexColor * textureColor)
    vec4 diffuseColor = uDiffuseColor;
    diffuseColor *= vColor;
    
    if(uDiffuseTex != NULL) {
        
    }
    
    diffuseColor *= texture(uDiffuseTex, vTexCo*uTextureScale);
    diffuseColor *= texture(uOtherTex, vTexCo*uTextureScale);
    
    // START WITH BLACK
    fColor = vec4(0,0,0,1);
    
    //LOOP OVER LIGHTS
    for (int i=0; i<MAX_LIGHTS; i++)
    {
        float type = L[i].attenuation.w;
        if (type == NO_LIGHT) {
            break; // unknown light type
        }
        else if (type == AMBIENT_LIGHT) {
            fColor += diffuseColor * L[i].color;
        }
        else if (type == DIRECTIONAL_LIGHT) {
            float NdotL = max(0.0, dot(N, L[i].direction));
            fColor += diffuseColor * NdotL * L[i].color;
        }
        else if (type == POINT_LIGHT) {
            vec4 Li = vec4((L[i].position - vPosition).xyz, 0.0);
            float d = sqrt(dot(Li,Li));
            Li *= (1/d);
            vec4 attDist = vec4(d*d, d, 1, 0);
            float attenVal = min(1.0, 1.0/dot(attDist, L[i].attenuation));
            float NdotL = max(0.0, dot(N, Li));
            fColor += (NdotL * attenVal) * diffuseColor * L[i].color;
        }
        else if (type == SPOT_LIGHT) {
            vec4 Li = vec4((L[i].position - vPosition).xyz, 0.0);
            float d = sqrt(dot(Li,Li));
            Li *= (1/d);
            vec4 attDist = vec4(d*d, d, 1, 0);
            float attenVal = min(1.0, 1.0/dot(attDist, L[i].attenuation));
            float NdotL = max(0.0, dot(N, Li));
            
            float cosA = L[i].coneAngles[0];
            float cosB = L[i].coneAngles[1];
            float liDotDir = -(dot(Li, L[i].direction));
            if (liDotDir <= cosB) attenVal = 0.0;
            else if (liDotDir < cosA) attenVal *= (liDotDir - cosB) / (cosA - cosB);
            fColor += (NdotL * attenVal) * diffuseColor * L[i].color;
        }
    }
    
    // SET W VALUE TO 1
    fColor.w = 1.0;
}
