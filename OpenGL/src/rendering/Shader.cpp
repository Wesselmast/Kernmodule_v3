#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"

struct ShaderSources {
	std::string VertexSource;
	std::string FramentSource;
};

ShaderSources parseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;

	std::string line;
	std::stringstream ss[2];
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}


Shader::Shader(const std::string & filepath) : rendererID(0) {
	ShaderSources source = parseShader(filepath);
	rendererID = createShader(source.VertexSource, source.FramentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(rendererID));
}

bool Shader::compileShader() {
	return false;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::bind() const {
	GLCall(glUseProgram(rendererID));
}

void Shader::unBind() const {
	GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string & name, float v0, float v1, float v2, float v3) {
	int location = getUniformLocation(name);
	GLCall(glUniform4f(location, v0, v1, v2, v3))
}

void Shader::setUniform1i(const std::string & name, int value) {
	int location = getUniformLocation(name);
	GLCall(glUniform1i(location, value))
}

void Shader::setUniformMat4f(const std::string & name, const glm::mat4 & matrix) {
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string & name) {
	if (uniformLocationCashe.find(name) != uniformLocationCashe.end()) {
		return uniformLocationCashe[name];
	}

	GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));

	if (location != -1) {
		uniformLocationCashe[name] = location;
	}
	return location;
}
