#ifndef GLF_WINDOW_INCLUDED
#define GLF_WINDOW_INCLUDED

//#pragma warning(disable : once)

// OpenGL
#ifdef WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	include <GL/glew.h>
#	include <GL/wglew.h>
//#	include <GL/glext.h>
#elif defined(linux) || defined(__linux)
#	include <GL/glew.h>
#	define GL_GLEXT_PROTOTYPES 1
#	include <GL/gl.h>
#	include <GL/glext.h>
#elif defined(__APPLE__)
#	include <OpenGL/gl.h>
#else
#	error "Unsupported platform"
#endif

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


// GLF libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/half_float.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/raw_data.hpp>


//#include <gli/gli.hpp>
//#include <gli/gtx/loader.hpp>

// STL
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

namespace glf
{
#if defined(linux) || defined(__linux)
	std::string const SHADER_DIRECTORY("data/shader/");
	std::string const TEXTURE_DIRECTORY("data/textures/");
	std::string const MESH_DIRECTORY("data/meshes/");
#else
	std::string const SHADER_DIRECTORY("data/shader/");
	std::string const TEXTURE_DIRECTORY("data/textures/");
	std::string const MESH_DIRECTORY("data/meshes/");
#endif

	enum mouse_button
	{
		MOUSE_BUTTON_NONE = 0,
		MOUSE_BUTTON_LEFT = (1 << 0),
		MOUSE_BUTTON_RIGHT = (1 << 1),
		MOUSE_BUTTON_MIDDLE = (1 << 2)
	};

	struct Window
	{
		Window(glm::ivec2 const & size) :
			size(size),
			mouseOrigin(size >> 1),
			mouseCurrent(size >> 1),
			translationOrigin(0, 0, 0),
			translationCurrent(0, 0, 0),
			rotationOrigin(0,0,0), 
			rotationCurrent(0,0,0),
			mouseButtonFlags(0)
		{}

		glm::ivec2 size;
		glm::vec2 mouseOrigin;
		glm::vec2 mouseCurrent;
		glm::vec3 translationOrigin;
		glm::vec3 translationCurrent;
		glm::vec3 rotationOrigin;
		glm::vec3 rotationCurrent;
		int mouseButtonFlags;
	};

	std::string loadFile(std::string const & Filename);
	void loadObj (const char* filename, 
		      std::vector<glm::vec4> &vertices, 
		      std::vector<glm::vec4> &normals,
		      std::vector<glm::vec2> &texcoor);
	bool checkError(const char* Title);
	bool checkProgram(GLuint ProgramName);
	bool checkShader(GLuint ShaderName, char const* Source);
	bool validateProgram(GLuint ProgramName);

	int version(int Major, int Minor);
	int run();
	int run	(int argc, 
	         char* argv[], 
	         glm::ivec2 const & Size, 
	         int Profile, 
	         int Major, 
	         int Minor);

	void swapBuffers();
	int version(int Major, int Minor);
	bool checkGLVersion(GLint MajorVersionRequire, GLint MinorVersionRequire);
	bool checkExtension(char const * String);
	void init();
	bool saveBinary	(std::string const & Filename, 
	                 GLenum const & Format, 
	                 std::vector<glm::byte> const & Data, 
	                 GLint const & Size);
	bool loadBinary (std::string const & Filename, 
	                 GLenum & Format,
	                 std::vector<glm::byte> & Data,
	                 GLint & Size);
	std::string loadFile(std::string const & Filename);
	bool checkError(const char* Title);
	bool checkFramebuffer(GLuint FramebufferName);
	bool validateProgram(GLuint ProgramName);
	bool checkProgram(GLuint ProgramName);
	bool checkShader(GLuint ShaderName, const char* Source);
	GLuint createShader (GLenum Type, 
	                     std::string const & Source);
	void GLAPIENTRY debugOutput (GLenum source, 
	                                    GLenum type, 
	                                    GLuint id, 
	                                    GLenum severity, 
	                                    GLsizei length, 
	                                    const GLchar* message, 
	                                    GLvoid* userParam);
//	void checkDebugOutput()
	void keyboard(int key, int x, int y);
	void mouse(int Button, int State, int x, int y);
	void reshape(int w, int h);
	void idle();
	void close();
	void motion(int x, int y);
	void displayProxy();

