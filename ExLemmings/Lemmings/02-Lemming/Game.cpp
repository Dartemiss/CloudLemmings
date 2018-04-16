#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	gstate = 0;
	numLvl = 3;
	paused = false;
	fastmode = false;
	bLeftMouse = bRightMouse = bMiddleMouse = false;
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
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
		glutSetCursor(GLUT_CURSOR_NONE);
		if (hasWon()) {
			glm::vec2 aux = scene.getDeadsWins();
			winSc.init(aux.y, aux.x, true);
			gstate = 2;
		}
		else if (hasLost()) {
			glm::vec2 aux = scene.getDeadsWins();
			winSc.init(aux.y, aux.x, false);
			gstate = 2;
		}
		if (!paused) {
			if (fastmode) scene.update(deltaTime*2);
			else scene.update(deltaTime);	
		}
		break;
	case 2:
		winSc.update(deltaTime);
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene.render();
	if(gstate == 0)sceneaux.render();
	else if (gstate == 1)scene.render();
	else if (gstate == 2)winSc.render();
}

void Game::setLevel(int lvl) {
	numLvl = numLvl + lvl;
}

void Game::initSc() {
	Scene newSc;
	scene = newSc;
	scene.init(numLvl);
	gstate = 1;
}

void Game::newAction(int act) {
	if (act == 0) {
		sceneaux.init();
		gstate = 0;
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
	else if (key == 112 && !paused)
		paused = true;
	else if (key == 112 && paused)
		paused = false;
	else if (key == 102 && !fastmode)
		fastmode = true;
	else if (key == 102 && fastmode)
		fastmode = false;
	else if (key == 113)
		scene.bombed();
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
	scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, bMiddleMouse);
}

void Game::mousePress(int button)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, bMiddleMouse);
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, bMiddleMouse);
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		bMiddleMouse = true;
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse, bMiddleMouse);
	}
}

void Game::mouseRelease(int button)
{
	if(button == GLUT_LEFT_BUTTON)
		bLeftMouse = false;
	else if(button == GLUT_RIGHT_BUTTON)
		bRightMouse = false;
	else if (button == GLUT_MIDDLE_BUTTON)
		bMiddleMouse = false;
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
		if (scene.lemArrived()) {
			return true;
		}
		else return false;
	}
	else return false;
}

bool Game::hasLost()
{
	if (gstate == 1) {
		if (scene.lemEnded()) {
			return true;
		}
		else return false;
	}
	else return false;
}





