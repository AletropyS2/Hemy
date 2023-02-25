#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Buffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include "OrthographicCamera.h"

namespace Hemy
{
	class HEMY_API Renderer
	{
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(OrthographicCamera* camera);
		static void EndScene();

		static void Flush();
		static void NextBatch();
		static void StartBatch();

		static void DrawQuad(const Vec3& position, const Vec3& scale, float rotation, Texture* texture, const Vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	private:
		static OrthographicCamera* m_CurrentCamera;
	};
}