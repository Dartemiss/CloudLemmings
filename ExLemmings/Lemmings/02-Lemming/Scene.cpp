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


void Scene::init(int numlvl,int skin)
{
	initShaders();

	//INIT CLOCK
	for (int i = 0; i < 5; i++) {
		number.init(250 + i * 10, 157, simpleTexProgram, spritesheet);
		clock.push_back(number);
	}
	clock[2].setValue(10);
	clock[0].setValue(0);
	clock[1].setValue(3);
	clock[3].setValue(3);
	clock[4].setValue(7);

	//INIT GATES
	spritesheetGates.loadFromFile("images/enter_gate.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetGates.setMinFilter(GL_NEAREST);
	spritesheetGates.setMagFilter(GL_NEAREST);

	spritesheetGatesOut.loadFromFile("images/out_gate.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetGatesOut.setMinFilter(GL_NEAREST);
	spritesheetGatesOut.setMagFilter(GL_NEAREST);


	//LEVELS
	if (numlvl == 1) {
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH + 72), float(CAMERA_HEIGHT + 85 - 120/3)) }; //Mon
		glm::vec2 texCoords[2] = { glm::vec2(120.f / 512.0, 0.f), glm::vec2(1, 1) };
		map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
		colorTexture.loadFromFile("images/fun1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		maskTexture.loadFromFile("images/fun1_mask.png", TEXTURE_PIXEL_FORMAT_L);

		gate.init(glm::vec2(40, 10), simpleTexProgram, spritesheetGates, spritesheetGatesOut, true);
		gateOut.init(glm::vec2(200, 105), simpleTexProgram, spritesheetGates, spritesheetGatesOut, false);

		limitOffsetDreta = 0;
	}
	else if (numlvl == 2) {
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH+72), float(CAMERA_HEIGHT +85 - (120 / 3))) };
		glm::vec2 texCoords[2] = { glm::vec2(120.f / 512.0, 0.f), glm::vec2(1, 1) };
		map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
		colorTexture.loadFromFile("images/fun2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		maskTexture.loadFromFile("images/fun2_mask.png", TEXTURE_PIXEL_FORMAT_L);

		gate.init(glm::vec2(40, 10), simpleTexProgram, spritesheetGates, spritesheetGatesOut, true);
		gateOut.init(glm::vec2(245, 64), simpleTexProgram, spritesheetGates, spritesheetGatesOut, false);

		limitOffsetDreta = 0;
	}
	else if (numlvl == 3) {
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH+230), float(CAMERA_HEIGHT +85 - (120/3))) };
		glm::vec2 texCoords[2] = { glm::vec2(120.f / 668.0, 0.f), glm::vec2(1, 1) };
		map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
		colorTexture.loadFromFile("images/mayhem8.png", TEXTURE_PIXEL_FORMAT_RGBA);
		maskTexture.loadFromFile("images/mayhem8_mask.png", TEXTURE_PIXEL_FORMAT_L);

		gate.init(glm::vec2(40, 10), simpleTexProgram, spritesheetGates, spritesheetGatesOut, true);
		gateOut.init(glm::vec2(365, 124), simpleTexProgram, spritesheetGates, spritesheetGatesOut, false);

		limitOffsetDreta = 150;

	}
	else if (numlvl == 4) {
		glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH+487), float(CAMERA_HEIGHT +85 - (120 / 3))) };
		glm::vec2 texCoords[2] = { glm::vec2(120.f / 924.0, 0.f), glm::vec2(1, 1) };
		map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
		colorTexture.loadFromFile("images/tricky1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		maskTexture.loadFromFile("images/tricky1_mask.png", TEXTURE_PIXEL_FORMAT_L);

		gate.init(glm::vec2(40, 10), simpleTexProgram, spritesheetGates, spritesheetGatesOut, true);
		gateOut.init(glm::vec2(617, 90), simpleTexProgram, spritesheetGates, spritesheetGatesOut, false);

		limitOffsetDreta = 470;
	}

	// taxing 1
	//glm::vec2 texCoords[2] = { glm::vec2(120.f / 1227.0, 0.f), glm::vec2((120.f + 320.f) / 1227.0f, 160.f / 256.0f) };
	//tricky 1
	//glm::vec2 texCoords[2] = { glm::vec2(120.f / 924.0, 0.f), glm::vec2((120.f + 320.f) / 924.0f, 160.f / 256.0f) };
	//mayhem8
	//glm::vec2 texCoords[2] = { glm::vec2(120.f / 668.0, 0.f), glm::vec2((120.f + 320.f) / 668.0f, 160.f / 256.0f) };


	colorTexture.setMinFilter(GL_NEAREST);
	colorTexture.setMagFilter(GL_NEAREST);
	maskTexture.setMinFilter(GL_NEAREST);
	maskTexture.setMagFilter(GL_NEAREST);

	
	buttonBase.loadFromFile("images/button_base.png", TEXTURE_PIXEL_FORMAT_RGBA);
	buttonBase.setMinFilter(GL_NEAREST);
	buttonBase.setMagFilter(GL_NEAREST);
	gui = Sprite::createSprite(glm::ivec2(440, 220), glm::vec2(1.0f, 1.0f), &buttonBase, &simpleTexProgram);
	gui->setNumberAnimations(1);
	gui->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	gui->changeAnimation(0);
	gui->setPosition(glm::vec2(-60, 70));

	offsetX = 0;

	//INIT SOUND SYSTEM
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels

	system->createSound("Sounds/song.wav", FMOD_DEFAULT, 0, &sound1);
	sound1->setMode(FMOD_LOOP_NORMAL);


	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	if(skin == 1){
		spritesheet.loadFromFile("images/old/mirror_lemming_sayan.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else {
		spritesheet.loadFromFile("images/mirror_lemming.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	spritesheetLadder.loadFromFile("images/ladder.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetLadder.setMinFilter(GL_NEAREST);
	spritesheetLadder.setMagFilter(GL_NEAREST);
	

	
	lemmingsInGame = 10;
	howmanyButtons = 7;

	for (int i = 0; i < lemmingsInGame; i++) {
		lemming.init(glm::vec2(60, 30), simpleTexProgram, spritesheet, *system);
		lemming.setMapMask(&maskTexture);
		listOflemmings.push_back(lemming);
	}
	lastLemming = 0;
	howmanyLem = 0;
	allCreatedLemm = 0;
	deathbybomb = 0;
	wonLem = 0;
	deadLem = 0;
	requiredLemsToWin = 55;
	//ladder.init(glm::vec2(120,130), simpleTexProgram, spritesheetLadder);

	//posGate = glm::vec2(200, 122);


	cursor = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.07142857143 / 2.0), &spritesheet, &simpleTexProgram);
	cursor->setNumberAnimations(3);
	cursor->addKeyframe(0, glm::vec2(13 / 16.0f, 0.07142857143f * 2 / 2));
	cursor->addKeyframe(1, glm::vec2(12 / 16.0f, 0.07142857143f * 2 / 2));
	cursor->addKeyframe(2, glm::vec2(14 / 16.0f, 0.07142857143f * 2 / 2));
	cursor->changeAnimation(0);
	
	glm::ivec2 pos = glm::ivec2(-20, -20);
	cursor->setPosition(pos);
	scloaded = true;
	startbombing = 0.0f;

	loadedSkill = -1;

	
	for (int i = 0; i < howmanyButtons; i++) {
		button.init(i, 50 + i * 30, 171, simpleTexProgram, spritesheet);
		listOfButtons.push_back(button);
		
	}

	lastSecond = 0.0f;

	settingPortal = false;
	first_portalOn = second_portalOn = false;	
	

	system->playSound(sound1, FMOD_DEFAULT, false, 0);
	system->createSound("Sounds/0477.wav", FMOD_DEFAULT, 0, &sound2);
	system->createSound("Sounds/5463.wav", FMOD_DEFAULT, 0, &sound3);
	system->createSound("Sounds/5301.wav", FMOD_DEFAULT, 0, &sound4);
}

