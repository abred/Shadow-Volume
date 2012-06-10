#version 410



//
layout(location = 0) in vec4 inPosition;
//layout(location = 1) in vec4 inNormal;
layout(location = 3) in vec2 inTex;
//



//out vec4 passPos;
//out vec4 passNormal;
out vec2 passTex;

	
uniform mat4 mvpMatrix;

void main()
{	
	passTex    = inTex;

	gl_Position = mvpMatrix * inPosition;
}
