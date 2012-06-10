#version 410



in vec4 passPos;
in vec4 passNormal;
in vec2 passTex;


out vec4 FragColor;

layout (location = 0) uniform sampler2D diffuseMap;


uniform vec3 lightPos;

//uniform float g_worldEyePositon;

void main()
{
	// ambient light
	vec3 ambientMaterialColor = texture(diffuseMap, passTex).xyz;
	float ambient = 0.3;
	vec3 ambientLightIntensity = ambient * ambientMaterialColor;

	// diffuse light
//	vec3 lightDirection = vec3(0.3, -1, -0.2);
//	vec3 lightPos = vec3 (-5, 30, 0.0);
	vec3 lightDirection = lightPos - passPos.xyz;
	vec3 light = normalize(lightDirection); // points into directon of light
	
	float diffuse = max(0, dot( normalize(passNormal.xyz), light));
	vec3 diffuseMaterialColor = texture(diffuseMap, passTex).xyz;//vec3(0.7, 0.7, 0.7);
	//vec3 diffuseMaterialColor = vec3(0.7, 0.7, 0.7);
	vec3 diffuseLightIntensity = diffuse * diffuseMaterialColor;

	// specular
	//vec3 eye = normalize( g_worldEyePositon - vtf.worldPosition);
    //vec3 vhalf = normalize(light + eye);
	//float specular = max(0, dot(normal, vhalf));
	//float Shininess = 32.0;//g_Shininess.x;
	//specular = pow(specular, Shininess);
	//vec3 diffuseLightIntensity = specular*materialSpecularColor

	// final
	vec3 finalColor = diffuseLightIntensity;   

	FragColor = vec4(finalColor.xyz, 1.0f);
	//FragColor = vec4(texture(diffuseMap, passTex).xyz, 1.0f);
	//FragColor = vec4(passNormal.xyz, 1.0f);
	//FragColor = vec4(passTex, 1.0f, 1.0f);
}
