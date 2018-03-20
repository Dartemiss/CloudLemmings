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
	/*
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();
	quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, simpleProgram);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(0.5f, 0.5f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texCoords[0] = glm::vec2(0.5f, 0.5f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(2.f, 2.f);
	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	// Load textures
	texs[0].loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].loadFromFile("images/rocks.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	*/
	initShaders();
	currentTime = 0.0f;
	accion = 1;
	glm::vec2 geom[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(640.0f, 240.f) };
	glm::vec2 texCoords[2] = {glm::vec2(0.0f,0.0f),glm::vec2(1.0f,1.0f)};
	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	imgFondo.loadFromFile("images/keepitcutre.png", TEXTURE_PIXEL_FORMAT_RGBA);


	glm::vec2 geom3[2] = { glm::vec2(0.f, 0.f), glm::vec2(160.0f, 60.0f) };
	glm::vec2 texCoords3[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
	play = TexturedQuad::createTexturedQuad(geom3,texCoords3,texProgram);
	imgPlay.loadFromFile("images/play.png", TEXTURE_PIXEL_FORMAT_RGBA);
	imgPlaySelected.loadFromFile("images/playselected.png", TEXTURE_PIXEL_FORMAT_RGBA);
		
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
		accion += 1;
		accion = accion % 3;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)){
		Game::instance().setSpecialKey(GLUT_KEY_UP);
		accion += 2;
		accion = accion % 3;


	}
	if (accion == 0){


		//texto.render("Play ", glm::vec2(260, 380), 20, glm::vec4(1, 1, 1, 1));
		glm::vec2 geom3[2] = { glm::vec2(300.f, 170.f), glm::vec2(300 + 160.f, 170 + 60.0f) };
		glm::vec2 texCoords3[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		play = TexturedQuad::createTexturedQuad(geom3, texCoords3, texProgram);


		//texto.render("How to play ", glm::vec2(200, 420), 14, glm::vec4(1, 1, 1, 1));

		//texto.render("Credits ", glm::vec2(240, 460), 14, glm::vec4(1, 1, 1, 1));

		glm::vec2 geom2[2] = { glm::vec2(280.f, 170.f), glm::vec2(280 + 32.f, 170 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);

	}
	else if (accion == 1){

		//texto.render("Play ", glm::vec2(270, 380), 14, glm::vec4(1, 1, 1, 1));
		glm::vec2 geom3[2] = { glm::vec2(300.f, 210.f), glm::vec2(300 + 160.f, 210 + 60.0f) };
		glm::vec2 texCoords3[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		play = TexturedQuad::createTexturedQuad(geom3, texCoords3, texProgram);

		//texto.render("How to play ", glm::vec2(160, 420), 20, glm::vec4(1, 1, 1, 1));

		//texto.render("Credits ", glm::vec2(240, 460), 14, glm::vec4(1, 1, 1, 1));

		glm::vec2 geom2[2] = { glm::vec2(280.f, 210.f), glm::vec2(280 + 32.f, 210 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);

	}
	else if (accion == 2){


		//texto.render("Play ", glm::vec2(270, 380), 14, glm::vec4(1, 1, 1, 1));
		glm::vec2 geom3[2] = { glm::vec2(300.f, 250.f), glm::vec2(300 + 160.f, 250 + 60.0f) };
		glm::vec2 texCoords3[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		play = TexturedQuad::createTexturedQuad(geom3, texCoords3, texProgram);


		//texto.render("How to play ", glm::vec2(200, 420), 14, glm::vec4(1, 1, 1, 1));

		//texto.render("Credits ", glm::vec2(215, 460), 20, glm::vec4(1, 1, 1, 1));

		glm::vec2 geom2[2] = { glm::vec2(280.f, 250.f), glm::vec2(280 + 32.f, 250 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);

	}

	if(Game::instance().getKey(13)){
		Game::instance().newAction(accion);
	}
}

void SceneAux::render()
{
	/*

	glm::mat4 modelview;

	simpleProgram.use();
	simpleProgram.setUniformMatrix4f("projection", projection);
	simpleProgram.setUniform4f("color", 0.2f, 0.2f, 0.8f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(128.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	simpleProgram.setUniformMatrix4f("modelview", modelview);
	quad->render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(384.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(128.f, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[1]->render(texs[0]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(384.f, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[2]->render(texs[1]);
	*/


	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(imgFondo);

	if (accion == 0){


		//texto.render("Play ", glm::vec2(260, 380), 20, glm::vec4(1, 1, 1, 1));
		play->render(imgPlaySelected);
		//texto.render("How to play ", glm::vec2(220, 420), 14, glm::vec4(1, 1, 1, 1));

		//texto.render("Credits ", glm::vec2(250, 460), 14, glm::vec4(1, 1, 1, 1));


	}
	else if (accion == 1){

		//texto.render("Play ", glm::vec2(270, 380), 14, glm::vec4(1, 1, 1, 1));
		play->render(imgPlay);
		//texto.render("How to play ", glm::vec2(180, 420), 20, glm::vec4(1, 1, 1, 1));

		//texto.render("Credits ", glm::vec2(250, 460), 14, glm::vec4(1, 1, 1, 1));


	}
	else if (accion == 2){


		//texto.render("Play ", glm::vec2(270, 380), 14, glm::vec4(1, 1, 1, 1));
		play->render(imgPlay);
		//texto.render("How to play ", glm::vec2(220, 420), 14, glm::vec4(1, 1, 1, 1));

		//texto.render("Credits ", glm::vec2(220, 460), 20, glm::vec4(1, 1, 1, 1));


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

