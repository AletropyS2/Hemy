#pragma once

#include "Core.h"
#include "Hemy/Math/Mat4.h"
#include "Hemy/Math/Vector.h"

namespace Hemy
{
	class HEMY_API OrthographicCamera
	{
	public:
		OrthographicCamera(float width, float height, float orthoSize = 5.0f);

		const Vec3& GetPosition() const { return m_Position; }
		void SetPosition(const Vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		float GetSize() const { return m_OrthoSize; }
		void SetSize(float size) { m_OrthoSize = size; RecalculateProjectionMatrix(); }

		void SetViewport(float width, float height);

		const Mat4& GetProjectionMatrix() const { return m_Projection; }
		const Mat4& GetViewMatrix() const { return m_View; }
		const Mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }
	private:
		void RecalculateProjectionMatrix();
		void RecalculateViewMatrix();

	private:
		Mat4 m_Projection;
		Mat4 m_View;
		Mat4 m_ViewProjection;

		Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		float m_AspectRatio;
		float m_OrthoSize;
	};
}