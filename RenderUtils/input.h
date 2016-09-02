#pragma once



#ifndef INPUT_H
#define INPUT_H



class input
{
public:
	enum key_state
	{
		UP,DOWN,PRESS,RELEASE
	};
	enum
	{
		LEFT_MOUSE, RIGHT_MOUSE, MIDDLE_MOUSE
	};
private:
	struct GLFWwindow *winHandle;
	key_state keys[1024];
	float curMousePos[2], prevMousePos[2], deltaMousePos[2];

	key_state mouseKeys[8];

public:


	bool init(const class Window &window);
	bool step();
	bool term();

	void setCursorPos(double xPos, double yPos);

	key_state getKeyState(int key) const;

	key_state getMouseButtonState(int button) const;

	void getMousePos(float &xPos, float &yPos) const;
	void getDeltaMouse(float &xPos, float &yPos) const;

	void hideCursor() const;
	void showCursor() const;


};



#endif