//unsigned int x = 0;

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	//cursor->update(deltaTime);
	clock[2].update();
	if (currentTime - lastSecond > 1000.0f) {
		lastSecond = currentTime;
		clock[4].diminish();
		clock[4].update();
		if (clock[4].getValue() == 9) {
			clock[3].diminish();
			clock[3].update();
			if (clock[3].getValue() == 9) {
				clock[3].setValue(5);
				clock[1].diminish();
				clock[1].update();
				if (clock[1].getValue() == 9) {
					clock[0].diminish();
					clock[0].update();
					if (clock[0].getValue() == 9) {
						//GAME LOST
						
					}
				}
			}
		}
	}
		
	if (deathbybomb == 0) { //No es creen mes lemmings un cop s'activa la bomba
		if (currentTime - lastLemming > 1500.0f && allCreatedLemm < lemmingsInGame) {
			lastLemming = currentTime;
			++howmanyLem;
			++allCreatedLemm;
			system->playSound(sound3, NULL, false, 0);

		}
	}


	for (int i = 0; i < howmanyLem; i++) {
		if (gateOut.isColliding(listOflemmings[i].getactualPos()) && listOflemmings[i].getState() != 7) {
			listOflemmings[i].change_state(7);
			++wonLem;
			listOflemmings[i].update(deltaTime);
		}
		if (listOflemmings[i].getState() == 1) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			eraseMaskY(pos.x, pos.y);
			listOflemmings[i].update(deltaTime);
			//offsetX += 1;
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
					ladder.changePos(pos + glm::vec2(8,0));
				else {
					pos -= glm::vec2(25, 1);
					ladder.changePos(pos);
					
				}
				ladder.changeSteps(0);
				listOfLadders.push_back(ladder);
				int s = listOfLadders.size() - 1;
				listOflemmings[i].setnumLadder(s);
			}
			listOflemmings[i].setnLadder(false);
			int aux = listOflemmings[i].getnumLadder();
			if (right) {
				applyMaskLadder(pos.x + 8, pos.y, step);
				listOfLadders[aux].changeSteps(step - 1);
				
					
			}
			else {
				applyMaskLadderLeft(pos.x, pos.y, step);
				listOfLadders[aux].changeSteps(13 + step);
				
			}
			listOflemmings[i].update(deltaTime);
		}
		else if (listOflemmings[i].getState() == 5 && !first_portalOn) {
			if (!first_portalOn) {
				glm::vec2 pos = listOflemmings[i].getLemPos();
				portal_first.init(pos.x-20, pos.y-5, simpleTexProgram, spritesheet);
				first_portalOn = true;
			}
			settingPortal = true;
			cursor->changeAnimation(2);
		}
		else if (listOflemmings[i].getState() == 9) {
			glm::vec2 auxpos = listOflemmings[i].getactualPos();
			proyectil.init(glm::vec2(auxpos.x + 10, auxpos.y), simpleTexProgram, spritesheet);
			listOfkames.push_back(proyectil);
			int aux = listOfkames.size();
			listOfkames[aux - 1].setMapMask(&maskTexture);
			listOflemmings[i].change_state(10);
			
		}
		else if (listOflemmings[i].hasDied()) {
			listOflemmings.erase(listOflemmings.begin() + i);
			//particlesystems.erase(particlesystems.begin() + i); Necessari?
			howmanyLem--;
			++deadLem;
		}
		else if (deathbybomb == 1 && listOflemmings[i].diedByBomb()) {
			//crear particle systems
			system->playSound(sound2, FMOD_DEFAULT, false, 0);
			for (int i = 0; i < howmanyLem; i++) {
				ParticleSystem aux;
				partSys = aux;
				glm::ivec2 pos = listOflemmings[i].getLemPos();
				partSys.init(pos.x, pos.y, simpleTexProgram, spritesheet);
				particlesystems.push_back(partSys);

			}
			deathbybomb = 2;
		}
		else if (listOflemmings[i].getState() == 3 && !listOflemmings[i].isBlocking()) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			applyMask(pos.x, pos.y);
			listOflemmings[i].update(deltaTime);
		}
		else if (deathbybomb == 1){
			//Actualitzar compte enrere:

			//Un cop passat compte enrere:
			if (listOflemmings[i].getState() != 52 && currentTime - timeBombStarted > 5000) {
				listOflemmings[i].change_state(52);
			}
			listOflemmings[i].update(deltaTime);
		}
		else if (deathbybomb == 2 && (particlesystems[i].get_time_living() < 6000)) {
			particlesystems[i].update(deltaTime);
		}
		else if (deathbybomb == 2 && (particlesystems[i].get_time_living() >= 6000)){
			listOflemmings.erase(listOflemmings.begin() + i);
			particlesystems.erase(particlesystems.begin() + i);
			howmanyLem--;
		}
		else if (first_portalOn && second_portalOn) {
			glm::ivec2 pos = listOflemmings[i].getLemPos();
			if (portal_first.contact(pos.x,pos.y)) {
				glm::ivec2 newPos = portal_second.getPos();
				listOflemmings[i].setPos(newPos);
			}
			listOflemmings[i].update(deltaTime);
		}
		else listOflemmings[i].update(deltaTime);


		if (howmanyLem == 0 && !first_portalOn)
			howmanyLem = -1;

	}

	gate.update(deltaTime);
	gateOut.update(deltaTime);
	for (int i = 0; i < howmanyButtons; i++) {
		listOfButtons[i].update();
	}

	if (first_portalOn) {
		portal_first.update(deltaTime);
	}
	if (second_portalOn) {
		portal_second.update(deltaTime);
	}

	for (int j = 0; j < listOfkames.size(); j++) {
		if (listOfkames[j].getState() == 1) {
			glm::vec2 aux = listOfkames[j].getPosition();
			eraseMaskBOOM(aux.x, aux.y);
			listOfkames.erase(listOfkames.begin() + j);
			
		}
		else listOfkames[j].update(deltaTime);
		
	}



	FMOD_RESULT a = system->update(); //update FMOD, need to call this once per frame to keep the sound engine running
	if (a != FMOD_OK) {
		int x = 3;
	}

}


