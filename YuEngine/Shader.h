#ifndef DEF_SHADER
#define DEF_SHADER


#include <gl/glew.h>
#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtx\transform.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>


// Includes communs

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


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
    bool charger(std::vector<std::string> _locations);
    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    GLuint getProgramID() const;


	void sendFloat(std::string name, float value);
	void sendInt(std::string name, int value);
	void sendMatrix4(std::string name, glm::mat4 &matrix);

	void use();
	void unuse();

    private:
	std::vector<std::string> locations;

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};
}
#endif
