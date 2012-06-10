#include <iostream>

#include <glf.hpp>
#include <gli/gli.hpp>
#include <gli/gtx/gl_texture2d.hpp>




//GLuint textureID(0);
GLuint texFloorID(0);

std::vector<glm::vec4> objVertices;
std::vector<glm::vec4> objNormals;
std::vector<glm::vec2> objTexCoord;
//std::vector<GLushort>  objIndices;

//std::string objName = glf::MESH_DIRECTORY + "Imrod_LowPoly/ImrodLowPoly2.obj";
//std::string objName = glf::MESH_DIRECTORY + "Imrod_LowPoly/untitled2.obj";

std::string const NAME = "OpenGL Varying structs";	
 
std::string const AMBIENT_VERTEX_SHADER(glf::SHADER_DIRECTORY + "ambient.vert");
std::string const AMBIENT_FRAGMENT_SHADER(glf::SHADER_DIRECTORY + "ambient.frag");
std::string const STENCIL_VERTEX_SHADER(glf::SHADER_DIRECTORY + "stencil.vert");
std::string const STENCIL_GEOMETRY_SHADER(glf::SHADER_DIRECTORY + "stencil.geom");
std::string const STENCIL_FRAGMENT_SHADER(glf::SHADER_DIRECTORY + "stencil.frag");
std::string const FINAL_VERTEX_SHADER(glf::SHADER_DIRECTORY + "final.vert");
std::string const FINAL_GEOMETRY_SHADER(glf::SHADER_DIRECTORY + "final.geom");
std::string const FINAL_FRAGMENT_SHADER(glf::SHADER_DIRECTORY + "final.frag");


int const SIZE_WIDTH(640);
int const SIZE_HEIGHT(480);
int const MAJOR_VERSION(4);
int const MINOR_VERSION(1);

glf::Window window(glm::ivec2(SIZE_WIDTH, SIZE_HEIGHT));

GLuint shaderAmbient(0);
GLuint shaderStencil(0);
GLuint shaderFinal(0);
GLuint objArrayBufferID[3] = {0};
GLuint objVertexArrayID(0);
//GLuint objIndexBufferID(0);
GLint  uniformMVPa(0);
GLint  uniformMVPf(0);
GLint  uniformM(0);
GLint  uniformP(0);
GLint  uniformPf(0);
GLint  uniformMV(0);
GLint  uniformMIT(0);
GLint  uniformTexa(0);
GLint  uniformTexf(0);
GLint  uniformLightPoss(0);
GLint  uniformLightPosf(0);
GLint  uniformZPass(0);
GLint  uniformMVf(0);

