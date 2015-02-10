#pragma once

#include <string>
#include <GL\glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const std::string& p_VertexShaderFilePath, const std::string& p_FragmentShaderFilePath);
	void LinkShaders();
	void AddAttribute(const std::string& p_AttributeName);

	GLint GetUniformLocation(const std::string& m_UniformName);

	void Use();
	void Unuse();
private:
	void CompileIndShader(const std::string& p_FilePath, GLuint p_Id);

	int m_NumAttributes;

	GLuint m_ProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
};