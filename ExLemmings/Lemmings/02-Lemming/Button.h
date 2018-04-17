#pragma once
#include "Sprite.h"

class Button
{
public:
	void init(int whichskill, int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update();
	void render(int offsetX);
	bool isPressed(int mouseX, int mouseY);
	void unPress();

private:
	glm::ivec2 pos;
	Sprite *sprite;
	bool pressed;
	int id_skill;
	int auxOffset;
	int posxx;
};