int zPass = 0;


	GLuint ArrayBufferName(0);
	GLuint VertexArrayName(0);
	GLuint ArrayBufferName2(0);
	GLuint VertexArrayName2(0);
	GLuint VertexArrayName3(0);
	GLuint IndexBufferName2(0);
	GLuint IndexBufferName3(0);
	GLuint IndexBufferName(0);

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v4fv4fv2f);
	glf::vertex_v4fv4fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v4fv4fv2f (glm::vec4(-50.0f,-0.5f, -50.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
				       glm::vec2(0.0f, 0.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4( 50.0f,-0.5f, -50.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
				       glm::vec2(1.0f, 0.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4(-50.0f, -0.5f, 50.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
				       glm::vec2(0.0f, 1.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4( 50.0f, -0.5f, 50.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
				       glm::vec2(1.0f, 1.0f))
	};
	glf::vertex_v4fv4fv2f const VertexData2[2*VertexCount] =
	{
		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,10.5f, 5.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
				       glm::vec2(0.0f, 0.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,10.5f, 5.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
				       glm::vec2(1.0f, 0.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,5.5f, 5.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
				       glm::vec2(0.0f, 0.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,5.5f, 5.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
				       glm::vec2(1.0f, 0.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,10.5f, 10.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
				       glm::vec2(0.0f, 1.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,10.5f, 10.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
				       glm::vec2(1.0f, 1.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,5.5f, 10.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
				       glm::vec2(0.0f, 1.0f)),
		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,5.5f, 10.0f, 1.0f),
				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
				       glm::vec2(1.0f, 1.0f))

	};
//	glf::vertex_v4fv4fv2f const VertexData2[2*VertexCount] =
//	{
//		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,10.5f, 5.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
//				       glm::vec2(0.0f, 0.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,10.5f, 5.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
//				       glm::vec2(1.0f, 0.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,10.5f, 10.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
//				       glm::vec2(0.0f, 1.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,10.5f, 10.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
//				       glm::vec2(1.0f, 1.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,5.5f, 5.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
//				       glm::vec2(0.0f, 0.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,5.5f, 5.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
//				       glm::vec2(1.0f, 0.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4(-5.0f,5.5f, 10.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),  
//				       glm::vec2(0.0f, 1.0f)),
//		glf::vertex_v4fv4fv2f (glm::vec4( 5.0f,5.5f, 10.0f, 1.0f),
//				       glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), 
//				       glm::vec2(1.0f, 1.0f))
//	};
	
//	unsigned int indices[6] = {0, 1, 2, 1, 3, 2};
	unsigned int indices2[72] = {0, 4, 1, 3, 2, 6, 
				     1, 7, 3, 6, 2, 0, 
				     1, 4, 5, 7, 3, 2, 
				     5, 6, 7, 2, 3, 1, 
				     5, 1, 4, 0, 6, 7, 
				     5, 4, 6, 3, 7, 1, 
				     4, 1, 0, 2, 6, 5, 
				     0, 3, 2, 7, 6, 4, 
				     4, 5, 1, 3, 0, 2, 
				     4, 7, 5, 3, 1, 0, 
				     2, 0, 3, 7, 6, 4, 
				     3, 5, 7, 4, 6, 2};
				     
//	unsigned int indices2[72] = {0, 4, 1, 3, 2, 6, 
//				     1, 7, 3, 6, 2, 0, 
//				     1, 4, 5, 7, 3, 2, 
//				     5, 6, 7, 2, 3, 1, 
//				     5, 1, 4, 0, 6, 7, 
//				     5, 4, 6, 3, 7, 1, 
//				     4, 1, 0, 2, 6, 5, 
//				     0, 3, 2, 7, 6, 4, 
//				     4, 5, 1, 3, 0, 2, 
//				     4, 7, 5, 3, 1, 0, 
//				     2, 0, 3, 7, 6, 4, 
//				     3, 5, 7, 4, 6, 2};
	
	unsigned int indices3[36] = {0, 1, 2, 
				     1, 3, 2, 
				     1, 5, 3, 
				     5, 7, 3, 
				     0, 4, 1, 
				     4, 5, 1, 
				     6, 2, 3, 
				     6, 3, 7, 
				     5, 6, 7, 
				     5, 4, 6, 
				     4, 0, 6, 
				     0, 2, 6};


bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool initProgram()
{
	bool validated = true;

//	if (textureID < 0)
//	{
//		printf("error while loading texture:%d", textureID);
//		exit(0);
//	}
	// Create program
	if(validated)
	{
		// AMBIENT SHADER
		printf("creating ambient shader...\n");
		GLuint vertexShader = glf::createShader(GL_VERTEX_SHADER, AMBIENT_VERTEX_SHADER);
		GLuint fragmentShader = glf::createShader(GL_FRAGMENT_SHADER, AMBIENT_FRAGMENT_SHADER);

		shaderAmbient = glCreateProgram();
		glAttachShader(shaderAmbient, vertexShader);
		glAttachShader(shaderAmbient, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glLinkProgram(shaderAmbient);


		// STENCIL SHADER
		printf("creating stencil shader...\n");
		vertexShader = glf::createShader(GL_VERTEX_SHADER, STENCIL_VERTEX_SHADER);
		GLuint geometryShader = glf::createShader(GL_GEOMETRY_SHADER, STENCIL_GEOMETRY_SHADER);
		fragmentShader = glf::createShader(GL_FRAGMENT_SHADER, STENCIL_FRAGMENT_SHADER);

		shaderStencil = glCreateProgram();
		glAttachShader(shaderStencil, vertexShader);
		glAttachShader(shaderStencil, geometryShader);
		glAttachShader(shaderStencil, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
		glLinkProgram(shaderStencil);


		// FINAL SHADER
		printf("creating final shader...\n");
		vertexShader = glf::createShader(GL_VERTEX_SHADER, FINAL_VERTEX_SHADER);
		fragmentShader = glf::createShader(GL_FRAGMENT_SHADER, FINAL_FRAGMENT_SHADER);
//		geometryShader = glf::createShader(GL_GEOMETRY_SHADER, FINAL_GEOMETRY_SHADER);

		shaderFinal = glCreateProgram();
		glAttachShader(shaderFinal, vertexShader);
//		glAttachShader(shaderFinal, geometryShader);
		glAttachShader(shaderFinal, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
//		glDeleteShader(geometryShader);
		glLinkProgram(shaderFinal);

	}

//	textureID = gli::createTexture2D(glf::MESH_DIRECTORY + "Imrod_LowPoly/Imrod_Diffuse.tga"); 
	texFloorID = gli::createTexture2D(glf::TEXTURE_DIRECTORY + "Skybox1/dn.tga"); 
	
	// Get variables locations
	if(validated)
	{
		// using layout, or maybe not
		uniformMVPa = glGetUniformLocation(shaderAmbient, "mvpMatrix");
		uniformMVPf = glGetUniformLocation(shaderFinal, "mvpMatrix");
		uniformM = glGetUniformLocation(shaderFinal, "modelMatrix");
		uniformP = glGetUniformLocation(shaderStencil, "projectionMatrix");
		uniformPf = glGetUniformLocation(shaderFinal, "projectionMatrix");
		uniformMV = glGetUniformLocation(shaderStencil, "modelViewMatrix");
		uniformMIT = glGetUniformLocation(shaderFinal, "modelMatrixIT");
//		uniformMVf = glGetUniformLocation(shaderFinal, "modelViewMatrix");
		// uniformTex(;
		// uniformLightPos(0);
		uniformTexa = glGetUniformLocation(shaderAmbient, "diffuseMap");
		uniformTexf = glGetUniformLocation(shaderFinal, "diffuseMap");
		
		uniformLightPoss = glGetUniformLocation(shaderStencil, "lightPos");
		uniformLightPosf = glGetUniformLocation(shaderFinal, "lightPos");
		
		uniformZPass = glGetUniformLocation(shaderStencil, "zPass");
	}

	return validated && glf::checkError("initProgram");
}

bool initvertexArray()
{
	// Build a vertex array object
	glGenVertexArrays(1, &objVertexArrayID);
 	glBindVertexArray(objVertexArrayID);
	{
		glBindBuffer(GL_ARRAY_BUFFER, objArrayBufferID[0]);
		  glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, 0, GLF_BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, objArrayBufferID[1]);
		  glVertexAttribPointer(glf::semantic::attr::NORMAL, 4, GL_FLOAT, GL_FALSE, 0, GLF_BUFFER_OFFSET(0));
		
		glBindBuffer(GL_ARRAY_BUFFER, objArrayBufferID[2]);
		  glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, GLF_BUFFER_OFFSET(0));
		

		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::NORMAL);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);

//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objIndexBufferID);
	}
	glBindVertexArray(0);

	glGenVertexArrays(1, &VertexArrayName);
	glBindVertexArray(VertexArrayName);
		glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::NORMAL, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec4)));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(2*sizeof(glm::vec4)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::NORMAL);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
		
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferName);
	glBindVertexArray(0);
	
	
	glGenVertexArrays(1, &VertexArrayName2);
	glBindVertexArray(VertexArrayName2);
		glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName2);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::NORMAL, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec4)));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(2*sizeof(glm::vec4)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::NORMAL);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferName2);
	glBindVertexArray(0);
	
	glGenVertexArrays(1, &VertexArrayName3);
	glBindVertexArray(VertexArrayName3);
		glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName2);
		glVertexAttribPointer(glf::semantic::attr::POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(0));
		glVertexAttribPointer(glf::semantic::attr::NORMAL, 4, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(sizeof(glm::vec4)));
		glVertexAttribPointer(glf::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v4fv4fv2f), GLF_BUFFER_OFFSET(2*sizeof(glm::vec4)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glEnableVertexAttribArray(glf::semantic::attr::POSITION);
		glEnableVertexAttribArray(glf::semantic::attr::NORMAL);
		glEnableVertexAttribArray(glf::semantic::attr::TEXCOORD);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferName3);
	glBindVertexArray(0);

	return glf::checkError("initvertexArray");
}

