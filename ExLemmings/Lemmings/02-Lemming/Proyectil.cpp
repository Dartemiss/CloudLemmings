#include "Proyectil.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum ProyectilAnims {
	MOVE_RIGHT,EXPLOTE,EMPTY
};

void Proyectil::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet) {

	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	for (int i = 4; i<7; i++)
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(float(i) / 16.0f, 0.07142857143f * 15/2));

	sprite->setAnimationSpeed(EXPLOTE, 8);
	for (int i = 8; i<14; i++)
		sprite->addKeyframe(EXPLOTE, glm::vec2(float(i) / 16.0f, 0.07142857143f * 13 / 2));

	sprite->setAnimationSpeed(EMPTY, 8);
	sprite->addKeyframe(EMPTY, glm::vec2(float(14) / 16.0f, 0.07142857143f * 1 / 2));

	//state = MOVING_RIGHT_STATE;
	state = MOVING_RIGHT_STATE;
	sprite->changeAnimation(MOVE_RIGHT);
	sprite->setPosition(initialPosition);

	last = false;
}

void Proyectil::update(int deltaTime) {
	if (sprite->update(deltaTime) == 0)
		return;

	switch (state) {
	
	case MOVING_RIGHT_STATE:
		sprite->position() += glm::vec2(5,0);
		if (collision()) {
			last = true;
			sprite->position() -= glm::vec2(4, 0);
			sprite->changeAnimation(EXPLOTE);
			state = EXPLOTING_STATE;
		}
		break;
	case EXPLOTING_STATE:
		break;
	}
}

void Proyectil::change_state(int nstate) {
	if (nstate == 0) {
		sprite->changeAnimation(MOVE_RIGHT);
		state = MOVING_RIGHT_STATE;
	}
	else if (nstate == 1) {
		sprite->changeAnimation(EMPTY);
		state = EXPLOTING_STATE;
	}
}

int Proyectil::getState() {
	if (state == EXPLOTING_STATE) {
		return 1;
	}
	else return 0;
}


void Proyectil::render()
{

	sprite->render(0);


}

void Proyectil::setPosition(glm::vec2 Lpos) {
	sprite->setPosition(Lpos);
}

glm::vec2 Proyectil::getPosition() {
	return sprite->position();
}

void Proyectil::setMapMask(VariableTexture *mapMask)
{
	mask = mapMask;
}

bool Proyectil::collision()
{
	glm::ivec2 posBase = sprite->position() + glm::vec2(120, 0); // Add the map displacement

	posBase += glm::ivec2(7, 7);
	if ((mask->pixel(posBase.x, posBase.y) == 0) && (mask->pixel(posBase.x + 1, posBase.y) == 0))
		return false;
	if ((mask->pixel(posBase.x, posBase.y) == 0) && (mask->pixel(posBase.x - 1, posBase.y) == 0))
		return false;

	return true;
}