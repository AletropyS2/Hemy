#include "hemypch.h"
#include "VertexArray.h"

#include <GL/glew.h>

namespace Hemy
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddBufferLayout(const VertexBuffer& vb, const BufferLayout& layout)
	{
		vb.Bind();
		auto& elements = layout.GetElements();

		uint32_t offset = 0;
		for (int i = 0; i < elements.size(); i++)
		{
			auto& element = elements[i];

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.Count, element.Type, false, layout.GetStride(), (void*)element.Offset);
		}
		vb.Unbind();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}
