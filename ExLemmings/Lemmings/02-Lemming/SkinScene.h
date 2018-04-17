#pragma once

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"
class SkinScene
{
public:
	SkinScene();
	~SkinScene();
	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	int accion;
	Quad * quad;
	Texture texs[2], imgFondo, imgCursor;
	TexturedQuad *texQuad[3], *fondo, *cursor;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;
};

