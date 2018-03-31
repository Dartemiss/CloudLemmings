#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	map = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
}


void Scene::init()
{
	glm::vec2 geom[2] = {glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH), float(CAMERA_HEIGHT))};
	glm::vec2 texCoords[2] = {glm::vec2(120.f / 512.0, 0.f), glm::vec2((120.f + 320.f) / 512.0f, 160.f / 256.0f)};

	initShaders();

	map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
	colorTexture.loadFromFile("images/fun9.png", TEXTURE_PIXEL_FORMAT_RGBA);
	colorTexture.setMinFilter(GL_NEAREST);
	colorTexture.setMagFilter(GL_NEAREST);
	maskTexture.loadFromFile("images/fun9_mask.png", TEXTURE_PIXEL_FORMAT_L);
	maskTexture.setMinFilter(GL_NEAREST);
	maskTexture.setMagFilter(GL_NEAREST);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	spritesheet.loadFromFile("images/mirror_lemming.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	for (int i = 0; i < 10; i++) {
		lemming.init(glm::vec2(60, 30), simpleTexProgram, spritesheet);
		lemming.setMapMask(&maskTexture);
		listOflemmings.push_back(lemming);
	}
	lastLemming = 0;
	howmanyLem = 0;
	allCreatedLemm = 0;
}

//unsigned int x = 0;

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (currentTime - lastLemming > 2000.0f && allCreatedLemm < 10) {
		lastLemming = currentTime;
		++howmanyLem;
		++allCreatedLemm;
	}
	for (int i = 0; i < howmanyLem; i++) {
		if (listOflemmings[i].getState() == 1) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			eraseMask(pos.x, pos.y);
		}
		else if (listOflemmings[i].hasDied()) {
			listOflemmings.erase(listOflemmings.begin() + i);
			howmanyLem--;
		}
		else if (listOflemmings[i].getState() == 3 && !listOflemmings[i].isBlocking()) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			applyMask(pos.x, pos.y);
		}
		listOflemmings[i].update(deltaTime);
	}

}

void Scene::render()
{
	glm::mat4 modelview;

	maskedTexProgram.use();
	maskedTexProgram.setUniformMatrix4f("projection", projection);
	maskedTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	maskedTexProgram.setUniformMatrix4f("modelview", modelview);
	map->render(maskedTexProgram, colorTexture, maskTexture);
	
	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);
	

	for (int i = 0; i < howmanyLem; i++) {
		listOflemmings[i].render();
	}

}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton, bool bMiddleButton)
{
	if (bLeftButton) {
		//eraseMask(mouseX, mouseY);
		give_skill(mouseX, mouseY, 1);
	}
	else if (bRightButton) {
		//applyMask(mouseX, mouseY); 
		give_skill(mouseX, mouseY, 0);
	}
	else if (bMiddleButton) {
		give_skill(mouseX, mouseY, 3);
	}
}

int Scene::lemArrived()
{
	for (int i = 0; i < howmanyLem; i++) {
		glm::ivec2 pos = listOflemmings[i].getLemPos();
		if (pos.x > 200) {
			++lemmingsTotal;
			listOflemmings.erase(listOflemmings.begin() + i);
			howmanyLem--;
		}
	}
	return lemmingsTotal;
}

void Scene::digging(int lem) {
	glm::ivec2 pos = listOflemmings[lem].getLemPos();
	if (pos.x > 100) {
		
	}
}

void Scene::give_skill(int mouseX, int mouseY, int skill) {
	int posX, posY;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	posX = mouseX / 3;
	posY = mouseY / 3;

	glm::ivec2 posMouse = glm::ivec2(posX, posY);
	for (int i = 0; i < howmanyLem; i++) {
		glm::ivec2 pos = listOflemmings[i].getLemPos();
		bool xx = (pos.x - 12 < posMouse.x) && (pos.x + 12 > posMouse.x);
		bool yy = (pos.y - 12 < posMouse.y) && (pos.y + 12 > posMouse.y);
		//xx = yy = true;
		if(xx && yy) {
			listOflemmings[i].change_state(skill);
		}
	}
}


void Scene::eraseMask(int lemX, int lemY)
{
	int posX = lemX + 130;
	int posY = lemY;
	
	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;
	for (int i = 0; i < 7; ++i) {
		for (int y = max(0, posY - 3); y <= min(maskTexture.height() - 1, posY + 3); y++)
			for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
				maskTexture.setPixel(x, y, 0);

		++posY;
	}
}

void Scene::applyMask(int lemX, int lemY)
{
	int posX, posY;
	posX = lemX + 120;
	posY = lemY;
	
	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;

	/*for(int y=max(0, posY-3); y<=min(maskTexture.height()-1, posY+3); y++)
		for(int x=max(0, posX-3); x<=min(maskTexture.width()-1, posX+3); x++)
			maskTexture.setPixel(x, y, 255);*/

	for (int i = 0; i < 10; i++) {
		maskTexture.setPixel(posX+5,posY+i,1);
		maskTexture.setPixel(posX + 15, posY + i, 1);
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	if(!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();

	vShader.initFromFile(VERTEX_SHADER, "shaders/maskedTexture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/maskedTexture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	maskedTexProgram.init();
	maskedTexProgram.addShader(vShader);
	maskedTexProgram.addShader(fShader);
	maskedTexProgram.link();
	if(!maskedTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << maskedTexProgram.log() << endl << endl;
	}
	maskedTexProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



