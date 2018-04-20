#include "Number.h"


void Number::init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet, int size) {

	sprite = Sprite::createSprite(glm::ivec2(size, size), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(11);
	//sprite->setAnimationSpeed(0, 4);

	for (int i = 0; i < 11; i++)
		sprite->addKeyframe(i, glm::vec2(float(i) / 16.0f, 0.07142857143f * 13 / 2));

	sprite->changeAnimation(0);
	pos = glm::ivec2(x, y);
	sprite->setPosition(pos);
	value = 0;
}

void Number::update() {
	sprite->changeAnimation(value);
}

void Number::render() {
	sprite->render(0);
}

void Number::diminish() {
	value -= 1;
	if (value < 0) value = 9;
}

void Number::setValue(int val) {
	value = val;
	update();
}

int Number::getValue() {
	return value;
}
glm::ivec2 Number::getPos() {
	return pos;
}