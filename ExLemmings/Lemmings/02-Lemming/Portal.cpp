#include "Portal.h"


void Portal::init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet) {

	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 4);

	for (int i = 0; i < 4; i++)
		sprite->addKeyframe(0, glm::vec2(float(i) / 16.0f, 0.07142857143f * 15 / 2));

	sprite->changeAnimation(0);
	pos = glm::ivec2(x, y);
	sprite->setPosition(pos);
}

void Portal::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Portal::render() {
	sprite->render(0);
}

bool Portal::contact(int lemX, int lemY) {
	if ((pos.y - 2 < lemY) && (pos.y + 18 > lemY)) {
		if ((pos.x - 3 < lemX) && (pos.x + 18 > lemX)) {
			return true;
		}
	}
	return false;
}

glm::ivec2 Portal::getPos() {
	return pos;
}