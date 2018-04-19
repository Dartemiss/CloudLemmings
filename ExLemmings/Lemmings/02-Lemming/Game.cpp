#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	gstate = 0;
	numLvl = 1;
	skin = 0;
	paused = false;
	fastmode = false;
	bLeftMouse = bRightMouse = bMiddleMouse = false;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//scene.init();
	sceneaux.init();
	sceneskin.init();
	scenecredits.init();
	scenehelp.init();
}

bool Game::update(int deltaTime)
{
	switch (gstate)
	{
		//Menu
	case 0:
		glutSetCursor(GLUT_CURSOR_INHERIT);
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
			if (fastmode) scene.update(deltaTime * 2);
			else scene.update(deltaTime);
		}
		break;
	case 2:
		winSc.update(deltaTime);
		break;
	case 3:
		sceneskin.update(deltaTime);
		break;
	case 4:
		scenecredits.update(deltaTime);
		break;
	case 5:
		scenehelp.update(deltaTime);
		break;
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(gstate == 0)sceneaux.render();
	else if (gstate == 1)scene.render();
	else if (gstate == 2)winSc.render();
	else if (gstate == 3)sceneskin.render();
	else if (gstate == 4)scenecredits.render();
	else if (gstate == 5)scenehelp.render();
}

void Game::setLevel(int lvl) {
	numLvl = numLvl + lvl;
}

void Game::initSc() {
	Scene newSc;
	scene = newSc;
	scene.init(numLvl,skin);
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
	else if (act == 2) {
		gstate = 3;
	}
	else if (act == 3) {
		gstate = 4;
	}
	else if (act == 4) {
		gstate = 5;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	else if (key == '1') {
		if (gstate == 0) {
			sceneaux.silence();
			numLvl = 1;
			initSc();
		}
	}
	else if (key == '2') {
		if (gstate == 0) {
			sceneaux.silence();
			numLvl = 2;
			initSc();
		}
	}
	else if (key == '3') {
		if (gstate == 0) {
			sceneaux.silence();
			numLvl = 3;
			initSc();
		}
	}
	else if (key == '4') {
		if (gstate == 0) {
			sceneaux.silence();
			numLvl = 4;
			initSc();
		}
	}
	else if (key == '0') {
		if (gstate != 0) {
			scene.silence();
			sceneaux.init();
			gstate = 0;
		}
	}
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
	else if (key == 'a' && gstate == 1)
		scene.setXoffset(-1);
	else if (key == 'd' && gstate == 1)
		scene.setXoffset(1);
	else if (key == 13 && gstate == 3) {
		int act = sceneskin.getAction();
		setSkin(act);
		newAction(0);
	}
	else if (key == 13 && gstate == 5) {
		newAction(0);
	}
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

void Game::setSkin(int s) {
	skin = s;
	gstate = 0;
}




