#include "hemypch.h"
#include "OrthographicCamera.h"

#include <GL/glew.h>

namespace Hemy
{
	OrthographicCamera::OrthographicCamera(float width, float height, float orthoSize)
		: m_View(1.0f), m_OrthoSize(orthoSize)
	{
		m_AspectRatio = width / height;
		m_Projection = Mat4::Ortho(-m_AspectRatio * m_OrthoSize, m_AspectRatio * m_OrthoSize, -m_OrthoSize, m_OrthoSize, -1.0f, 1.0f);
		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::SetViewport(float width, float height)
	{
		m_AspectRatio = width / height;
		glViewport(0, 0, (int)width, (int)height);
		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::RecalculateProjectionMatrix()
	{
		m_Projection = Mat4::Ortho(-m_AspectRatio * m_OrthoSize, m_AspectRatio * m_OrthoSize, -m_OrthoSize, m_OrthoSize, -1.0f, 1.0f);
		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		Mat4 transform = Mat4::Translate(1.0f, -m_Position);

		m_View = transform;
		m_ViewProjection = m_Projection * m_View;
	}
}