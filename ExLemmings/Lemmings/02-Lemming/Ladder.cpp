#include "Ladder.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum LadderAnims {
	ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,ELEVEN,TWUELVE,FULL,ZERO
};

void Ladder::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet){
	sprite = Sprite::createSprite(glm::ivec2(40, 20), glm::vec2(0.125, 2*0.03571428571), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);

	sprite->setAnimationSpeed(FULL, 12);
	sprite->addKeyframe(FULL, glm::vec2(float(0) / 8.0f, 2*0.03571428571* 0));

	sprite->setAnimationSpeed(ONE, 12);
	sprite->addKeyframe(ONE, glm::vec2(float(1) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(TWO, 12);
	sprite->addKeyframe(TWO, glm::vec2(float(2) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(THREE, 12);
	sprite->addKeyframe(THREE, glm::vec2(float(3) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(FOUR, 12);
	sprite->addKeyframe(FOUR, glm::vec2(float(4) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(FIVE, 12);
	sprite->addKeyframe(FIVE, glm::vec2(float(5) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(SIX, 12);
	sprite->addKeyframe(SIX, glm::vec2(float(6) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(SEVEN, 12);
	sprite->addKeyframe(SEVEN, glm::vec2(float(7) / 8.0f, 2*0.03571428571 * 0));

	sprite->setAnimationSpeed(EIGHT, 12);
	sprite->addKeyframe(EIGHT, glm::vec2(float(0) / 8.0f, 2*0.03571428571 * 1));

	sprite->setAnimationSpeed(NINE, 12);
	sprite->addKeyframe(NINE, glm::vec2(float(1) / 8.0f, 2*0.03571428571 * 1));

	sprite->setAnimationSpeed(TEN, 12);
	sprite->addKeyframe(TEN, glm::vec2(float(2) / 8.0f, 2*0.03571428571 * 1));

	sprite->setAnimationSpeed(ELEVEN, 12);
	sprite->addKeyframe(ELEVEN, glm::vec2(float(3) / 8.0f, 2*0.03571428571 * 1));

	sprite->setAnimationSpeed(TWUELVE, 12);
	sprite->addKeyframe(TWUELVE, glm::vec2(float(4) / 8.0f, 2*0.03571428571 * 1));

	sprite->setAnimationSpeed(ZERO, 12);
	sprite->addKeyframe(ZERO, glm::vec2(float(5) / 8.0f, 2*0.03571428571 * 2));

	sprite->changeAnimation(ZERO);
	sprite->setPosition(initialPosition);

	
}

void Ladder::changeSteps(int numStep) {
	if (numStep == 1) {
		sprite->changeAnimation(ONE);
	}
	else if (numStep == 2) {
		sprite->changeAnimation(TWO);
	}
	else if (numStep == 3) {
		sprite->changeAnimation(THREE);
	}
	else if (numStep == 4) {
		sprite->changeAnimation(FOUR);
	}
	else if (numStep == 5) {
		sprite->changeAnimation(FIVE);
	}
	else if (numStep == 6) {
		sprite->changeAnimation(SIX);
	}
	else if (numStep == 7) {
		sprite->changeAnimation(SEVEN);
	}
	else if (numStep == 8) {
		sprite->changeAnimation(EIGHT);
	}
	else if (numStep == 9) {
		sprite->changeAnimation(NINE);
	}
	else if (numStep == 10) {
		sprite->changeAnimation(TEN);
	}
	else if (numStep == 11) {
		sprite->changeAnimation(ELEVEN);
	}
	else if (numStep == 12) {
		sprite->changeAnimation(TWUELVE);
	}
	else if (numStep == 13) {
		sprite->changeAnimation(FULL);
	}
	else if (numStep == 0) {
		sprite->changeAnimation(ZERO);
	}
}

void Ladder::changePos(glm::vec2 pos) {
	pos = pos - glm::vec2(0, 2);
	sprite->setPosition(pos);
}

void Ladder::update(int deltaTime){
	if (sprite->update(deltaTime) == 0)
		return;
}


void Ladder::render()
{
	sprite->render();
}