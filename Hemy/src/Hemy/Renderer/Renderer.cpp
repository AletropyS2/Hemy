#include "hemypch.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <cmath>

static void OpenGLErrorCallback(GLenum source, GLenum type, uint32_t id, GLenum severity, int lenght, const char* msg, const void* userparam)
{
	HERROR("OpenGL Error! Severity: %d | Error: %s", severity, msg);
}

const static std::string DefaultShaderVert = R"(
#version 400 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_ViewProj;

void main()
{
	gl_Position = u_ViewProj * a_Position;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
})";

const static std::string DefaultShaderFrag = R"(
#version 330 core

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

out vec4 o_Color;

uniform sampler2D u_Textures[16];

void main()
{
	int id = int(v_TexIndex);
	vec4 texColor;

	if(id == 0) { texColor = texture(u_Textures[0], v_TexCoord); } 
	else if(id == 1) { texColor = texture(u_Textures[1], v_TexCoord); }
	else if(id == 2) { texColor = texture(u_Textures[2], v_TexCoord); }
	else if(id == 3) { texColor = texture(u_Textures[3], v_TexCoord); }
	else if(id == 4) { texColor = texture(u_Textures[4], v_TexCoord); }
	else if(id == 5) { texColor = texture(u_Textures[5], v_TexCoord); }
	else if(id == 6) { texColor = texture(u_Textures[6], v_TexCoord); }
	else if(id == 7) { texColor = texture(u_Textures[7], v_TexCoord); }
	else if(id == 8) { texColor = texture(u_Textures[8], v_TexCoord); }
	else if(id == 9) { texColor = texture(u_Textures[9], v_TexCoord); }
	else if(id == 10) { texColor = texture(u_Textures[10], v_TexCoord); }
	else if(id == 11) { texColor = texture(u_Textures[11], v_TexCoord); }
	else if(id == 12) { texColor = texture(u_Textures[12], v_TexCoord); }
	else if(id == 13) { texColor = texture(u_Textures[13], v_TexCoord); }
	else if(id == 14) { texColor = texture(u_Textures[14], v_TexCoord); }
	else if(id == 15) { texColor = texture(u_Textures[15], v_TexCoord); }

	o_Color = texColor * v_Color;
}
)";

namespace Hemy
{
	OrthographicCamera* Renderer::m_CurrentCamera = nullptr;

	static Shader* DefaultShader = nullptr;
	static VertexArray* VA = nullptr;
	static VertexBuffer* VB = nullptr;
	static ElementBuffer* EB = nullptr;

	struct Vertex
	{
		Vec4 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TexIndex;
	};

	static const Vec4 QuadVertexPositions[4]
	{
		{ -1.0f, -1.0f, 0.0f, 1.0f },
		{ -1.0f, 1.0f,	0.0f, 1.0f },
		{ 1.0f,	 1.0f,	0.0f, 1.0f },
		{ 1.0f,  -1.0f, 0.0f, 1.0f }
	};

	static Vertex* QuadBufferBase;
	static Vertex* QuadBufferPtr;

	const static uint32_t MaxQuads = 1000;
	const static uint32_t MaxVertices = MaxQuads * 4;
	const static uint32_t MaxIndices = MaxQuads * 6;
	const static uint32_t MaxTextures = 16;

	std::array<Texture*, MaxTextures> TextureSlots;
	uint32_t TextureSlotIndex = 1; // 0: White Texture

	Texture* WhiteTexture;

	static uint32_t Quads = 0;

	void Renderer::Initialize()
	{
		int success = glewInit();
		HASSERT(success == GLEW_OK, "Cannot initialize Glew");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		QuadBufferBase = new Vertex[MaxVertices];

		DefaultShader = new Shader(DefaultShaderVert, DefaultShaderFrag, false);

		VA = new VertexArray{};
		VA->Bind();
		VB = new VertexBuffer(MaxVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		uint32_t* indices = new uint32_t[MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < MaxIndices; i+=6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		EB = new ElementBuffer(MaxIndices, (void*)indices);

		BufferLayout layout;
		layout.Push<float>(4);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);

		VA->AddBufferLayout(*VB, layout);

		VA->Unbind();

		WhiteTexture = new Texture(1, 1, 0xffffffff);

		TextureSlots[0] = WhiteTexture;

		for (uint32_t i = 1; i < MaxTextures; i++)
			TextureSlots[i] = nullptr;

		int32_t textureSampler[MaxTextures];
		for (uint32_t i = 0; i < MaxTextures; i++)
			textureSampler[i] = i;

		DefaultShader->Bind();
		DefaultShader->UploadIntArray("u_Textures", textureSampler, MaxTextures);
		DefaultShader->Unbind();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::BeginScene(OrthographicCamera* camera)
	{
		m_CurrentCamera = camera;

		StartBatch();
	}

	void Renderer::EndScene()
	{
		Flush();
	}

	void Renderer::Flush()
	{

		uint32_t dataSize = (uint32_t)((uint8_t*)QuadBufferPtr - (uint8_t*)QuadBufferBase);

		VB->SetData(dataSize, QuadBufferBase);
		VA->Bind();

		// Bind Textures
		for (uint32_t i = 0; i < TextureSlotIndex; i++)
			TextureSlots[i]->Bind(i);

		DefaultShader->Bind();
		Mat4 viewProj = m_CurrentCamera->GetViewProjectionMatrix();
		DefaultShader->UploadMatrix4x4("u_ViewProj", viewProj.GetValues());

		glDrawElements(GL_TRIANGLES, Quads * 6, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer::StartBatch()
	{
		Quads = 0;
		QuadBufferPtr = QuadBufferBase;
	}

	void Renderer::DrawQuad(const Vec3& position, const Vec3& scale, float rotation, Texture* texture, const Vec4& color)
	{
		Mat4 transform = Mat4::Translate(1.0f, position)
			* Mat4::Rotate(1.0f, (rotation * 3.14 / 180), { 0.0f, 0.0f, 1.0f })
			* Mat4::Scale(1.0f, scale);

		Vec2 texCoords[4] { { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };

		float textureIndex = 0.0f;

		if (texture != nullptr)
		{
			for (uint32_t i = 1; i < TextureSlotIndex; i++)
			{
				if (TextureSlots[i]->GetID() == texture->GetID())
				{
					textureIndex = (float)i;
					break;
				}
			}

			if (textureIndex == 0.0f)
			{
				textureIndex = (float)TextureSlotIndex;
				TextureSlots[TextureSlotIndex] = texture;
				TextureSlotIndex++;
			}
		}

		for (uint32_t i = 0; i < 4; i++)
		{
			QuadBufferPtr->Position = transform * QuadVertexPositions[i];
			QuadBufferPtr->Color = color;
			QuadBufferPtr->TexCoord = texCoords[i];
			QuadBufferPtr->TexIndex = textureIndex;

			QuadBufferPtr++;
		}

		Quads++;
	}

}