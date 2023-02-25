#pragma once

#include "Buffer.h"
#include "BufferLayout.h"
#include <stdint.h>

namespace Hemy
{
	class HEMY_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBufferLayout(const VertexBuffer& vb, const BufferLayout& layout);

		void Bind();
		void Unbind();

	private:
		uint32_t m_RendererID;
	};
}