void Scene::render()
{
	glm::mat4 modelview;

	maskedTexProgram.use();
	maskedTexProgram.setUniformMatrix4f("projection", projection);
	maskedTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//modelview = glm::mat4(1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(-offsetX, 0.0f, 0.f));
	maskedTexProgram.setUniformMatrix4f("modelview", modelview);
	map->render(maskedTexProgram, colorTexture, maskTexture);
	
	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//modelview = glm::mat4(1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(-offsetX, 0.0f, 0.f));
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);

	
	
	gateOut.render(offsetX);
	if (first_portalOn) {
		portal_first.render(offsetX);
	}
	if (second_portalOn) {
		portal_second.render(offsetX);
	}
	for (int i = 0; i < howmanyLem; i++) {
		//listOflemmings[i].render(offsetX);
		if (deathbybomb != 2) {
			listOflemmings[i].render(offsetX);
		}
		
		if (deathbybomb == 2 && (particlesystems[i].get_time_living() < 6000)) {
			particlesystems[i].render(offsetX);
		}	
	}
	gui->render(0);
	for (int i = 0; i < howmanyButtons; i++) {
		listOfButtons[i].render(offsetX);
		
	}
	

	cursor->render(0);
	gate.render(offsetX);

	for (int i = 0; i < listOfkames.size(); i++) {
		listOfkames[i].render(offsetX);
		
	}

	for (int i = 0; i < listOfLadders.size(); i++) {
		listOfLadders[i].render(offsetX);
	}

	for (int i = 0; i < 5; i++) {
		clock[i].render();
	}

}


