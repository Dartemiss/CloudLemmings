#pragma once
#include "Sprite.h"

class Particle
{
public:
	void init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update(int deltaTime);
	void render(int offsetX);

private:
	glm::dvec2 pos;
	glm::dvec2 vel;
	glm::dvec2 acc;
	Sprite *sprite;
	int color;
};

