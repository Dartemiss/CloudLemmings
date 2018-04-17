#pragma once
#ifndef _GATE_INCLUDE
#define _GATE_INCLUDE


#include "Sprite.h"
#include "VariableTexture.h"

class Gate
{
public:
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet1, Texture &spritesheet2,bool s);
	void update(int deltaTime);
	void render(int offsetX);
	glm::vec2 getPosition();
	void setPosition(glm::vec2 aux);
	bool isColliding(glm::vec2 pos);
private:
	Sprite * sprite, * spriteOut;
	VariableTexture *mask;
	bool inout;
	glm::vec2 pos;
};
#endif // _GATE_INCLUDE