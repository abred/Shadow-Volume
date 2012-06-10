#include "../include/glf.hpp"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif






bool check();
bool begin();
bool end();
void display();



namespace glf
{
	void swapBuffers()
	{
		glutSwapBuffers();
		glGetError(); // 'glutSwapBuffers' generates an here with OpenGL 3 > core profile ... :/
	}

	int version(int Major, int Minor)
	{
		return Major * 100 + Minor * 10;
	}

#if !defined(__APPLE__)
	bool checkGLVersion(GLint MajorVersionRequire, GLint MinorVersionRequire)
	{
		GLint MajorVersionContext = 0;
		GLint MinorVersionContext = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &MajorVersionContext);
		glGetIntegerv(GL_MINOR_VERSION, &MinorVersionContext);
		return glf::version(MajorVersionContext, MinorVersionContext) 
			>= glf::version(MajorVersionRequire, MinorVersionRequire);
	}

	bool checkExtension(char const * String)
	{
		GLint ExtensionCount = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &ExtensionCount);
		for(GLint i = 0; i < ExtensionCount; ++i)
			if(std::string((char const*)glGetStringi(GL_EXTENSIONS, i)) == std::string(String))
				return true;
		return false;
	}
#endif

	void init()
	{
#if (defined(WIN32))
//		glewInit();
//		glGetError();
		
		//glTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC)glutGetProcAddress("glTextureStorage2DEXT");
//		glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)glutGetProcAddress("glDebugMessageControlARB");
//		glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)glutGetProcAddress("glDebugMessageCallbackARB");
//		glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)glutGetProcAddress("glDebugMessageInsertARB");

		//assert(glTextureStorage2DEXT);
#endif
	}

	bool saveBinary	(std::string const & Filename, 
	                 GLenum const & Format, 
	                 std::vector<glm::byte> const & Data, 
	                 GLint const & Size)
	{
		FILE* File = fopen(Filename.c_str(), "wb");

		if(File)
		{
			fwrite(&Format, sizeof(GLenum), 1, File);
			fwrite(&Size, sizeof(Size), 1, File);
			fwrite(&Data[0], Size, 1, File);
			fclose(File);
			return true;
		}
		return false;
	}

	bool loadBinary (std::string const & Filename, 
	                 GLenum & Format,
	                 std::vector<glm::byte> & Data,
	                 GLint & Size)
	{
		FILE* File = fopen(Filename.c_str(), "rb");

		if(File)
		{
			fread(&Format, sizeof(GLenum), 1, File);
			fread(&Size, sizeof(Size), 1, File);
			Data.resize(Size);
			fread(&Data[0], Size, 1, File);
			fclose(File);
			return true;
		}
		return false;
	}

	std::string loadFile(std::string const & Filename)
	{
		std::ifstream stream(Filename.c_str(), std::ios::in);

		if(!stream.is_open())
			return "";

		std::string Line = "";
		std::string Text = "";

		while(getline(stream, Line))
			Text += "\n" + Line;

		stream.close();

		return Text;
	}

	void loadObj (const char* filename, 
		      std::vector<glm::vec4> &vertices, 
		      std::vector<glm::vec4> &normals,
		      std::vector<glm::vec2> &texcoord)
	{
		std::ifstream in(filename, std::ios::in);
		if (!in)
		{
			std::cerr << "Cannot open " << filename << std::endl;
			exit(1); 
		}
		std::vector<glm::vec4> verticesTemp;
		verticesTemp.reserve(4400);
		std::vector<glm::vec4> normalsTemp;
		normalsTemp.reserve(4400);
		std::vector<glm::vec2> texcoordTemp;
		texcoordTemp.reserve(3400);
//		std::vector<GLushort> indicesTemp;
		
		std::string line;
		while (getline(in, line)) 
		{
			// Vertices
			if (line.substr(0,2) == "v ")
			{
				std::istringstream s(line.substr(2));
				glm::vec4 v; 
				s >> v.x; 
				s >> v.y; 
				s >> v.z;
				v.w = 1.0f;
				verticesTemp.push_back(v);
			} 
			// Indices
			else if (line.substr(0,2) == "f ")
			{
				/* ignoring this line now*/
			}
			// TexCoord
			else if (line.substr(0,3) == "vt ")
			{
				std::istringstream s(line.substr(3));
				glm::vec2 v;
				s >> v.x; 
				s >> v.y;
				texcoordTemp.push_back(v);
			}
			// Normals
			else if (line.substr(0,3) == "vn ")
			{
				std::istringstream s(line.substr(3));
				glm::vec4 v;
				s >> v.x; 
				s >> v.y; 
				s >> v.z;
				v.w = 0.0f;
				normalsTemp.push_back(v);
			}
			// Comment
			else if (line[0] == '#') 
			{
				/* ignoring this line */
			}
			else
			{
				/* ignoring this line */
			}
		}
		
		in.close();
		in.open(filename, std::ios::in);
		if (!in)
		{
			std::cerr << "Cannot open " << filename << std::endl;
			exit(1); 
		}
		
		int indices[3];
		while (getline(in, line)) 
		{
			if (line.substr(0,2) == "f ")
			{
				std::istringstream s(line.substr(2));
				
				std::string v[3];
				s >> v[0] >> v[1] >> v[2];
				
				for (unsigned int i = 0; i < 3; ++i)
				{
					std::string::iterator ib = v[i].begin();
					std::string::iterator ie = v[i].begin();
					unsigned int c = 0;
					while (ie != v[i].end())
					{
						if (*ie == '/')
						{
							std::stringstream ss(std::string(ib, ie));
							GLushort a;
							ss >> a;
						
							indices[c++] = --a;
							
							++ie;
							ib = ie;
						}
						
						++ie;
						
					}
					std::stringstream ss(std::string(ib, ie));
					GLushort a;
					ss >> a;
					indices[c] = --a;
					
					vertices.push_back (verticesTemp[indices[0]]);
					texcoord.push_back (texcoordTemp[indices[1]]);
					normals.push_back (normalsTemp[indices[2]]);
					
				}
			}
			else
			{
				/* ignoring this line */
			}
		}
		 
		// normals.resize(mesh->vertices.size(), glm::vec3(0.0, 0.0, 0.0));
		// for (int i = 0; i < indices.size(); i+=3) 
		// {
		// 	GLushort ia = elements[i];
		// 	GLushort ib = elements[i+1];
		// 	GLushort ic = elements[i+2];
		// 	glm::vec3 normal = glm::normalize(glm::cross(
		// 						  vertices[ib] - vertices[ia],
		// 						  vertices[ic] - vertices[ia]));
		// 	normals[ia] = normals[ib] = normals[ic] = normal;
		// }
	}

	bool checkError(const char* Title)
	{
		int Error;
		if((Error = glGetError()) != GL_NO_ERROR)
		{
			std::string ErrorString;
			switch(Error)
			{
			case GL_INVALID_ENUM:
				ErrorString = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				ErrorString = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				ErrorString = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				ErrorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			case GL_OUT_OF_MEMORY:
				ErrorString = "GL_OUT_OF_MEMORY";
				break;
			default:
				ErrorString = "UNKNOWN";
				break;
			}
			fprintf(stdout, "OpenGL Error(%s): %s\n", ErrorString.c_str(), Title);
		}
		return Error == GL_NO_ERROR;
	}

