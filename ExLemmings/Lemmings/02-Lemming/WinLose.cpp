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
	accion = 1;
	glm::vec2 geom[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(640.0f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.0f,0.0f),glm::vec2(1.0f,1.0f) };

	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	if (win) {
		imgFondo.loadFromFile("images/placeholderwin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else {
		imgFondo.loadFromFile("images/placeholderlose.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	lemSpritesheet.loadFromFile("images/old/mirror_lemming_sayan.png", TEXTURE_PIXEL_FORMAT_RGBA);
	lemSpritesheet.setMinFilter(GL_NEAREST);
	lemSpritesheet.setMagFilter(GL_NEAREST);
	nNeed = numNeed;
	nSaved = numSaved;
	won = win;

	if (numNeed >= 10) {
		lemN0.init(362, 154, texProgram, lemSpritesheet);
		lemN1.init(342, 154, texProgram, lemSpritesheet);

		int der = numNeed % 10;
		int izq = int(numNeed / 10);
		lemN0.setValue(der);
		lemN1.setValue(izq);
	}
	else {
		lemN0.init(362, 154, texProgram, lemSpritesheet);
		lemN0.setValue(numNeed);
	}

	if (numSaved >= 10) {
		lemS0.init(362, 284, texProgram, lemSpritesheet);
		lemS1.init(342, 284, texProgram, lemSpritesheet);

		int der = numSaved % 10;
		int izq = int(numSaved / 10);
		lemS0.setValue(der);
		lemS1.setValue(izq);
	}
	else {
		lemS0.init(362, 284, texProgram, lemSpritesheet);
		lemS0.setValue(numSaved);
	}

}

void WinLose::update(int deltaTime) {
	currentTime += deltaTime;

	if (Game::instance().getKey(13)) {
		if (won)
			Game::instance().setLevel(1);
		Game::instance().newAction(1);
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
