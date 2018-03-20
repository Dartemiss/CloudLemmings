#ifndef _SCENEAUX_INCLUDE
#define _SCENEAUX_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class SceneAux
{

public:
	SceneAux();
	~SceneAux();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	int accion;
	Quad * quad;
	Texture texs[2],imgFondo,imgCursor,imgPlay,imgPlaySelected;
	TexturedQuad *texQuad[3],*fondo,*cursor,*play;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENEAUX_INCLUDE