#if !defined(__APPLE__)
	bool checkFramebuffer(GLuint FramebufferName)
	{
		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch(Status)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_UNDEFINED");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_UNSUPPORTED");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			fprintf(stdout, "OpenGL Error(%s)\n", "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
			break;
		}

		return Status != GL_FRAMEBUFFER_COMPLETE;
	}
#endif

	bool validateProgram(GLuint ProgramName)
	{
		if(!ProgramName)
			return false;

		glValidateProgram(ProgramName);
		GLint Result = GL_FALSE;
		glGetProgramiv(ProgramName, GL_VALIDATE_STATUS, &Result);

		if(Result == GL_FALSE)
		{
			fprintf(stdout, "Validate program\n");
			int InfoLogLength;
			glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
			std::vector<char> Buffer(InfoLogLength);
			glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
			fprintf(stdout, "%s\n", &Buffer[0]);
		}

		return Result == GL_TRUE;
	}

	bool checkProgram(GLuint ProgramName)
	{
		if(!ProgramName)
			return false;

		GLint Result = GL_FALSE;
		glGetProgramiv(ProgramName, GL_LINK_STATUS, &Result);

		fprintf(stdout, "Linking program\n");
		int InfoLogLength;
		glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> Buffer(std::max(InfoLogLength, int(1)));
		glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
		fprintf(stdout, "%s\n", &Buffer[0]);

		return Result == GL_TRUE;
	}

	bool checkShader(GLuint ShaderName, const char* Source)
	{
		if(!ShaderName)
			return false;

		GLint Result = GL_FALSE;
		glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Result);

		fprintf(stdout, "Compiling shader...\n%s\n", Source);
		int InfoLogLength;
		glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> Buffer(InfoLogLength);
		glGetShaderInfoLog(ShaderName, InfoLogLength, NULL, &Buffer[0]);
		fprintf(stdout, "%s\n", &Buffer[0]);

		return Result == GL_TRUE;
	}

	GLuint createShader (GLenum type, 
	                     std::string const & source)
	{
		GLuint shaderID = 0;

		if(!source.empty())
		{
			std::string sourceContent = glf::loadFile(source);
			char const * sourcePointer = sourceContent.c_str();
			shaderID = glCreateShader(type);
			glShaderSource(shaderID, 1, &sourcePointer, NULL);
			glCompileShader(shaderID);
		}

		return shaderID;
	}


