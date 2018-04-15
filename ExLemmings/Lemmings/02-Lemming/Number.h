#pragma once
#include "Sprite.h"
class Number
{
public:
	void init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update();
	void render();
	void diminish();
	glm::ivec2 getPos();
	void setValue(int val);
	int	getValue();
private:
	glm::ivec2 pos;
	int value;
	Sprite *sprite;
};