bool initarrayBuffer()
{
	// Generate a buffer object
	glGenBuffers(3, &objArrayBufferID[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, objArrayBufferID[0]);
	  glBufferData(GL_ARRAY_BUFFER, 4*objVertices.size() * sizeof(GLfloat), &objVertices[0], GL_STATIC_DRAW);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, objArrayBufferID[1]);
	  glBufferData(GL_ARRAY_BUFFER, 4*objNormals.size() * sizeof(GLfloat), &objNormals[0], GL_STATIC_DRAW);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, objArrayBufferID[2]);
	  glBufferData(GL_ARRAY_BUFFER, 4*objTexCoord.size() * sizeof(GLfloat), &objTexCoord[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	glGenBuffers(1, &objIndexBufferID);

//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objIndexBufferID);
//	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, objIndices.size() * sizeof(GLuint), &objIndices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ArrayBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName);
    glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &ArrayBufferName2);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferName2);
    glBufferData(GL_ARRAY_BUFFER, 2*VertexSize, VertexData2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


//	glGenBuffers(1, &IndexBufferName);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferName);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, &indices[0], GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &IndexBufferName2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferName2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*72, &indices2[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &IndexBufferName3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferName3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*36, &indices3[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	return glf::checkError("initarrayBuffer");
}