#if !defined(__APPLE__)
	void GLAPIENTRY debugOutput (GLenum source, 
	                                    GLenum type, 
	                                    GLuint id, 
	                                    GLenum severity, 
	                                    GLsizei length, 
	                                    const GLchar* message, 
	                                    GLvoid* userParam)
	{
		//FILE* f;
		//f = fopen("debug_output.txt","a");
		//if(f)
		{
			char debSource[32], debType[32], debSev[32];
			if(source == GL_DEBUG_SOURCE_API_ARB)
				strcpy(debSource, "OpenGL");
			else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
				strcpy(debSource, "Windows");
			else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
				strcpy(debSource, "Shader Compiler");
			else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
				strcpy(debSource, "Third Party");
			else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
				strcpy(debSource, "Application");
			else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
				strcpy(debSource, "Other");
 
			if(type == GL_DEBUG_TYPE_ERROR_ARB)
				strcpy(debType, "error");
			else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
				strcpy(debType, "deprecated behavior");
			else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
				strcpy(debType, "undefined behavior");
			else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
				strcpy(debType, "portability");
			else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
				strcpy(debType, "performance");
			else if(type == GL_DEBUG_TYPE_OTHER_ARB)
				strcpy(debType, "message");
 
			if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
				strcpy(debSev, "high");
			else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
				strcpy(debSev, "medium");
			else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
				strcpy(debSev, "low");

			 fprintf(stderr,"%s: %s(%s) %d: %s\n", debSource, debType, debSev, id, message);
			 //fclose(f);
		}
	}
