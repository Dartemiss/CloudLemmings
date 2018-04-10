#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "SceneAux.h"


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	void newAction(int act);
	void initSc();

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	void setSpecialKey(int key);

	bool hasWon();

private:
	bool bPlay;                       // Continue to play game?
	int gstate;
	bool paused;
	bool fastmode;
	Scene scene;                      // Scene to render
	SceneAux sceneaux;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int mouseX, mouseY;               // Mouse position
	bool bLeftMouse, bRightMouse, bMiddleMouse;     // Mouse button states

	enum gameState
	{
		MENU_STATE, PLAYING_STATE, INSTRUCTIONS_STATE, CREDITS_STATE
	};

};


#endif // _GAME_INCLUDE


