#ifndef _SCENEAUX_INCLUDE
#define _SCENEAUX_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"
#include "fmod.hpp" //fmod c++ header
#pragma comment( lib, "fmod_vc.lib" ) // fmod library

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
	void silence();

private:
	void initShaders();

private:
	int accion;
	Quad * quad;
	Texture texs[2],imgFondo,imgCursor,imgPlay,imgPlaySelected,imgSkin,imgSkinSelected,imgCredits,imgCreditsSelected;
	TexturedQuad *texQuad[3],*fondo,*cursor,*play,*skin,*credits;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;

	//FMod Stuff
	FMOD::System     *system; //handle to FMOD engine
	FMOD::Sound      *sound1; //sound that will be loaded and played

};


#endif // _SCENEAUX_INCLUDE

