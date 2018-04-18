#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneAux.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>


SceneAux::SceneAux()
{
	quad = NULL;
}

SceneAux::~SceneAux()
{
	if (quad != NULL)
		delete quad;
	for (int i = 0; i<3; i++)
		if (texQuad[i] != NULL)
			delete texQuad[i];
}


void SceneAux::init()
{

	//INIT SOUND SYSTEM
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels

	system->createSound("Sounds/white_orchard.wav", FMOD_DEFAULT, 0, &sound1);
	sound1->setMode(FMOD_LOOP_NORMAL);
	system->playSound(sound1, FMOD_DEFAULT, false, 0);

	initShaders();
	currentTime = 0.0f;
	accion = 0;
	glm::vec2 geom[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(640.0f, 240.f) };
	glm::vec2 texCoords[2] = {glm::vec2(0.0f,0.0f),glm::vec2(1.0f,1.0f)};
	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	imgFondo.loadFromFile("images/keepitcutre.png", TEXTURE_PIXEL_FORMAT_RGBA);


	glm::vec2 geom3[2] = { glm::vec2(300.f, 200.f), glm::vec2(300 + 160.f, 200 + 60.0f) };
	play = TexturedQuad::createTexturedQuad(geom3,texCoords,texProgram);
	imgPlay.loadFromFile("images/play.png", TEXTURE_PIXEL_FORMAT_RGBA);
	imgPlaySelected.loadFromFile("images/playselected.png", TEXTURE_PIXEL_FORMAT_RGBA);

	glm::vec2 geom4[2] = { glm::vec2(300.f, 280.f), glm::vec2(300 + 160.f, 280 + 60.0f) };
	skin = TexturedQuad::createTexturedQuad(geom4, texCoords, texProgram);
	imgSkin.loadFromFile("images/skin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	imgSkinSelected.loadFromFile("images/skinselected.png", TEXTURE_PIXEL_FORMAT_RGBA);

	glm::vec2 geom5[2] = { glm::vec2(300.f, 360.f), glm::vec2(300 + 160.f, 360 + 60.0f) };
	credits = TexturedQuad::createTexturedQuad(geom5, texCoords, texProgram);
	imgCredits.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	imgCreditsSelected.loadFromFile("images/creditsselected.png", TEXTURE_PIXEL_FORMAT_RGBA);

		
	glm::vec2 geom2[2] = { glm::vec2(0.f, 0.f), glm::vec2(32.f, 32.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	imgCursor.loadFromFile("images/auxcursor.png", TEXTURE_PIXEL_FORMAT_RGBA);


	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void SceneAux::update(int deltaTime)
{
	currentTime += deltaTime;
	//accion = 1;
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)){
		Game::instance().setSpecialKey(GLUT_KEY_DOWN);
		accion += 2;
		accion = accion % 3;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)){
		Game::instance().setSpecialKey(GLUT_KEY_UP);
		accion += 1;
		accion = accion % 3;


	}
	if (accion == 0){


		glm::vec2 geom2[2] = { glm::vec2(280.f, 200.f), glm::vec2(280 + 32.f, 200 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);

	}
	else if (accion == 1){

		glm::vec2 geom2[2] = { glm::vec2(280.f, 360.f), glm::vec2(280 + 32.f, 360 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);


	}
	else if (accion == 2){


		glm::vec2 geom2[2] = { glm::vec2(280.f, 280.f), glm::vec2(280 + 32.f, 280 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);

	}

	if(Game::instance().getKey(13)){
		Game::instance().newAction(accion+1);
	}
}

void SceneAux::render()
{


	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(imgFondo);

	if (accion == 0){


		play->render(imgPlaySelected);
		skin->render(imgSkin);
		credits->render(imgCredits);

	}
	else if (accion == 1){

		play->render(imgPlay);
		skin->render(imgSkin);
		credits->render(imgCreditsSelected);
	}
	else if (accion == 2){

		play->render(imgPlay);
		skin->render(imgSkinSelected);
		credits->render(imgCredits);


	}

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	cursor->render(imgCursor);

}

void SceneAux::initShaders()
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

void SceneAux::silence() {
	system->release();
}


