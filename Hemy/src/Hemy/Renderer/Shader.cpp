#include "hemypch.h"
#include "Shader.h"

#include <GL/glew.h>

namespace Hemy
{
	Shader::Shader(const std::string& vertPath, const std::string& fragPath, bool parseShader)
	{
		m_RendererID = glCreateProgram();

		uint32_t vs = CompileShader(GL_VERTEX_SHADER, parseShader ? ParseShader(vertPath) : vertPath);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, parseShader ? ParseShader(fragPath) : fragPath);

		glAttachShader(m_RendererID, vs);
		glAttachShader(m_RendererID, fs);

		glLinkProgram(m_RendererID);

		int success;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			int lenght;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &lenght);
			char* msg = new char[lenght];
			glGetProgramInfoLog(m_RendererID, lenght, 0, msg);

			HERROR("Failed to link program: %s", msg);
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::UploadFloat4(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::UploadInt1(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::UploadIntArray(const std::string& name, int* values, uint32_t count)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void Shader::UploadMatrix4x4(const std::string& name, float* valuePtr, bool transpose)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, valuePtr);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		return location;
	}

	std::string Shader::ParseShader(const std::string& filepath)
	{

		std::ifstream stream(filepath);

		HASSERT(stream.is_open(), "Cannot open shader file");

		std::string line;
		std::stringstream ss;

		while (getline(stream, line))
		{
			ss << line << "\n";
		}

		return ss.str();
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
	{
		uint32_t id = glCreateShader(type);

		const char* src = source.c_str();
		glShaderSource(id, 1, &src, 0);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int lenght;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
			char* msg = new char[lenght];
			glGetShaderInfoLog(id, lenght, 0, msg);

			HERROR("Cannot compile shader: %s", msg);
		}

		return id;
	}
}