	namespace semantic
	{
		namespace uniform
		{
			enum type
			{
				MATERIAL  = 0,
				TRANSFORM0 = 1,
				TRANSFORM1 = 2
			};
		};

		namespace image
		{
			enum type
			{
				DIFFUSE = 0
			};
		}//namesapce image

		namespace attr
		{
			enum type
			{
				POSITION = 0,
				NORMAL   = 1,
				COLOR    = 2,
				TEXCOORD = 3
			};
		}//namespace attr

		namespace vert
		{
			enum type
			{
				POSITION = 0,
				COLOR    = 3,
				TEXCOORD = 4,
				INSTANCE = 7
			};
		}//namespace vert

		namespace frag
		{
			enum type
			{
				COLOR  = 0,
				RED    = 0,
				GREEN  = 1,
				BLUE   = 2,
				ALPHA  = 0
			};
		}//namespace frag

		namespace renderbuffer
		{
			enum type
			{
				DEPTH,
				COLOR0
			};
		}//namespace renderbuffer

	}//namespace semantic

	struct vertex_v2fv2f
	{
		vertex_v2fv2f (glm::vec2 const & Position, 
		               glm::vec2 const & Texcoord) :
			Position(Position),
			Texcoord(Texcoord)
		{}

		glm::vec2 Position;
		glm::vec2 Texcoord;
	};

	struct vertex_v4fv2f
	{
		vertex_v4fv2f (glm::vec4 const & Position, 
		               glm::vec2 const & Texcoord) :
			Position(Position),
			Texcoord(Texcoord)
		{}

		glm::vec4 Position;
		glm::vec2 Texcoord;
	};
	
	struct vertex_v2fc4f
	{
		vertex_v2fc4f (glm::vec2 const & Position, 
		               glm::vec4 const & Color) :
			Position(Position),
			Color(Color)
		{}

		glm::vec2 Position;
		glm::vec4 Color;
	};

	struct vertex_v4fv4fv2f
	{
		vertex_v4fv4fv2f (glm::vec4 const & Position, 
				  glm::vec4 const & Normal, glm::vec2 const& Tex):
			Position(Position),
			Normal(Normal),
			TexCoord(Tex)
		{}

		glm::vec4 Position;
		glm::vec4 Normal;
		glm::vec2 TexCoord;
	};

	struct vertex_v4fc4f
	{
		vertex_v4fc4f (glm::vec4 const & Position, 
		               glm::vec4 const & Color) :
			Position(Position),
			Color(Color)
		{}

		glm::vec4 Position;
		glm::vec4 Color;
	};

	struct vertex_v2fc4ub
	{
		vertex_v2fc4ub (glm::vec2 const & Position, 
		                glm::u8vec4 const & Color) :
			Position(Position),
			Color(Color)
		{}

		glm::vec2 Position;
		glm::u8vec4 Color;
	};

	struct vertex_v2fv2fv4ub
	{
		vertex_v2fv2fv4ub (glm::vec2 const & Position, 
		                   glm::vec2 const & Texcoord, 
		                   glm::u8vec4 const & Color) :
			Position(Position),
			Texcoord(Texcoord),
			Color(Color)
		{}

		glm::vec2 Position;
		glm::vec2 Texcoord;
		glm::u8vec4 Color;
	};

}//namespace glf

//namespace 
//{
	extern glf::Window window;
//}//namespace 

#define GLF_BUFFER_OFFSET(i) ((char *)NULL + (i))
#ifndef GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD
#define GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD 0x9160
#endif



#endif//GLF_WINDOW_INCLUDED
