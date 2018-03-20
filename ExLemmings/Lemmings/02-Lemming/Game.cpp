#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	gstate = 0;
	bLeftMouse = bRightMouse = false;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	//scene.init();
	sceneaux.init();
}

bool Game::update(int deltaTime)
{
	switch (gstate)
	{
	//Menu
	case 0:
		sceneaux.update(deltaTime);
		break;
	case 1:
		if (hasWon()) gstate = 0;
		scene.update(deltaTime);
		break;
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene.render();
	if(gstate == 0)sceneaux.render();
	else if (gstate == 1)scene.render();
}

void Game::initSc() {
	scene.init();
	gstate = 1;
}

void Game::newAction(int act) {
	if (act == 0) {
		sceneaux.init();
	}
	else if (act == 1) {
		initSc();
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	else if (key == '1')
		initSc();
	else if (key == '0')
		gstate = 0;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
	scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void Game::mousePress(int button)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void Game::mouseRelease(int button)
{
	if(button == GLUT_LEFT_BUTTON)
		bLeftMouse = false;
	else if(button == GLUT_RIGHT_BUTTON)
		bRightMouse = false;
}

bool Game::getKey(int key) const
{

	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::setSpecialKey(int key) {
	specialKeyReleased(key);
}

bool Game::hasWon()
{
	if (gstate == 1) {
		if (scene.lemArrived() == 10) {
			return true;
		}
		else return false;
	}
	else return false;
}