int Scene::loadSkill(int mouseX, int mouseY) {
	int posX = mouseX / 3;
	int posY = mouseY / 3;
	for (int i = 0; i < howmanyButtons; i++) {
		if (listOfButtons[i].isPressed(posX, posY)) {
			system->playSound(sound4, FMOD_DEFAULT, false, 0);
			return i;
			
		}
		
	}
	return -1;
	
}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton, bool bMiddleButton){
	if (scloaded) {
		glm::ivec2 pos = glm::ivec2(mouseX / 3 - 11, mouseY / 3 - 7);
		int mouseOffX = mouseX + offsetX*3;
		cursor->setPosition(pos);
		if (isOnLemming(mouseOffX, mouseY)) {
			cursor->changeAnimation(1);
			
		}
		else if (!settingPortal) {
			cursor->changeAnimation(0);
			
		}
		else {
			cursor->changeAnimation(2);
		}

		if (bLeftButton) {
			if (!settingPortal) { //No portal
				if (loadedSkill != -1) {
					if (loadedSkill == 5) {
						if (!first_portalOn) {
							give_skill(mouseOffX, mouseY, loadedSkill);
						}
					}
					else {
						give_skill(mouseOffX, mouseY, loadedSkill);
					}
				}
				int skill = loadSkill(mouseOffX, mouseY);
				if (skill != -1) {
					if (loadedSkill != -1 && loadedSkill != skill) {
						listOfButtons[loadedSkill].unPress();
					}
					loadedSkill = skill;
				}
			}
			else {//Place portal
				int posX = mouseOffX / 3 - 10;
				int posY = mouseY / 3 - 8;
				glm::ivec2 pos_firstPortal = portal_first.getPos();
				if (posX - pos_firstPortal.x < 150) {
					portal_second.init(posX, posY, simpleTexProgram, spritesheet);
					second_portalOn = true;
					settingPortal = false;
				}
			}
		}
		else if (bRightButton) {
			//applyMask(mouseX, mouseY); 
			give_skill(mouseOffX, mouseY, 5);
		}
		else if (bMiddleButton) {
			give_skill(mouseOffX, mouseY, 8);
			
		}
		
	}
}

