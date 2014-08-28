
#version 410 core

layout (location = 0) smooth in vec4 vPosition;
layout (location = 1) smooth in vec4 vNormal;
layout (location = 2) smooth in vec2 vTexCo;
layout (location = 3) smooth in vec4 vColor;

layout (location = 0) out vec4 fColor;

uniform vec4 uLightDirection = normalize(vec4(1.0, 1.0, 1.5, 0.0));
uniform vec4 uLightColor = vec4(1, 1, 1, 1.0);

uniform vec4 uViewDirection = normalize(vec4(0.0, 1.0, 1.0, 0.0));
uniform vec4 uHeadLightColor = vec4(0.2, 0.1, 0.1, 1.0);
uniform vec4 uRimLightColor = vec4(0.7, 0.7, 1.0, 3.0);

uniform vec4 uAmbientLight = vec4(1.0, 1.0, 1.0, 1.0);

uniform vec4 uDiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec4 uGlossColor = vec4(0.8, 0.25, 0.0, 3.0);
uniform vec4 uSpecularColor = vec4(0.2, 0.2, 0.2, 0.9);

uniform sampler2D uDiffuseTex;

void main()
{
	vec4 N = normalize(vNormal + texture(uDiffuseTex, vTexCo)*0.05);
    //vec4 N = normalize(vNormal);
	vec4 diffuseColor = uDiffuseColor;
	if (dot(vColor.rgb, vColor.rgb) > 0.0) diffuseColor *= vColor;
	diffuseColor *= texture(uDiffuseTex, vTexCo);
	vec4 specColor = 1-texture(uDiffuseTex, vTexCo);
	//specColor *= specColor;

	fColor = vec4(0,0,0,1);
	
	// NORMAL (debug)
	//fColor += 0.5 * (vec4(1,1,1,1) + N.xyzw);

	// AMBIENT TERM
	//fColor += diffuseColor * uAmbientLight;
	
	// HEAD LIGHT
	float NdotV = max(0.0, dot(uViewDirection, N));
	fColor += NdotV * diffuseColor * uHeadLightColor;

	// DIFFUSE TERM 
	float NdotL = max(0.0, dot(uLightDirection, N));
	fColor += diffuseColor * NdotL * uLightColor;

	// SPECULAR AND GLOSS TERMS
	vec3 R = reflect(-uViewDirection.xyz, N.xyz);
	float RdotL = max(0.0, dot(R, uLightDirection.xyz));
	//
	// Gloss (phong lobe)
	fColor += pow(RdotL, uGlossColor.a) * uGlossColor * uLightColor * specColor;
	//
	// sharp reflection (specular)
	float tval = uSpecularColor.a;
	fColor += smoothstep(tval, tval + 0.02, RdotL) * uSpecularColor * uLightColor * specColor;
	
	// RIM LIGHT
	float rimPower = pow(1-NdotV, uRimLightColor.a);
	fColor += rimPower * uRimLightColor;

	// SET W TERM
	fColor.w = 1.0;
}