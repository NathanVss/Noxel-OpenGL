#include "Shader.h"

// Constructeurs et Destructeur
namespace YuEngine {

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{
}


Shader::Shader(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;


    // Chargement du nouveau shader

	charger(shaderACopier.locations);
}


Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
                                                                       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}


Shader::~Shader()
{
    // Destruction du shader

    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}


// M�thodes

Shader& Shader::operator=(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;


    // Chargement du nouveau shader
	

	charger(shaderACopier.locations);


    // Retour du pointeur this

    return *this;
}

void Shader::sendFloat(std::string name, float value) {
	glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);

}
void Shader::sendInt(std::string name, int value) {
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}
void Shader::sendMatrix4(std::string name, glm::mat4 &matrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(matrix));

}
void Shader::use() {
	glUseProgram(m_programID);
}
void Shader::unuse() {
	glUseProgram(0);
}


GLuint Shader::getUniformLocation(const std::string& uniformName) {
	GLuint location = glGetUniformLocation(m_programID, uniformName.c_str());
	if(location == GL_INVALID_INDEX) {
		std::cout << "Uniforme" + uniformName + " not found in shader !" << std::endl;
		return 0;
	}
	return location;
}


bool Shader::charger(std::vector<std::string> _locations)
{
    // Destruction d'un �ventuel ancien Shader

    if(glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if(glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

    if(glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);


    // Compilation des shaders

    if(!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;

    if(!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;


    // Cr�ation du programme

    m_programID = glCreateProgram();


    // Association des shaders

    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);


	locations = _locations;
    // Verrouillage des entr�es shader
	for(int i = 0; i < locations.size(); i++) {
		glBindAttribLocation(m_programID, i, locations[i].c_str());

	}
    //glBindAttribLocation(m_programID, 0, "vertexPosition");
    //glBindAttribLocation(m_programID, 1, "vertexColor");
    //glBindAttribLocation(m_programID, 2, "vertexUV");


    // Linkage du programme

    glLinkProgram(m_programID);


    // V�rification du linkage

    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);


    // S'il y a eu une erreur

    if(erreurLink != GL_TRUE)
    {
        // R�cup�ration de la taille de l'erreur

        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de m�moire

        char *erreur = new char[tailleErreur + 1];


        // R�cup�ration de l'erreur

        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

        std::cout << erreur << std::endl;


        // Lib�ration de la m�moire et retour du bool�en false

        delete[] erreur;
        glDeleteProgram(m_programID);

        return false;
    }



    // Sinon c'est que tout s'est bien pass�

    else
        return true;
}


bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Cr�ation du shader

    shader = glCreateShader(type);


    // V�rification du shader

    if(shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }


    // Flux de lecture

    std::ifstream fichier(fichierSource.c_str());


    // Test d'ouverture

    if(!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);

        return false;
    }


    // Strings permettant de lire le code source

    std::string ligne;
    std::string codeSource;


    // Lecture

    while(getline(fichier, ligne))
        codeSource += ligne + '\n';


    // Fermeture du fichier

    fichier.close();


    // R�cup�ration de la chaine C du code source

    const GLchar* chaineCodeSource = codeSource.c_str();


    // Envoi du code source au shader

    glShaderSource(shader, 1, &chaineCodeSource, 0);


    // Compilation du shader

    glCompileShader(shader);


    // V�rification de la compilation

    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);


    // S'il y a eu une erreur

    if(erreurCompilation != GL_TRUE)
    {
        // R�cup�ration de la taille de l'erreur

        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de m�moire

        char *erreur = new char[tailleErreur + 1];


        // R�cup�ration de l'erreur

        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

        std::cout << erreur << std::endl;


        // Lib�ration de la m�moire et retour du bool�en false

        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }


    // Sinon c'est que tout s'est bien pass�

    else
        return true;
}


// Getter

GLuint Shader::getProgramID() const
{
    return m_programID;
}
}