glm::vec2 Scene::getDeadsWins() {
	return glm::vec2(wonLem, requiredLemsToWin);
}

bool Scene::lemArrived()
{
	if(!first_portalOn){
		if (wonLem >= requiredLemsToWin && howmanyLem == -1)
			return true;
		return false;
	}
	else {
		if (wonLem >= requiredLemsToWin && howmanyLem == 0)
			return true;
		return false;
	}

}

bool Scene::lemEnded()
{
	if (!first_portalOn) {
		if (howmanyLem == -1)
			return true;
	}
	else {
		if (howmanyLem == 1)
			return true;
	}
	return false;
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
	bool justOneLemming = false;
	for (int i = 0; i < howmanyLem && !justOneLemming; i++) {
		glm::ivec2 pos = listOflemmings[i].getLemPos();
		bool xx = (pos.x + 5 < posMouse.x) && (pos.x + 15 > posMouse.x);
		bool yy = (pos.y - 12 < posMouse.y) && (pos.y + 12 > posMouse.y);
		//xx = yy = true;
		if(xx && yy) {
			if (listOflemmings[i].getState() == 3) { //If it was blocking, erase shield
				unApplyMask(pos.x, pos.y);
			}
			listOflemmings[i].change_state(skill);
			justOneLemming = true;
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
	

	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if(maskTexture.pixel(x,posY-1) != 1)
			maskTexture.setPixel(x, posY - 1, 0);
		
	}

	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY - 2) != 1)
			maskTexture.setPixel(x, posY - 2, 0);
	}
	
	if (maskTexture.pixel(posX, posY - 3) != 1)
		maskTexture.setPixel(posX, posY - 3, 0);
	
	for (int y = max(0, posY); y <= min(maskTexture.height() - 1, posY + 5); y++)
		for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
			if (maskTexture.pixel(x, y) != 1)
				maskTexture.setPixel(x, y, 0);
	
	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if (maskTexture.pixel(x, posY +6) != 1)
			maskTexture.setPixel(x, posY + 6, 0);
	
	}
	
	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY + 7) != 1)
			maskTexture.setPixel(x, posY + 7, 0);
		
	}
	
	if (maskTexture.pixel(posX, posY +8) != 1)
		maskTexture.setPixel(posX, posY + 8, 0);
	
}

void Scene::eraseMaskXLeft(int lemX, int lemY)
 {
	int posX = lemX + 125;
	int posY = lemY;
	
		
		
	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if (maskTexture.pixel(x, posY - 1) != 1)
			maskTexture.setPixel(x, posY - 1, 0);
		
	}
	
	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY - 2) != 1)
			maskTexture.setPixel(x, posY - 2, 0);
		
	}
	
	if (maskTexture.pixel(posX, posY - 1) != 1)
		maskTexture.setPixel(posX, posY - 3, 0);
	
	for (int y = max(0, posY); y <= min(maskTexture.height() - 1, posY + 5); y++)
		for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
			if (maskTexture.pixel(x, y) != 1)
				maskTexture.setPixel(x, y, 0);
	
	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if (maskTexture.pixel(x, posY + 6) != 1)
			maskTexture.setPixel(x, posY + 6, 0);
		
	}
	
	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY + 7) != 1)
			maskTexture.setPixel(x, posY + 7, 0);
		
	}
	
	if (maskTexture.pixel(posX, posY +8) != 1)
		maskTexture.setPixel(posX, posY + 8, 0);
	
}