bool begin()
{
	bool validated = glf::checkGLVersion(MAJOR_VERSION, MINOR_VERSION);

	if(validated)
	{
		objVertices.reserve(25200);
		objNormals.reserve(25200);
		objTexCoord.reserve(25200);
//		objIndices.reserve(76000);
//		glf::loadObj (objName.c_str(), objVertices, objNormals, objTexCoord);
	}
	if(validated && glf::checkExtension("GL_ARB_debug_output"))
		validated = initDebugOutput();
	if(validated)
		validated = initProgram();
	if(validated)
		validated = initarrayBuffer();
	if(validated)
		validated = initvertexArray();
		
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//	glEnable( GL_BLEND );

// set OpenGL state
// enable depth and stencil test
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_STENCIL_TEST);
	
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_CLAMP);
	
	glDepthFunc(GL_LEQUAL);
//	glCullFace(GL_BACK);
//	glFrontFace(GL_CW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f)[0]);
	glClearDepth(1.0f);
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClearStencil(0);
	
	return validated && glf::checkError("begin");
}

bool end()
{
	glDeleteVertexArrays(1, &objVertexArrayID);
	glDeleteBuffers(1, objArrayBufferID);
	glDeleteProgram(shaderAmbient);
	glDeleteProgram(shaderStencil);
	glDeleteProgram(shaderFinal); 

	return glf::checkError("end");
}

