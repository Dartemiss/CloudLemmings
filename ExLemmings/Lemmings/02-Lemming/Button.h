#pragma once
#include "Sprite.h"

class Button
{
public:
	void init(int whichskill, int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update();
	void render();
	bool isPressed(int mouseX, int mouseY);
	void unPress();

private:
	glm::vec2 pos;
	Sprite *sprite;
	int color;
	bool pressed;
};


