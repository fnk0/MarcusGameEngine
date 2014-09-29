
#version 410 core

//---------------------------------------------------------------------------
// Stuff that should not have to change between vertex shaders
//---------------------------------------------------------------------------

// INPUTS FROM VERTEX SHADER STAGE
layout (location = 0) smooth in vec4 vPosition;
layout (location = 0) smooth in vec4 vNormal;
layout (location = 0) smooth in vec2 vTexCo;
layout (location = 0) smooth in vec4 vColor;

// OUTPUT FRAGMENT COLOR
out vec4 fColor;

//---------------------------------------------------------------------------
// Global inputs (uniforms)
//---------------------------------------------------------------------------

// TRANSFORM MATRICES
uniform mat4 uObjectPerpsectM;      // object-world-view-perspect transform
uniform mat4 uObjectWorldM;         // object-world transform
uniform mat4 uObjectWorldInverseM;  // inverse object-world transform

// LIGHT PROPERTIES
// uLightDirection and lightColor combined references a single directional light source
//uniform vec4 uLightDirection = normalize(vec4(1.0, 1.0, 1.0, 0.0));
//uniform vec4 uLightColor = vec4(1.5, 1.5, 1.5, 1.0); // Intensity!

// STRUCT = BAG FOR DATA
// NO METHODS AND EVERYTHING IS PUBLIC
struct Light {
    
    vec4 uLightType;
    vec4 uLightDirection;
    vec4 uLightColor;
    vec4 uLightPosition;
    
};
/*
uniform Light[2] lights = Light[] (
                    Light(vec4(0, 0, 0, 0),
                            normalize(vec4(0, 1, 0, 0)),
                            vec4(2, 0, 0, 1),
                            vec4(-5, 5, 5, 1)),
                   Light(vec4(0, 0, 0, 0),
                         normalize(vec4(1, 0, 0, 0)),
                         vec4(0, 0, 2, 1),
                         vec4(-5, 5, 5, 1)));
 
 */

uniform Light[2] lights;
uniform vec4 lightTest;

uniform vec4 uAmbientLight = vec4(0.2, 0.2, 0.2, 1.0);

uniform vec4 uViewDirection = vec4(0, 0, 1, 0);

// A point light source will need a color, direction and position
// 3 or 4 vec4
// Directional light is infinite far away and shines with the uLight color intensity
// Point color says that there;s a light with a certain position in space with a certain intensity
// Also there's a follow up function
// Divides by the square root distance of a lightSource + 1

// SURFACE PROPERTIES (diffuse only)
uniform float uTextureScale = 1.0;
uniform vec4 uDiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D uDiffuseTex; // diffuse texture (can modulate the color over the surface)
// TODO add another uniform shader 2d
uniform sampler2D uSpecularTexture;

// specular color = Intensity * ks * dot(R, LightDirection)^n

//---------------------------------------------------------------------------
// Main shader code
//---------------------------------------------------------------------------

void main()
{
    
    // START WITH BLACK
    fColor = vec4(0,0,0,1);
    
	// get a normalized version of the surface normal
	vec4 N = normalize(vNormal);
    
	// compute the diffuse color (uniformDiffuseColor * vertexColor * textureColor)
	vec4 diffuseColor = uDiffuseColor;
	diffuseColor *= vColor;
	diffuseColor *= texture(uDiffuseTex, vTexCo*uTextureScale); // That gives the diffuse color for the shader
    diffuseColor *= texture(uSpecularTexture, vTexCo*uTextureScale);
    
    for(int i =0; i < 2; i++) {
        
        if(lights[i].uLightColor == vec4(0, 0, 0, 0)) {
            continue;
        }
        
        vec4 R = reflect(uViewDirection, N);
        //vec4 specularColor = uLightColor * texture(uSpecularTexture, vTexCo*uTextureScale) * pow(dot(R, uLightDirection), 10);
        vec4 specularColor = lights[i].uLightColor * texture(uSpecularTexture, vTexCo*uTextureScale) * pow(dot(R, lights[i].uLightDirection), 10);
        
        // DIFFUSE TERM
        float NdotL = max(0.0, dot(lights[i].uLightDirection, N)); // the dot product computes the cos
        fColor += diffuseColor * NdotL * lights[i].uLightColor;
    }
    
    // AMBIENT
    fColor += uAmbientLight * diffuseColor;
    //fColor += specularColor;
    
    // To change the diffuse color needs to pass the value through the c++ code
    // To compute reflect there's a reflection function in glsl
    // something like.... vec3 R = reflect(uViewDirection, Normal)

	// SET W VALUE TO 1
	fColor.w = 1.0;
}
