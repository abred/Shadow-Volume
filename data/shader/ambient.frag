#version 410



in vec2 passTex;


out vec4 FragColor;


layout (location = 0) uniform sampler2D diffuseMap;



void main()
{
	float ambient = 0.3;
	vec3 test = ambient * texture(diffuseMap, passTex).xyz;
	FragColor = vec4(test, 1.0);
//	FragColor = ambient * texture (diffuseMap, passTex);
//	FragColor = vec4(passTex, 0.0, 1.0);
}
