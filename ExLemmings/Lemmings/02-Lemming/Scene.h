#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"
#include "Lemming.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	
	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);
	void digging(int lem);
	int lemArrived();

private:
	void initShaders();
	void give_skill(int mouseX, int mouseY);
	void eraseMask(int mouseX, int mouseY);
	void applyMask(int mouseX, int mouseY);

private:
	Texture colorTexture;
	VariableTexture maskTexture;
	MaskedTexturedQuad *map;
	ShaderProgram simpleTexProgram, maskedTexProgram;
	float currentTime;
	glm::mat4 projection;
	vector<Lemming> listOflemmings;
	float lastLemming;
	int howmanyLem;
	int lemmingsTotal;
	int allCreatedLemm;
	Lemming lemming;
	Texture spritesheet;


};


#endif // _SCENE_INCLUDE