void Scene::eraseMaskBOOM(int lemX, int lemY)
 {
	int posX = lemX + 130;
	int posY = lemY;
	
		
		
	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if (maskTexture.pixel(x, posY - 4) != 1)
			maskTexture.setPixel(x, posY - 4, 0);
		
	}
	
	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY - 5) != 1)
			maskTexture.setPixel(x, posY - 5, 0);
		
	}
	
	if (maskTexture.pixel(posX, posY - 3) != 1)
		maskTexture.setPixel(posX, posY - 3, 0);
	
	for (int y = max(0, posY - 3); y <= min(maskTexture.height() - 1, posY + 8); y++)
		for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
			if (maskTexture.pixel(x, y) != 1)
				maskTexture.setPixel(x, y, 0);
	
	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if (maskTexture.pixel(x, posY + 9) != 1)
			maskTexture.setPixel(x, posY + 9, 0);
		
	}
	
	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY + 10) != 1)
			maskTexture.setPixel(x, posY + 10, 0);
		
	}
	
	if (maskTexture.pixel(posX, posY + 11) != 1)
		maskTexture.setPixel(posX, posY + 11, 0);
	
}

void Scene::eraseMaskY(int lemX, int lemY)
{
	int posX = lemX + 130;
	int posY = lemY;

	for (int x = max(0, posX - 3); x <= min(maskTexture.width() - 1, posX + 3); x++)
		for (int y = max(0, posY - 3); y <= min(maskTexture.height() - 1, posY + 9); y++)
			if (maskTexture.pixel(x, y) != 1)
				maskTexture.setPixel(x, y, 0);

	for (int x = max(0, posX - 2); x <= min(maskTexture.width() - 1, posX + 2); x++) {
		if (maskTexture.pixel(x, posY + 10) != 1)
			maskTexture.setPixel(x, posY + 10, 0);
	}
	
	for (int x = max(0, posX - 1); x <= min(maskTexture.width() - 1, posX + 1); x++) {
		if (maskTexture.pixel(x, posY +11) != 1)
			maskTexture.setPixel(x, posY + 11, 0);
		
	}
	
	if (maskTexture.pixel(posX, posY + 12) != 1)
		maskTexture.setPixel(posX, posY + 12, 0);
}


void Scene::applyMask(int lemX, int lemY)
{
	int posX, posY;
	posX = lemX + 120;
	posY = lemY;

	for (int i = 0; i < 10; i++) {
		maskTexture.setPixel(posX+5,posY+i,1);
		maskTexture.setPixel(posX + 15, posY + i, 1);
	}
	for (int i = 0; i < 27; i++) {
		maskTexture.setPixel(posX-10 + i, posY - 2, 1);
	}
}

void Scene::unApplyMask(int lemX, int lemY)
{
	int posX, posY;
	posX = lemX + 120;
	posY = lemY;

	for (int i = 0; i < 10; i++) {
		maskTexture.setPixel(posX + 5, posY + i, 0);
		maskTexture.setPixel(posX + 15, posY + i, 0);
	}
	for (int i = 0; i < 27; i++) {
		maskTexture.setPixel(posX - 10 + i, posY - 2, 0);
	}
}

void Scene::applyMaskLadder(int ladX, int ladY,int step){
	int posX, posY;
	int offset = (step - 1) * 2;
	posX = ladX + 120 + offset + 1;
	posY = ladY - (step-1) + 11;

	for (int i = 0; i < 1; i++) {
		maskTexture.setPixel(posX + i, posY, 155);
	}
}

void Scene::applyMaskLadderLeft(int ladX, int ladY, int step) {
	int posX, posY;
	int offset = (step - 1) * 2;
	posX = ladX + 120 - offset + 6;
	posY = ladY - (step - 1) + 11;
		
	for (int i = 0; i < 1; i++) {
		maskTexture.setPixel(posX + i, posY, 155);
		
	}
	
}

void Scene::bombed()
{
	if (!deathbybomb) {
		timeBombStarted = currentTime;
		
		deathbybomb = 1;
		
	}
}

void Scene::setXoffset(int offset) {
	if ((offsetX + 4 * offset) >= 0 && (offsetX + 4 * offset) <= limitOffsetDreta) {
		offsetX += 4 * offset;
	}
	//glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH), float(CAMERA_HEIGHT - (120 / 3))) };
	//glm::vec2 texCoords[2] = { glm::vec2((offsetX+120.f) / 924.0, 0.f), glm::vec2((offsetX+120.f + 320.f) / 924.0f, 160.f / 256.0f) };
	//map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
}

void Scene::silence() {
	for (int i = 0; i < howmanyLem; i++) {
		listOflemmings[i].silence();
	}
	system->release();
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



