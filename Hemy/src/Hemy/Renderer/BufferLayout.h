#pragma once

#include <stdint.h>
#include <vector>
#include "Core.h"

#include "GL/glew.h"

namespace Hemy 
{
	struct HEMY_API BufferLayoutElement
	{
		uint32_t Offset;
		uint32_t Count;
		uint32_t Type;
	};

	class HEMY_API BufferLayout
	{
	public:
		BufferLayout()
			: m_Stride(0) { }

		template<typename T>
		void Push(uint32_t count);

		template<>
		void Push<float>(uint32_t count)
		{
			m_Elements.push_back({ m_Stride, count, GL_FLOAT });
			m_Stride += count * sizeof(float) ;
		}

		template<>
		void Push<int>(uint32_t count)
		{
			m_Elements.push_back({ m_Stride, count, GL_INT });
			m_Stride += count * sizeof(int);
		}

		inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }
		inline const uint32_t GetStride() const { return m_Stride; }

	private:
		uint32_t m_Stride;
		std::vector<BufferLayoutElement> m_Elements;
	};
}