/*
	void checkDebugOutput()
	{
		   unsigned int count = 10; // max. num. of messages that will be read from the log
		   int bufsize = 2048;
	 
		   unsigned int* sources      = new unsigned int[count];
		   unsigned int* types        = new unsigned int[count];
		   unsigned int* ids   = new unsigned int[count];
		   unsigned int* severities = new unsigned int[count];
		   int* lengths = new int[count];
	 
		   char* messageLog = new char[bufsize];
	 
		   unsigned int retVal = glGetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
		   if(retVal > 0)
		   {
				 unsigned int pos = 0;
				 for(unsigned int i=0; i<retVal; i++)
				 {
						debugOutput(sources[i], types[i], ids[i], severities[i], NULL, &messageLog[pos], NULL);
						pos += lengths[i];
				  }
		   }
		   delete [] sources;
		   delete [] types;
		   delete [] ids;
		   delete [] severities;
		   delete [] lengths;
		   delete [] messageLog;
	}
*/
#endif

	void keyboard(int key, int x, int y)
	{
		switch(key) 
		{
		case GLUT_KEY_F1:
			end();
			exit(0);

			//exit(end());
			break;
		case GLUT_KEY_UP:
			window.translationCurrent.y += 1;
			window.translationOrigin = window.translationCurrent;
			break;
		case GLUT_KEY_DOWN:
			window.translationCurrent.y -= 1;
			window.translationOrigin = window.translationCurrent;
			break;
		case GLUT_KEY_LEFT:
			window.translationCurrent.x += 1;
			window.translationOrigin = window.translationCurrent;
			break;
		case GLUT_KEY_RIGHT:
			window.translationCurrent.x -= 1;
		       	window.translationOrigin = window.translationCurrent;;
			break;
		case GLUT_KEY_PAGE_UP:
			window.translationCurrent.z += 1;
			window.translationOrigin = window.translationCurrent;
			break;
		case GLUT_KEY_PAGE_DOWN:
			window.translationCurrent.z -= 1;
			window.translationOrigin = window.translationCurrent;
			break;
		}
	}

	void mouse(int button, int state, int x, int y)
	{
		switch(state)
		{
			case GLUT_DOWN:
			{
				window.mouseOrigin = window.mouseCurrent = glm::ivec2(x, y);
				switch(button)
				{
					case GLUT_LEFT_BUTTON:
					{
						window.mouseButtonFlags |= glf::MOUSE_BUTTON_LEFT;
						window.translationOrigin = window.translationCurrent;
					}
					break;
					case GLUT_MIDDLE_BUTTON:
					{
						window.mouseButtonFlags |= glf::MOUSE_BUTTON_MIDDLE;
					}
					break;
					case GLUT_RIGHT_BUTTON:
					{
						window.mouseButtonFlags |= glf::MOUSE_BUTTON_RIGHT;
						window.rotationOrigin = window.rotationCurrent;
					}
					break;
				}
			}
			break;
			case GLUT_UP:
			{
				switch(button)
				{
					case GLUT_LEFT_BUTTON:
					{
						window.translationOrigin += glm::vec3((window.mouseCurrent - window.mouseOrigin), 0.0f) / 10.f;
						window.mouseButtonFlags &= ~glf::MOUSE_BUTTON_LEFT;
					}
					break;
					case GLUT_MIDDLE_BUTTON:
					{
						window.mouseButtonFlags &= ~glf::MOUSE_BUTTON_MIDDLE;
					}
					break;
					case GLUT_RIGHT_BUTTON:
					{
						window.rotationOrigin += glm::vec3(window.mouseCurrent - window.mouseOrigin, 0.0f);
						window.mouseButtonFlags &= ~glf::MOUSE_BUTTON_RIGHT;
					}
					break;
				}
			}
			break;
		}
	}

	void reshape(int w, int h)
	{
		window.size = glm::ivec2(w, h);
	}

	void idle()
	{
//#if defined(WIN32)
		glutPostRedisplay();
//#endif
	}

	void close()
	{
		exit(end() ? 0 : 1);
	}

	void motion(int x, int y)
	{
		window.mouseCurrent = glm::ivec2(x, y);
		
		glm::vec2 temp = window.mouseCurrent - window.mouseOrigin;
		window.translationCurrent = window.mouseButtonFlags & glf::MOUSE_BUTTON_LEFT ? window.translationOrigin + glm::vec3(temp.x, temp.y, 0.0f) / 10.f : window.translationOrigin;
		window.rotationCurrent = window.mouseButtonFlags & glf::MOUSE_BUTTON_RIGHT ? window.rotationOrigin + glm::vec3(temp.x, temp.y, 0.0f) : window.rotationOrigin;
	}

	void displayProxy()
	{
//		int FrameID = 0;
//		++FrameID;
//#ifdef GLF_AUTO_STATUS
//		if(FrameID > 10)
//			exit(end() ? 0 : 1);
//#endif//GLF_AUTO_STATUS
		display();
	}

	int run	(int argc, 
	         char* argv[], 
	         glm::ivec2 const & Size, 
	         int Profile, 
	         int Major, 
	         int Minor)
	{
		glutInitWindowSize(Size.x, Size.y);
		glutInitWindowPosition(64, 64);
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);// | GLUT_MULTISAMPLE);

		int WindowHandle = glutCreateWindow(argv[0]);
		
#if !defined(__APPLE__)
		glewExperimental = GL_TRUE;
		glewInit();
#endif//__APPLE__

		glutDestroyWindow(WindowHandle);

#if !defined(__APPLE__)
		glutInitContextVersion(Major, Minor);
//		if(Profile == WGL_CONTEXT_ES2_PROFILE_BIT_EXT)
//			glutInitContextProfile(WGL_CONTEXT_ES2_PROFILE_BIT_EXT);
		if(glf::version(Major, Minor) >= 320)
		{
			glutInitContextProfile(Profile); // GLUT_COMPATIBILITY_PROFILE GLUT_CORE_PROFILE
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
		}
#endif//__APPLE__
		
		glutCreateWindow(argv[0]);
		init();

		if(begin())
		{
			glutDisplayFunc(displayProxy); 
			glutReshapeFunc(glf::reshape);
			glutMouseFunc(glf::mouse);
			glutMotionFunc(glf::motion);
			// glutKeyboardFunc(glf::keyboard);
			glutSpecialFunc(glf::keyboard);
			glutIdleFunc(glf::idle);
#if !defined(__APPLE__)
			glutCloseFunc(glf::close);
			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
#endif//__APPLE__
			glutMainLoop();

			return 0;
		}

		return 1;
	}

}//namespace glf