void display()
{
	
 	glm::mat4 projectionMatrix = glm::perspective(45.0f, float(window.size.x / window.size.y), 0.1f, 10000.0f);
	glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), glm::vec3( window.translationCurrent.x, -window.translationCurrent.y, window.translationCurrent.z));
	glm::mat4 viewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -20.0f, -80.0f));
	glm::mat4 viewRotateX = glm::rotate(viewTranslate, window.rotationCurrent.y, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 viewMatrix = glm::rotate(viewRotateX, window.rotationCurrent.x, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 modelMatrix = glm::scale (glm::mat4(1.0f), glm::vec3(1.0f));
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	glm::mat4 MVP2 = projectionMatrix * viewMatrix * modelTranslate * modelMatrix;
	glm::mat4 modelMatrixIT = glm::inverse (glm::transpose(modelMatrix));
	glm::mat4 modelViewMatrix = viewMatrix * modelTranslate * modelMatrix;

	glm::vec4 lightPosa = modelViewMatrix * glm::vec4 (-25.0f, 100.0f, 40.0f, 1.0f);
	glm::vec4 lightPosb = modelMatrix * glm::vec4 (-5.0f, 100.0f, 100.0f, 1.0f);
	glViewport(0, 0, window.size.x, window.size.y);
	
	glm::vec3 lightPoss = glm::vec3( lightPosa.x, lightPosa.y, lightPosa.z);
	glm::vec3 lightPosf = glm::vec3( lightPosb.x, lightPosb.y, lightPosb.z);
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);



	// ambient draw (to fill depth buffer)
	glUseProgram(shaderAmbient);
	glUniformMatrix4fv (uniformMVPa, 1, GL_FALSE, &MVP[0][0]);
//	glBindVertexArray(objVertexArrayID);
	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glDrawArrays (GL_TRIANGLES, 0, objVertices.size());

	glBindTexture(GL_TEXTURE_2D, texFloorID);
	glBindVertexArray(VertexArrayName);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	

	glUniformMatrix4fv (uniformMVPa, 1, GL_FALSE, &MVP2[0][0]);	
	glBindVertexArray(VertexArrayName3);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	// stencil draw (to fill stencil buffer)
	if (zPass)
	{
		// incr for front facing triangles, decr for back facing triangles if depth test passes
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR_WRAP);
		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR_WRAP);
		// stencil test always passes
		glStencilFunc (GL_ALWAYS, 0, ~0);	
	}
	else
	{
		// decr for front facing triangles, incr for back facing triangles if depth test fails
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		// stencil test always passes
		glStencilFunc (GL_ALWAYS, 0, ~0);
	}


// clear stencil buffer and lock color and depth buffer
glClear(GL_STENCIL_BUFFER_BIT);
//glClear(GL_COLOR_BUFFER_BIT);
glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
glDepthMask(GL_FALSE);

	glUseProgram(shaderStencil);
	glUniformMatrix4fv (uniformMV, 1, GL_FALSE, &modelViewMatrix[0][0]);
	glUniformMatrix4fv (uniformP, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv (uniformLightPoss, 1, &lightPoss[0]);
	
	// zPass or zFail?
	glUniform1i(uniformZPass, zPass);

//	glBindVertexArray(objVertexArrayID);
//	glDrawArrays (GL_TRIANGLES_ADJACENCY, 0, objVertices.size());

	glBindTexture(GL_TEXTURE_2D, texFloorID);
	glBindVertexArray(VertexArrayName);
	glDrawArrays(GL_TRIANGLES_ADJACENCY, 0, 4);
	
	glBindVertexArray(VertexArrayName2);
	glDrawElements(GL_TRIANGLES_ADJACENCY, 72, GL_UNSIGNED_INT, 0);


// unlock depth and color buffer
glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
glDepthMask(GL_TRUE);

	// final draw (skip parts in shadow -> keep ambient color)
glClear(GL_DEPTH_BUFFER_BIT);

	// dont change stencil buffer values
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_KEEP);
	// stencil test only passes if value in stencil buffer == 0
	glStencilFunc (GL_EQUAL, 0, ~0);	

	
	
	glUseProgram(shaderFinal);
	glUniformMatrix4fv (uniformM, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv (uniformMIT, 1, GL_FALSE, &modelMatrixIT[0][0]);
	glUniformMatrix4fv (uniformMVPf, 1, GL_FALSE, &MVP[0][0]);
//	glUniformMatrix4fv (uniformPf, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv (uniformLightPosf, 1, &lightPosf[0]);


glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(objVertexArrayID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glDrawArrays (GL_TRIANGLES, 0, objVertices.size());

	glBindTexture(GL_TEXTURE_2D, texFloorID);
	glBindVertexArray(VertexArrayName);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
//	glBindVertexArray(VertexArrayName2);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUniformMatrix4fv (uniformMVPf, 1, GL_FALSE, &MVP2[0][0]);
	glBindVertexArray(VertexArrayName3);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glf::checkError("display");
	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
	return glf::run (argc, 
	                 argv, 
	                 glm::ivec2(::SIZE_WIDTH, ::SIZE_HEIGHT), 
	                 GL_CONTEXT_CORE_PROFILE_BIT, 
	                 ::MAJOR_VERSION, 
	                 ::MINOR_VERSION);
}








