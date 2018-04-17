#include "Button.h"


void Button::init(int whichskill, int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet) {
	int frameY = 12;
	int frameX = 0;
	auxOffset = 0;
	id_skill = whichskill;
	if (whichskill == 0) {//UMBRELLA
		frameX = 0;
	}
	else if (whichskill == 1) {//DIGGER
		frameX = 2;
	}
	else if (whichskill == 2) {//BASHER
		frameX = 4;
	}
	else if (whichskill == 3) {//BLOCKER
		frameX = 6;
	}
	else if (whichskill == 4) {//CLIMBER
		frameX = 8;
	}
	else if (whichskill == 5) {//PORTAL CASTER
		frameX = 10;
	}
	else if (whichskill == 6) {//BUILDER
		frameX = 12;
	}

	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	//sprite->setAnimationSpeed(0, 12);

	sprite->addKeyframe(0, glm::vec2(frameX / 16.0f, 0.07142857143f * frameY / 2));
	int frameXd = frameX + 1;
	sprite->addKeyframe(1, glm::vec2(frameXd / 16.0f, 0.07142857143f * frameY / 2));

	sprite->changeAnimation(0);
	pos = glm::ivec2(x, y);
	sprite->setPosition(pos);
	posxx = pos.x;
	pressed = false;
}

void Button::update() {

	if (pressed) {
		sprite->changeAnimation(1);
	}
	else {
		if (id_skill != 5) {
			sprite->changeAnimation(0);
		}
	}
}

void Button::render(int offsetX) {
	if (offsetX != auxOffset) {
		pos.x = posxx + offsetX;
		auxOffset = offsetX;
	}
	sprite->render(0);
}

bool Button::isPressed(int mouseX, int mouseY) {
	if ((pos.y - 2 < mouseY) && (pos.y + 18 > mouseY)) {
		if ((pos.x + 5 < mouseX) && (pos.x + 18 > mouseX)) {
			pressed = true;
			return true;
		}
	}
	return false;
}


void Button::unPress() {
	pressed = false;
}