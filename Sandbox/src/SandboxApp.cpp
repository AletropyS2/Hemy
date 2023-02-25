#include <Hemy.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 600;

using namespace Hemy;

int main()
{
	HASSERT(glfwInit(), "Cannot initialize GLFW");

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, true);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Sandbox", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	Renderer::Initialize();

	static OrthographicCamera camera(800.0f, 600.0f);

	camera.SetSize(10.0f);
	Texture creeperTexture("assets/textures/creeper.png");

	glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height)
	{
		camera.SetViewport((float)width, (float)height);
	});

	camera.SetRotation(45.0f);
		

	while (!glfwWindowShouldClose(window))
	{
		RendererCommand::Clear({ 0.8f, 0.32f, 0.45f, 1.0f });

		Renderer::BeginScene(&camera);

		Renderer::DrawQuad(0.0f, 2.0f, 0.0f, nullptr, 1.0f);
		Renderer::DrawQuad(0.0f, 1.0f, 0.0f, &creeperTexture, 1.0f);

		Renderer::EndScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}