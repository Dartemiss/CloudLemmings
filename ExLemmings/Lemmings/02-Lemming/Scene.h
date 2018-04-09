#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"
#include "Lemming.h"
#include "Ladder.h"
#include "ParticleSystem.h"
#include "Sprite.h"


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
	
	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton, bool bMiddleButton);
	void digging(int lem);
	int lemArrived();
	void bombed();

private:
	void initShaders();
	void give_skill(int mouseX, int mouseY, int skill);
	void eraseMaskX(int mouseX, int mouseY);
	void eraseMaskY(int mouseX, int mouseY);
	void applyMask(int mouseX, int mouseY);

	bool isOnLemming(int mouseX, int mouseY);

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
	Ladder ladder;
	Texture spritesheet,spritesheetLadder;
	bool deathbybomb;
	Sprite * sprite;
	ParticleSystem partSys;
	vector<ParticleSystem> particlesystems;
	float lastCurrentTime;
	bool onesec;
	Sprite * cursor;
	bool scloaded = false;


};


#endif // _SCENE_INCLUDE

