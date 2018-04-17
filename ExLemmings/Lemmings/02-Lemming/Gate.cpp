#include "Gate.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum GateAnims {
	OPEN, WIN, START,OUT1
};

void Gate::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet1, Texture &spritesheet2,bool s) {
	inout = s;
	
	sprite = Sprite::createSprite(glm::ivec2(60, 30), glm::vec2(0.5, 0.1), &spritesheet1, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(OPEN, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(OPEN, glm::vec2(float(0) / 2.0f, 0.1 * i));

	sprite->setAnimationSpeed(START, 12);
	sprite->addKeyframe(START, glm::vec2(float(0) / 2.0f, 0.1 * 8));

	sprite->changeAnimation(OPEN);
	sprite->setPosition(initialPosition);

	spriteOut = Sprite::createSprite(glm::ivec2(40, 30), glm::vec2(0.3333333, 0.125), &spritesheet2, &shaderProgram);
	spriteOut->setNumberAnimations(3);

	spriteOut->setAnimationSpeed(OUT1, 12);
	for (int i = 0; i<8; i++)
		spriteOut->addKeyframe(OUT1, glm::vec2(float(1) / 3.0f, 0.125 * i));

	spriteOut->changeAnimation(OUT1);
	spriteOut->setPosition(initialPosition);
	pos = initialPosition;
}

void Gate::update(int deltaTime) {
	if (sprite->update(deltaTime) == 0 && inout)
		return;
	if (spriteOut->update(deltaTime) == 0 && !inout)
		return;
	if (sprite->keyframe() == 7 && inout)
		sprite->changeAnimation(START);
}

void Gate::setPosition(glm::vec2 aux) {
	sprite->setPosition(aux);
	pos = aux;
}

bool Gate::isColliding(glm::vec2 lemP){
	if (lemP.x == pos.x + 12){
		if ((lemP.y < pos.y + 20) && lemP.y > pos.y - 20){
			return true;
		}
	}
	return false;
}

void Gate::render(int offsetX)
{
	if (inout) {
		sprite->render(offsetX);
	}
	else {
		spriteOut->render(offsetX);
	}
}