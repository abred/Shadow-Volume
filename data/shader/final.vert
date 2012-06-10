#version 410


//struct VertexToFragment
//{
//	vec3 worldPosition;
//	vec3 worldNormal;
//	vec2 tex;
//};

//
layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 3) in vec2 inTex;
//


//out VertexToFragment vtf;
out vec4 passPos;
out vec4 passNormal;
out vec2 passTex;


uniform mat4 modelMatrix;		
uniform mat4 modelMatrixIT; // inverse transposed	
uniform mat4 mvpMatrix;

void main()
{	
	passPos    = modelMatrix   * inPosition;
	passNormal = modelMatrixIT * inNormal;
	passTex    = inTex;

	gl_Position = mvpMatrix * inPosition;
}


//layout(location = 0) in vec4 inPosition;
//layout(location = 1) in vec4 inNormal;
//layout(location = 3) in vec2 inTex;
////


////out VertexToFragment vtf;
//out vec4 passPos1;
//out vec4 passNormal1;
//out vec2 passTex1;


//uniform mat4 modelMatrix;		
////uniform mat4 modelMatrixIT; // inverse transposed	
////uniform mat4 mvpMatrix;

//uniform mat4 modelViewMatrix; 

//void main()
//{	
//	passPos1    = inPosition;
////	passNormal = modelMatrixIT * inNormal;
//	passTex1    = inTex;

//	gl_Position = modelViewMatrix * inPosition;
//}






