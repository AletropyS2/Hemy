#pragma once

#include <stdint.h>
#include "Core.h"

#define GL_STATIC_DRAW 0x88E4

namespace Hemy
{

	class HEMY_API VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size, void* data, uint32_t usage = GL_STATIC_DRAW);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(uint32_t size, void* data);

	private:
		uint32_t m_RendererID;
	};

	class ElementBuffer
	{
	public:
		ElementBuffer(uint32_t size, void* data, uint32_t usage = GL_STATIC_DRAW);
		~ElementBuffer();

		void Bind();
		void Unbind();

	private:
		uint32_t m_RendererID;
	};

}