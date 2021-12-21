#ifndef SHADER_H
#define SHADER_H

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

struct shaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	unsigned int m_rendererID;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int value);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	shaderProgramSource parseShader(const std::string &filepath);
	unsigned int compileShader(unsigned int type, const std::string &source);
	unsigned int createShader(const std::string vertexShader, const std::string fragmentShader);
	int getUniformLocation(const std::string& name);
};

#endif