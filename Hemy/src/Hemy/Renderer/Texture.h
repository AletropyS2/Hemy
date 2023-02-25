#pragma once

#include <string>
#include "Core.h"

namespace Hemy
{
	class HEMY_API Texture
	{
	public:
		Texture(const std::string& filepath);
		Texture(uint32_t width, uint32_t height, uint32_t color);
		~Texture();

		void Bind(uint32_t slot = 0);
		void Unbind();

		uint32_t GetID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;
		int m_Width, m_Height, m_Comp;
		unsigned char* m_LocalBuffer;
	};
}