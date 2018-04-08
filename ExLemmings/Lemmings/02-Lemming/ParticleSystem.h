#pragma once
#include "Particle.h"

class ParticleSystem
{
public:
	void init(int x, int y, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update(int deltaTime);
	void render();
	float get_time_living();

private:
	int howmanypart;
	Particle part;
	vector<Particle> particles;
	float time_living;
};

