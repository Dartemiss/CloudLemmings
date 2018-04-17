#include "Ladder.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum LadderAnims {
	ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,ELEVEN,TWUELVE,FULL,ZERO,
	L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, LF
};

void Ladder::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet){
	sprite = Sprite::createSprite(glm::ivec2(40, 20), glm::vec2(0.125, 2*0.03571428571), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(27);

	sprite->addKeyframe(FULL, glm::vec2(float(5) / 8.0f, 2 * 0.03571428571 * 1));
	sprite->addKeyframe(ONE, glm::vec2(float(1) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(TWO, glm::vec2(float(2) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(THREE, glm::vec2(float(3) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(FOUR, glm::vec2(float(4) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(FIVE, glm::vec2(float(5) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(SIX, glm::vec2(float(6) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(SEVEN, glm::vec2(float(7) / 8.0f, 2*0.03571428571 * 0));

	sprite->addKeyframe(EIGHT, glm::vec2(float(0) / 8.0f, 2*0.03571428571 * 1));

	sprite->addKeyframe(NINE, glm::vec2(float(1) / 8.0f, 2*0.03571428571 * 1));

	sprite->addKeyframe(TEN, glm::vec2(float(2) / 8.0f, 2*0.03571428571 * 1));

	sprite->addKeyframe(ELEVEN, glm::vec2(float(3) / 8.0f, 2*0.03571428571 * 1));

	sprite->addKeyframe(TWUELVE, glm::vec2(float(4) / 8.0f, 2*0.03571428571 * 1));

	sprite->addKeyframe(ZERO, glm::vec2(float(5) / 8.0f, 2 * 0.03571428571 * 6));
	
	sprite->addKeyframe(LF, glm::vec2(float(2) / 8.0f, 2 * 0.03571428571 * 3));
	
	sprite->addKeyframe(L1, glm::vec2(float(6) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L2, glm::vec2(float(5) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L3, glm::vec2(float(4) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L4, glm::vec2(float(3) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L5, glm::vec2(float(2) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L6, glm::vec2(float(1) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L7, glm::vec2(float(0) / 8.0f, 2 * 0.03571428571 * 2));
	
	sprite->addKeyframe(L8, glm::vec2(float(7) / 8.0f, 2 * 0.03571428571 * 3));
	
	sprite->addKeyframe(L9, glm::vec2(float(6) / 8.0f, 2 * 0.03571428571 * 3));
	
	sprite->addKeyframe(L10, glm::vec2(float(5) / 8.0f, 2 * 0.03571428571 * 3));
	
	sprite->addKeyframe(L11, glm::vec2(float(4) / 8.0f, 2 * 0.03571428571 * 3));
	
	sprite->addKeyframe(L12, glm::vec2(float(3) / 8.0f, 2 * 0.03571428571 * 3));

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
	if (numStep == 14) {
		sprite->changeAnimation(L1);
		
	}
	else if (numStep == 15) {
		sprite->changeAnimation(L2);
		
	}
	else if (numStep == 16) {
		sprite->changeAnimation(L3);
		
	}
	else if (numStep == 17) {
		sprite->changeAnimation(L4);
		
	}
	else if (numStep == 18) {
		sprite->changeAnimation(L5);
		
	}
	else if (numStep == 19) {
		sprite->changeAnimation(L6);
		
	}
	else if (numStep == 20) {
		sprite->changeAnimation(L7);
		
	}
	else if (numStep == 21) {
		sprite->changeAnimation(L8);
		
	}
	else if (numStep == 22) {
		sprite->changeAnimation(L9);
		
	}
	else if (numStep == 23) {
		sprite->changeAnimation(L10);
		
	}
	else if (numStep == 24) {
		sprite->changeAnimation(L11);
		
	}
	else if (numStep == 25) {
		sprite->changeAnimation(L12);
		
	}
	else if (numStep == 26) {
		sprite->changeAnimation(LF);
		
	}
	else if (numStep == 0) {
		sprite->changeAnimation(ZERO);
	}
}

void Ladder::changePos(glm::vec2 pos) {
	pos = pos - glm::vec2(3, 3);
	sprite->setPosition(pos);
}

void Ladder::update(int deltaTime){
	if (sprite->update(deltaTime) == 0)
		return;
}


void Ladder::render(int offsetX)
{
	sprite->render(0);
}