#version 410


layout(location = 0) in vec4 inPosition;
//layout(location = 1) in vec4 inNormal;


uniform mat4 modelViewMatrix;


//out vec4 passNormal;

void main()
{	
//	passNormal = modelViewMatrix * inNormal;
	gl_Position = modelViewMatrix * inPosition;
}
