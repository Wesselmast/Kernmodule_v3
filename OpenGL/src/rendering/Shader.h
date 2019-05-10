#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader {
private:
	unsigned int rendererID;
	std::unordered_map<std::string, int> uniformLocationCashe;
public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unBind() const;

	//Set uniforms
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int value);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	bool compileShader();
	int getUniformLocation(const std::string& name);
	unsigned int compileShader(unsigned int type, const std::string & source);
	unsigned int createShader(const std::string & vertexShader, const std::string & fragmentShader);
};