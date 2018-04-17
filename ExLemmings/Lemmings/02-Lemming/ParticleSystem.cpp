#include "ParticleSystem.h"



void ParticleSystem::init(int posX, int posY, ShaderProgram &shaderProgram, Texture &spritesheet) {
	howmanypart = 32;
	time_living = 0.0f;
	for (int i = 0; i < howmanypart; i++) {
		part.init(posX, posY, shaderProgram, spritesheet);
		particles.push_back(part);
	}

}

void ParticleSystem::update(int deltaTime) {
	time_living += deltaTime;
	for (int i = 0; i < howmanypart; i++) {
		particles[i].update(deltaTime);
	}
}

void ParticleSystem::render(int offsetX) {
	for (int i = 0; i < howmanypart; i++) {
		particles[i].render(offsetX);
	}
}

float ParticleSystem::get_time_living() {
	return time_living;
}