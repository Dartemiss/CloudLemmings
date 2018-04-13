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
	glm::vec2 texCoords[2] = { glm::vec2(120.f / 512.0, 0.f), glm::vec2((120.f + 320.f) / 512.0f, 160.f / 256.0f) };

	initShaders();

	map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
	colorTexture.loadFromFile("images/fun2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	colorTexture.setMinFilter(GL_NEAREST);
	colorTexture.setMagFilter(GL_NEAREST);
	maskTexture.loadFromFile("images/fun2_mask.png", TEXTURE_PIXEL_FORMAT_L);
	maskTexture.setMinFilter(GL_NEAREST);
	maskTexture.setMagFilter(GL_NEAREST);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	spritesheet.loadFromFile("images/old/mirror_lemming_sayan.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	spritesheetLadder.loadFromFile("images/ladder.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetLadder.setMinFilter(GL_NEAREST);
	spritesheetLadder.setMagFilter(GL_NEAREST);
	
	spritesheetGates.loadFromFile("images/enter_gate.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetGates.setMinFilter(GL_NEAREST);
	spritesheetGates.setMagFilter(GL_NEAREST);

	spritesheetGatesOut.loadFromFile("images/out_gate.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetGatesOut.setMinFilter(GL_NEAREST);
	spritesheetGatesOut.setMagFilter(GL_NEAREST);
	

	for (int i = 0; i < 10; i++) {
		lemming.init(glm::vec2(60, 30), simpleTexProgram, spritesheet);
		lemming.setMapMask(&maskTexture);
		listOflemmings.push_back(lemming);
	}
	lastLemming = 0;
	howmanyLem = 0;
	allCreatedLemm = 0;
	deathbybomb = 0;
	//ladder.init(glm::vec2(120,130), simpleTexProgram, spritesheetLadder);
	gate.init(glm::vec2(40, 10), simpleTexProgram, spritesheetGates, spritesheetGatesOut,true);
	gateOut.init(glm::vec2(200, 122), simpleTexProgram, spritesheetGates, spritesheetGatesOut, false);
	//proyectil.init(glm::vec2(100, 100), simpleTexProgram, spritesheet);

	posGate = glm::vec2(200, 122);

	//listOfLadders.push_back(ladder);

	cursor = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &simpleTexProgram);
	cursor->setNumberAnimations(2);
	//cursor->setAnimationSpeed(0, 12);
		
	cursor->addKeyframe(0, glm::vec2(13 / 16.0f, 0.07142857143f * 2 / 2));
	cursor->addKeyframe(1, glm::vec2(12 / 16.0f, 0.07142857143f * 2 / 2));
	
	cursor->changeAnimation(0);
	
	glm::ivec2 pos = glm::ivec2(-20, -20);
	cursor->setPosition(pos);
	scloaded = true;

	startbombing = 0.0f;

	loadedSkill = -1;
	howmanyButtons = 4;
	
	for (int i = 0; i < howmanyButtons; i++) {
		button.init(i, 30 + i * 30, 130, simpleTexProgram, spritesheet);
		listOfButtons.push_back(button);
		
	}
}

//unsigned int x = 0;

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	//cursor->update(deltaTime);
		
		
	if (deathbybomb == 0) { //No es creen mes lemmings un cop s'activa la bomba
		if (currentTime - lastLemming > 2000.0f && allCreatedLemm < 10) {
			lastLemming = currentTime;
			++howmanyLem;
			++allCreatedLemm;

		}
	}


	for (int i = 0; i < howmanyLem; i++) {
		if (listOflemmings[i].getLemPos().x == posGate.x + 11000 && !listOflemmings[i].isWinning()) {
			listOflemmings[i].change_state(7);
		}
		if (listOflemmings[i].getState() == 1) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			eraseMaskY(pos.x, pos.y);
			listOflemmings[i].update(deltaTime);
		}
		else if (listOflemmings[i].getState() == 2) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			if (listOflemmings[i].right) {
				eraseMaskX(pos.x, pos.y);
			}
			else {
				eraseMaskXLeft(pos.x, pos.y);
			}
			listOflemmings[i].update(deltaTime);
		}
		else if (listOflemmings[i].getState() == 6) {
			int step = listOflemmings[i].getbuilderStep();
			bool right = listOflemmings[i].right;
			glm::vec2 pos = listOflemmings[i].pos;
			if (listOflemmings[i].nLadder){
				ladder.init(glm::vec2(120, 130), simpleTexProgram, spritesheetLadder);
				if (right)
					ladder.changePos(pos);
				else {
					pos -= glm::vec2(25, 1);
					ladder.changePos(pos);
				}
				listOfLadders.push_back(ladder);
				int s = listOfLadders.size() - 1;
				listOflemmings[i].setnumLadder(s);
				
			}
			listOflemmings[i].setnLadder(false);
			int aux = listOflemmings[i].getnumLadder();
			if (right) {
				applyMaskLadder(pos.x, pos.y, step);
				listOfLadders[aux].changeSteps(step -1);
				
			}
			else {
				applyMaskLadderLeft(pos.x, pos.y, step);
				listOfLadders[aux].changeSteps(13 + step);
			}
			listOflemmings[i].update(deltaTime);
		}
		else if (listOflemmings[i].getState() == 9) { 
			glm::vec2 auxpos = listOflemmings[i].getactualPos();
			proyectil.init(glm::vec2(auxpos.x + 10,auxpos.y), simpleTexProgram, spritesheet);
			listOfkames.push_back(proyectil);
			int aux = listOfkames.size();
			listOfkames[aux-1].setMapMask(&maskTexture);
			listOflemmings[i].change_state(10);
		}
		else if (listOflemmings[i].hasDied()) {
			listOflemmings.erase(listOflemmings.begin() + i);
			howmanyLem--;
		}
		else if (listOflemmings[i].getState() == 3 && !listOflemmings[i].isBlocking()) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			applyMask(pos.x, pos.y);
			listOflemmings[i].update(deltaTime);
		}
		else if (deathbybomb != 0 && (particlesystems[i].get_time_living() < 6000)) {
			//listOflemmings[i].change_state(2); ha de fer l'animacio del tembleque
			//listOflemmings[i].update(deltaTime);
			particlesystems[i].update(deltaTime);
			listOflemmings[i].update(deltaTime);
		}
	 /*else if (deathbybomb) {
				
			for (int j = 0; j < howmanyLem; j++) {
				int a = 3;
				particlesystems.erase(particlesystems.begin() + j);
				}
			}*/
		else listOflemmings[i].update(deltaTime);

	}

	gate.update(deltaTime);
	gateOut.update(deltaTime);
	for (int j = 0; j < listOfkames.size();j++) {
		if (listOfkames[j].getState()== 1) {
			glm::vec2 aux = listOfkames[j].getPosition();
			eraseMaskBOOM(aux.x, aux.y);
			listOfkames.erase(listOfkames.begin() + j);
		}
		else listOfkames[j].update(deltaTime);
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
	
	gateOut.render();
	for (int i = 0; i < howmanyLem; i++) {
		listOflemmings[i].render();
		if (deathbybomb != 0 && (particlesystems[i].get_time_living() < 6000)) {
			particlesystems[i].render();
			
		}
		
	}

	for (int i = 0; i < howmanyButtons; i++) {
		listOfButtons[i].render();
		
	}


	cursor->render();
	gate.render();
	//proyectil.render();
	
	for (int i = 0; i < listOfkames.size(); i++) {
		listOfkames[i].render();
	}


	for (int i = 0; i < listOfLadders.size(); i++) {

		listOfLadders[i].render(); 
	}

}


