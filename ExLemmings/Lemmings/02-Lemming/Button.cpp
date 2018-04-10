#include "Button.h"


void Button::init(int whichskill, int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet) {
	int frameY = 0;
	int frameX = 0;
	
	if (whichskill == 0) {//UMBRELLA
		frameY = 12;
		frameX = 0;
	}
	else if (whichskill == 1) {//DIGGER
		frameY = 12;
		frameX = 2;
	}
	else if (whichskill == 2) {//BASHER
		frameY = 12;
		frameX = 4;
	}
	else if (whichskill == 3) {//BLOCKER
		frameY = 12;
		frameX = 6;
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
	pressed = false;
}

void Button::update() {

	if (pressed) {
		sprite->changeAnimation(1);
	}
	else {
		sprite->changeAnimation(0);
	}
}

void Button::render() {
	sprite->render();
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