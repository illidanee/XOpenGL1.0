#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

void Callback_Error(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void Callback_Key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	/* Regsiter callback function */
	glfwSetErrorCallback(Callback_Error);

	GLFWwindow* pWindow;

	/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);

	/* Create a windowed mode window and its OpenGL context */
	pWindow = glfwCreateWindow(800, 600, "illidan", NULL, NULL);
	if (!pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Regsiter callback function */
	glfwSetKeyCallback(pWindow, Callback_Key);

	/* Make the window's context current */
	glfwMakeContextCurrent(pWindow);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(pWindow))
	{
		/* Render here */
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();
	return 0;
}