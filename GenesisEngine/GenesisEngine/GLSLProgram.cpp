#include "GLSLProgram.h"
#include "Errors.h"

#include <vector>

#include <fstream>

GLSLProgram::GLSLProgram() : m_NumAttributes(0), m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	m_ProgramID = glCreateProgram();

	m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_VertexShaderID == 0) {
		fatalError("Vertex shader failed to be created!");
	}

	m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_FragmentShaderID == 0) {
		fatalError("Fragment shader failed to be created!");
	}

	CompileIndShader(vertexShaderFilePath, m_VertexShaderID);
	CompileIndShader(fragmentShaderFilePath, m_FragmentShaderID);
}

void GLSLProgram::LinkShaders() {
	glAttachShader(m_ProgramID, m_VertexShaderID);
	glAttachShader(m_ProgramID, m_FragmentShaderID);

	glLinkProgram(m_ProgramID);

	GLint isLinked = 0;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(m_ProgramID);

		glDeleteShader(m_VertexShaderID);
		glDeleteShader(m_FragmentShaderID);

		std::printf("%s\n", &(infoLog[0]));
		fatalError("Shaders failed to link!");
	}

	glDetachShader(m_ProgramID, m_VertexShaderID);
	glDetachShader(m_ProgramID, m_FragmentShaderID);
	glDeleteShader(m_VertexShaderID);
	glDeleteShader(m_FragmentShaderID);
}

void GLSLProgram::AddAttribute(const std::string& attributeName) {
	glBindAttribLocation(m_ProgramID, m_NumAttributes++, attributeName.c_str());
}

GLint GLSLProgram::GetUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		nonFatalError("Uniform '" + uniformName + "' not found in shader!");
	}
	return location;
}

void GLSLProgram::Use() {
	glUseProgram(m_ProgramID);
	for (int i = 0; i < m_NumAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse() {
	glUseProgram(0);
	for (int i = 0; i < m_NumAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::CompileIndShader(const std::string& filePath, GLuint id) {
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + filePath + " failed to compile");
	}
}