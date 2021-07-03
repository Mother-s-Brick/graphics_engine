#pragma once

class Input {
public:
	/// <summary>
	/// Returns whether or not the keyCode
	/// (GLFW key enum) is pressed or not
	/// </summary>
	static bool isKeyPressed(int keyCode);
};