int Scene::loadSkill(int mouseX, int mouseY) {
	int posX = mouseX / 3;
	int posY = mouseY / 3;
	for (int i = 0; i < howmanyButtons; i++) {
		if (listOfButtons[i].isPressed(posX, posY)) {
			return i;
			
		}
		
	}
	return -1;
	
}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton, bool bMiddleButton){
	if (scloaded) {
		glm::ivec2 pos = glm::ivec2(mouseX / 3 - 11, mouseY / 3 - 7);
		cursor->setPosition(pos);
		if (isOnLemming(mouseX, mouseY)) {
			cursor->changeAnimation(1);
			
		}
		else {
			cursor->changeAnimation(0);
			
		}
		
			if (bLeftButton) {
			if (loadedSkill != -1) {
				give_skill(mouseX, mouseY, loadedSkill);
				
			}
			int skill = loadSkill(mouseX, mouseY);
			if (skill != -1) {
				if (loadedSkill != -1 && loadedSkill != skill) {
					listOfButtons[loadedSkill].unPress();
					
				}
				loadedSkill = skill;
				
			}
			
		}
		else if (bRightButton) {
						//applyMask(mouseX, mouseY); 
				give_skill(mouseX, mouseY, 0);
			
		}
		else if (bMiddleButton) {
			give_skill(mouseX, mouseY, 8);
			
		}
		
	}
}

