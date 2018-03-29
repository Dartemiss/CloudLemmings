#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Lemming.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum LemmingAnims
{
	WALKING_LEFT, WALKING_RIGHT,OPEN_UMBRELLA,UMBRELLA
};


void Lemming::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	state = FALLING_RIGHT_STATE;
	//state = OPEN_UMBRELLA;
	spritesheet.loadFromFile("images/mirror_lemming.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	//sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.125, 0.5), &spritesheet, &shaderProgram);
	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.07142857143/2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(WALKING_RIGHT, 12);
		for(int i=0; i<8; i++)
			sprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16.0f, 0.07142857143f * 0));
		
		sprite->setAnimationSpeed(WALKING_LEFT, 12);
		for(int i=15; i>8; i--)
			sprite->addKeyframe(WALKING_LEFT, glm::vec2(float(i) / 16.0f, 0.5 + 0.07142857143f*0));

		sprite->setAnimationSpeed(OPEN_UMBRELLA, 12);
		for(int i=0; i<8; i++)
			sprite->addKeyframe(OPEN_UMBRELLA, glm::vec2(float(i) / 16.0f, 0.07142857143f * 2/2));
		
		sprite->setAnimationSpeed(UMBRELLA, 12);
		for (int i = 8; i<12; i++)
			sprite->addKeyframe(UMBRELLA, glm::vec2(float(i) / 16.0f, 0.07142857143f * 2 / 2));
		
	sprite->changeAnimation(WALKING_RIGHT);
	//sprite->changeAnimation(OPEN_UMBRELLA);
	sprite->setPosition(initialPosition);
}

void Lemming::update(int deltaTime)
{
	int fall;

	if(sprite->update(deltaTime) == 0)
		return;

	switch(state)
	{
	case FALLING_LEFT_STATE:
		fall = collisionFloor(2);
		if(fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else
			state = WALKING_LEFT_STATE;
		break;
	case FALLING_RIGHT_STATE:
		fall = collisionFloor(2);
		if(fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else
			//sprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		break;
	case WALKING_LEFT_STATE:
		sprite->position() += glm::vec2(-1, -1);
		if(collision())
		{
			sprite->position() -= glm::vec2(-1, -1);
			sprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		else
		{
			fall = collisionFloor(3);
			if(fall > 0)
				sprite->position() += glm::vec2(0, 1);
			if(fall > 1)
				sprite->position() += glm::vec2(0, 1);
			if(fall > 2)
				state = FALLING_LEFT_STATE;
		}
		break;
	case WALKING_RIGHT_STATE:
		sprite->position() += glm::vec2(1, -1);
		if(collision())
		{
			sprite->position() -= glm::vec2(1, -1);
			sprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		else
		{
			fall = collisionFloor(3);
			if(fall < 3)
				sprite->position() += glm::vec2(0, fall);
			else
				state = FALLING_RIGHT_STATE;
		}
		break;
	case OPEN_UMBRELLA:
		fall = collisionFloor(2);
		if (fall > 0) {
			sprite->position() += glm::vec2(0, fall);
			sprite->changeAnimation(UMBRELLA);
			state = UMBRELLA;
		}
		else {
			sprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		break;
	case UMBRELLA:
		fall = collisionFloor(2);
		if (fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else
			sprite->changeAnimation(WALKING_RIGHT);
		state = WALKING_RIGHT_STATE;
		break;
	}
}

void Lemming::render()
{
	sprite->render();
}

void Lemming::setMapMask(VariableTexture *mapMask)
{
	mask = mapMask;
}

glm::ivec2 Lemming::getLemPos()
{
	glm::ivec2 pos = sprite->position();
	return pos;
}

int Lemming::collisionFloor(int maxFall)
{
	bool bContact = false;
	int fall = 0;
	glm::ivec2 posBase = sprite->position() + glm::vec2(120, 0); // Add the map displacement
	
	posBase += glm::ivec2(7, 10);
	while((fall < maxFall) && !bContact)
	{
		if((mask->pixel(posBase.x, posBase.y+fall) == 0) && (mask->pixel(posBase.x+1, posBase.y+fall) == 0))
			fall += 1;
		else
			bContact = true;
	}

	return fall;
}

bool Lemming::collision()
{
	glm::ivec2 posBase = sprite->position() + glm::vec2(120, 0); // Add the map displacement
	
	posBase += glm::ivec2(7, 9);
	if((mask->pixel(posBase.x, posBase.y) == 0) && (mask->pixel(posBase.x+1, posBase.y) == 0))
		return false;

	return true;
}







