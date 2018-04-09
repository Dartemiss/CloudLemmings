#pragma once
#ifndef _LADDER_INCLUDE
#define _LADDER_INCLUDE


#include "Sprite.h"
#include "VariableTexture.h"

class Ladder
{
public:
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update(int deltaTime);
	void render();
	void changeSteps(int numStep);
	void changePos(glm::vec2 pos);

private:
	Sprite * sprite, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6,
		*sprite7, *sprite8, *sprite9, *sprite10, *sprite11, *sprite12;
	VariableTexture *mask;
};
#endif // _LADDER_INCLUDE