int Scene::lemArrived()
{
	for (int i = 0; i < howmanyLem; i++) {
		glm::ivec2 pos = listOflemmings[i].getLemPos();
		if (pos.x > 400) {
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
		bool xx = (pos.x + 5 < posMouse.x) && (pos.x + 15 > posMouse.x);
		bool yy = (pos.y - 12 < posMouse.y) && (pos.y + 12 > posMouse.y);
		//xx = yy = true;
		if(xx && yy) {
			listOflemmings[i].change_state(skill);
		}
	}
}

bool Scene::isOnLemming(int mouseX, int mouseY) {
	int posX, posY;
	
	posX = mouseX / 3;
	posY = mouseY / 3;
	
	glm::ivec2 posMouse = glm::ivec2(posX, posY);
	for (int i = 0; i < howmanyLem; i++) {
		glm::ivec2 pos = listOflemmings[i].getLemPos();
		bool xx = (pos.x + 5 < posMouse.x) && (pos.x + 16 > posMouse.x);
		bool yy = (pos.y - 5 < posMouse.y) && (pos.y + 12 > posMouse.y);
		if (xx && yy) {
			return true;
			
		}
		
	}
	return false;
	
}


void Scene::eraseMaskX(int lemX, int lemY)
{
	int posX = lemX + 130;
	int posY = lemY;
	
	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;
		
		
	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY - 1, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY - 2, 0);
	}
	

	maskTexture.setPixel(posX, posY - 3, 0);

	for (int y = max(0, posY); y <= min(maskTexture.height() - 1, posY + 5); y++)
		for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
			maskTexture.setPixel(x, y, 0);

	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY + 6, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY + 7, 0);
	}


	maskTexture.setPixel(posX, posY + 8, 0);

}

void Scene::eraseMaskXLeft(int lemX, int lemY)
{
	int posX = lemX + 125;
	int posY = lemY;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;


	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY - 1, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY - 2, 0);
	}


	maskTexture.setPixel(posX, posY - 3, 0);

	for (int y = max(0, posY); y <= min(maskTexture.height() - 1, posY + 5); y++)
		for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
			maskTexture.setPixel(x, y, 0);

	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY + 6, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY + 7, 0);
	}


	maskTexture.setPixel(posX, posY + 8, 0);

}


void Scene::eraseMaskBOOM(int lemX, int lemY)
{
	int posX = lemX + 130;
	int posY = lemY;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;


	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY - 4, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY - 5, 0);
	}


	maskTexture.setPixel(posX, posY - 3, 0);

	for (int y = max(0, posY - 3); y <= min(maskTexture.height() - 1, posY + 8); y++)
		for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
			maskTexture.setPixel(x, y, 0);

	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY + 9, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY + 10, 0);
	}


	maskTexture.setPixel(posX, posY + 11, 0);

}

void Scene::eraseMaskY(int lemX, int lemY)
{
	int posX = lemX + 130;
	int posY = lemY;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;

	for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
		for (int y = max(0, posY - 3); y <= min(maskTexture.height() - 1, posY + 9); y++)
			maskTexture.setPixel(x, y, 0);

	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		maskTexture.setPixel(x, posY + 10, 0);
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		maskTexture.setPixel(x, posY + 11, 0);
	}


	maskTexture.setPixel(posX, posY + 12, 0);
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

void Scene::applyMaskLadder(int ladX, int ladY,int step){
	int posX, posY;
	int offset = (step - 1) * 2;
	posX = ladX + 120 + offset + 1;
	posY = ladY - (step-1) + 11;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;

	/*for(int y=max(0, posY-3); y<=min(maskTexture.height()-1, posY+3); y++)
	for(int x=max(0, posX-3); x<=min(maskTexture.width()-1, posX+3); x++)
	maskTexture.setPixel(x, y, 255);*/

	for (int i = 0; i < 1; i++) {
		maskTexture.setPixel(posX + i, posY, 155);
	}
}

void Scene::applyMaskLadderLeft(int ladX, int ladY, int step) {
	int posX, posY;
	int offset = (step - 1) * 2;
	posX = ladX + 120 - offset + 6;
	posY = ladY - (step - 1) + 11;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	//posX = mouseX/3 + 120;
	//posY = mouseY/3;

	/*for(int y=max(0, posY-3); y<=min(maskTexture.height()-1, posY+3); y++)
	for(int x=max(0, posX-3); x<=min(maskTexture.width()-1, posX+3); x++)
	maskTexture.setPixel(x, y, 255);*/

	for (int i = 0; i < 1; i++) {
		maskTexture.setPixel(posX + i, posY, 155);
	}
}

void Scene::bombed()
{
	if (!deathbybomb) {
			//crear particle system
			for (int i = 0; i < howmanyLem; i++) {
				ParticleSystem aux;
				partSys = aux;
				glm::ivec2 pos = listOflemmings[i].getLemPos();
				partSys.init(pos.x, pos.y, simpleTexProgram, spritesheet);
				particlesystems.push_back(partSys);
			
		}
		deathbybomb = 1;
		
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



