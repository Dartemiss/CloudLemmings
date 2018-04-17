#pragma once
#ifndef _PROYECTIL_INCLUDE
#define _PROYECTIL_INCLUDE


#include "Sprite.h"
#include "VariableTexture.h"

class Proyectil
{
public:
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update(int deltaTime);
	void render(int offsetX);
	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition();
	void change_state(int nstate);
	void setMapMask(VariableTexture *mapMask);
	bool last;
	int getState();

private:
	bool collision();
	enum ProyectilState
	{
		MOVING_RIGHT_STATE, MOVING_LEFT_STATE, EXPLOTING_STATE, EMPTY_STATE
	};
	Sprite *sprite;
	ProyectilState state;
	VariableTexture *mask;
	glm::vec2 pos;


};
#endif // _PROYECTIL_INCLUDE