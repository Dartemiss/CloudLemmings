#ifndef _WINLOSE_INCLUDE
#define _WINLOSE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"
#include "Number.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class WinLose
{

public:
	WinLose();
	~WinLose();

	void init(int numNeed,int numSaved, bool win);
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	int accion;
	Quad * quad;
	Texture imgFondo,lemSpritesheet, imgCursor;
	Number lemN1, lemN0, lemS1, lemS0;
	TexturedQuad *fondo, *cursor;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;
	bool won;
	int nNeed, nSaved;

};


#endif // _WINLOSE_INCLUDE

