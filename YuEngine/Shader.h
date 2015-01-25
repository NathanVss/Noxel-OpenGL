#ifndef DEF_SHADER
#define DEF_SHADER


#include <gl/glew.h>



// Includes communs

#include <iostream>
#include <string>
#include <fstream>


// Classe Shader
namespace YuEngine {
class Shader
{
    public:

    Shader();
    Shader(Shader const &shaderACopier);
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);
	GLuint getUniformLocation(const std::string& uniformName);
    bool charger();
    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    GLuint getProgramID() const;


	void sendFloat(std::string name, float value);
	void sendInt(std::string name, int value);


    private:

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};
}
#endif
