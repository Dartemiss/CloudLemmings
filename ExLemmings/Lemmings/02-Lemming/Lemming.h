#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "VariableTexture.h"
#include "fmod.hpp"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming
{

public:
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet, FMOD::System  &soundsystem);
	void update(int deltaTime);
	void render(int offsetX);
	
	void setMapMask(VariableTexture *mapMask);
	void change_state(int state);
	glm::ivec2 getLemPos();
	bool hasDied();
	int getState();
	bool isBlocking();
	int getbuilderStep();
	int builderStep;
	glm::vec2 pos;
	glm::vec2 getactualPos();
	bool nLadder;
	void setnumLadder(int s);
	void setnLadder(bool b);
	int getnumLadder();
	bool right;
	void setPos(glm::vec2 pos);
	bool diedByBomb();
	void silence();

private:
	int collisionFloor(int maxFall);
	int collisionWall(int maxFall);
	int collisionWallLeft(int maxFall);
	bool collision();
	bool collisionY();
	int lemFall;
	bool bDied;
	bool bBlocking;
	bool bclimbing;
	int numLadder;
	bool bDiedBomb;

private:
	enum LemmingState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE, DIGGING_STATE, OPEN_STATE,OPEN_STATE_LEFT, 
		FALLING_UMB_LEFT_STATE, FALLING_UMB_RIGHT_STATE, DYING_STATE, BLOCK_STATE, BASHER_STATE, DYING_BOMB_STATE, 
		CLIMBING_STATE, ARRIVING_CLIMB_STATE, BUILDER_STATE, BUILD_LADDER_STATE, WINNING_STATE, SUPER_STATE, TRANSFORM_STATE,
		BUILDER_LEFT_STATE, BASHER_LEFT_STATE,PORTAL_STATE
	};

	LemmingState state;
	Sprite *sprite;
	VariableTexture *mask;

	//FMod Stuff
	FMOD::System     *system; //handle to FMOD engine
	FMOD::Sound      *sound1, *sound2, *sound3; //sound that will be loaded and played

};


#endif // _LEMMING_INCLUDE


