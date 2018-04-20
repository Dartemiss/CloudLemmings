#include "WinLose.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>



WinLose::WinLose()
{
	quad = NULL;
}


WinLose::~WinLose()
{
	if (quad != NULL)
		delete quad;

}

void WinLose::init(int numNeed, int numSaved, bool win)
{
	initShaders();
	currentTime = 0.0f;
	accion = 0;
	glm::vec2 geom[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(640.0f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f,0.0f),glm::vec2(1.0f,1.0f) };

	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	if (win) {
		imgFondo.loadFromFile("images/winscene.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else {
		imgFondo.loadFromFile("images/losescene.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}

	glm::vec2 geom2[2] = { glm::vec2(0.f, 0.f), glm::vec2(32.f, 32.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	imgCursor.loadFromFile("images/auxcursor.png", TEXTURE_PIXEL_FORMAT_RGBA);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	lemSpritesheet.loadFromFile("images/old/mirror_lemming_sayan.png", TEXTURE_PIXEL_FORMAT_RGBA);
	lemSpritesheet.setMinFilter(GL_NEAREST);
	lemSpritesheet.setMagFilter(GL_NEAREST);
	nNeed = numNeed;
	nSaved = numSaved;
	won = win;

	if (numNeed >= 10) {
		//lemN0.init(362, 154, texProgram, lemSpritesheet, 20);
		//lemN1.init(342, 154, texProgram, lemSpritesheet, 20);
		lemN0.init(520, 335, texProgram, lemSpritesheet, 40);
		lemN1.init(512, 335, texProgram, lemSpritesheet, 40);

		int der = numNeed % 10;
		int izq = int(numNeed / 10);
		lemN0.setValue(der);
		lemN1.setValue(izq);
	}
	else {
		//lemN0.init(362, 154, texProgram, lemSpritesheet, 20);
		lemN0.init(520, 335, texProgram, lemSpritesheet, 40);
		lemN0.setValue(numNeed);
	}

	if (numSaved >= 10) {
		//lemS0.init(362, 284, texProgram, lemSpritesheet, 20);
		//lemS1.init(342, 284, texProgram, lemSpritesheet, 20);
		lemS0.init(245, 335, texProgram, lemSpritesheet, 40);
		lemS1.init(235, 335, texProgram, lemSpritesheet, 40);

		int der = numSaved % 10;
		int izq = int(numSaved / 10);
		lemS0.setValue(der);
		lemS1.setValue(izq);
	}
	else {
		//lemS0.init(362, 284, texProgram, lemSpritesheet, 20);
		lemS0.init(235, 335, texProgram, lemSpritesheet, 40);
		lemS0.setValue(numSaved);
	}

}

void WinLose::update(int deltaTime) {
	currentTime += deltaTime;

	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		Game::instance().setSpecialKey(GLUT_KEY_RIGHT);
		accion += 1;
		accion = accion % 2;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		Game::instance().setSpecialKey(GLUT_KEY_LEFT);
		accion += 1;
		accion = accion % 2;
	}

	if (accion == 0) {


		glm::vec2 geom2[2] = { glm::vec2(290.f, 380.f), glm::vec2(290 + 32.f, 380 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);

	}
	else if (accion == 1) {

		glm::vec2 geom2[2] = { glm::vec2(420.f, 380.f), glm::vec2(420 + 32.f, 380 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);


	}

	if (Game::instance().getKey(13)) {
		if (won && accion == 0) {
			Game::instance().setLevel(1);
			Game::instance().newAction(1);
		}
		else if (accion == 0) {
			Game::instance().newAction(1);
		}
		else {
			Game::instance().newAction(0);
		}
	}
}

void WinLose::render()
{

	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(imgFondo);
	cursor->render(imgCursor);

	if (nNeed >= 10) {
		lemN0.render();
		lemN1.render();
	}
	else {
		lemN0.render();
	}

	if (nSaved >= 10) {
		lemS0.render();
		lemS1.render();
	}
	else {
		lemS0.render();
	}
}


void WinLose::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if (!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
}
