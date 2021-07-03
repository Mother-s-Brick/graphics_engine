#include "Input.h"

static GLFWwindow* window = nullptr;

void Input::setWindow(Window* newWindow) {
	window = newWindow->window;
}

bool Input::isKeyPressed(int keyCode) {
	if (window == nullptr) return false;
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

void Input::closeWindow() {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Input::getWindowSize(int& width, int& height) {
	glfwGetFramebufferSize(window, &width, &height);
}
