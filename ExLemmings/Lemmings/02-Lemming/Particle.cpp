#include "Particle.h"

//Aquesta classe gestiona el comportament de cada particula


void Particle::init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet) {
	acc.x = 0;
	acc.y = 0.1;
	vel.x = (rand() % 40 + -15)/10.0;
	vel.y = (rand() % 40 + -40)/10.0;
	pos.x = float(x);
	pos.y = float(y);
	color = rand() % 7 + 9;

	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 12);
	
	sprite->addKeyframe(0, glm::vec2(color / 16.0f, 0.07142857143f * 1 / 2));

	sprite->changeAnimation(0);
	glm::ivec2 pos = glm::ivec2(x, y);
	sprite->setPosition(pos);
}

void Particle::update(int deltaTime) {
	pos.x += vel.x;
	vel.x += acc.x;
	pos.y += vel.y;
	vel.y += acc.y;
	sprite->position() = glm::vec2(pos.x, pos.y);
}

void Particle::render() {
	sprite->render();
}