#pragma once

#include <string>
#include <stdint.h>

#include "Core.h"

namespace Hemy
{
	class HEMY_API Shader
	{
	public:
		Shader(const std::string& vertPath, const std::string& fragPath, bool parseShader = true);
		~Shader();

		void Bind();
		void Unbind();

		// Uniforms

		void UploadFloat4(const std::string& name, float v0, float v1, float v2, float v3);
		void UploadInt1(const std::string& name, int value);
		void UploadIntArray(const std::string& name, int* values, uint32_t count);
		void UploadMatrix4x4(const std::string& name, float* valuePtr, bool transpose = false);

	private:
		int GetUniformLocation(const std::string& name);

	private:
		static std::string ParseShader(const std::string& filepath);
		static uint32_t CompileShader(uint32_t type, const std::string& source);

	private:
		uint32_t m_RendererID;

	};
}