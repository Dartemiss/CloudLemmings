#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "VariableTexture.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming
{

public:
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, Texture &spritesheet);
	void update(int deltaTime);
	void render();
	
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

private:
	int collisionFloor(int maxFall);
	int collisionWall(int maxFall);
	bool collision();
	bool collisionY();
	int lemFall;
	bool bDied;
	bool bBlocking;
	bool bclimbing;
	

private:
	enum LemmingState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE, DIGGING_STATE, OPEN_STATE, 
		FALLING_UMB_LEFT_STATE, FALLING_UMB_RIGHT_STATE, DYING_STATE, BLOCK_STATE, BASHER_STATE, DYING_BOMB_STATE, 
		CLIMBING_STATE, ARRIVING_CLIMB_STATE, BUILDER_STATE
	};

	LemmingState state;
	Sprite *sprite;
	VariableTexture *mask;

};


#endif // _LEMMING_INCLUDE


