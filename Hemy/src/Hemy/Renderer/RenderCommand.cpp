#include "hemypch.h"
#include "RendererCommand.h"

#include <GL/glew.h>

namespace Hemy
{
	void RendererCommand::Clear(const Vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}