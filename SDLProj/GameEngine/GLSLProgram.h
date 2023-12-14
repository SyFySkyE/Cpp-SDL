#pragma once

#include <string>
#include <GL/glew.h>

namespace GameEngine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void AddAttribute(const std::string& attributeName);
		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void LinkShaders();
		void Use();
		void UnUse();
		GLuint GetUniformLocation(const std::string& uniformName);
	private:

		void CompileShader(const std::string& filePath, GLuint id);

		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};
}


