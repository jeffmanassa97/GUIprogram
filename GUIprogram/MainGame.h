#pragma once //protects from circular includes

#include <SDL/SDL.h> //opens a window
#include <GL/glew.h> //draws on the window

#include "GLSLProgram.h"

#include "Sprite.h"


enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame(); //constructor
	~MainGame(); //destructor

	void run();

	

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window; //(called a handle to the window) hold a pointer to the window, allows to resize, set screen width & heighth, and open it
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Sprite _sprite;

	GLSLProgram _colorProgram;

	float _time;
};

