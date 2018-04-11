#pragma once
#include "Sprite.h"
class Portal
{
public:
	void init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update(int deltaTime);
	void render();
	bool contact(int lemX, int lemY);
	glm::ivec2 getPos();
private:
	glm::ivec2 pos;
	Sprite *sprite;
};

