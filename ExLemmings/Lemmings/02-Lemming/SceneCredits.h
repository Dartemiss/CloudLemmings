#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"
class SceneCredits
{
public:
	SceneCredits();
	~SceneCredits();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	int accion;
	Quad * quad;
	Texture texs[2], imgFondo;
	TexturedQuad *texQuad[3], *fondo;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;
};

