#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>
//initialize everything in MainGame.h



MainGame::MainGame() : 
	_screenWidth(1024), //initialization list
	_screenHeight(768), 
	_time(0.0f), //begin time at zero
	_window(nullptr), 
	_gameState(GameState::PLAY) //scope resoltuion operator, and constructor definition
{

}


MainGame::~MainGame()
{
}


void MainGame::run() {
	initSystems(); //open the window and get SDL and OpenGL, all set up with errors, background color, etc.

	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	gameLoop(); //processes Input, and draws the game
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL (everything in SDL)

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); //opens SDL window, takes care of all operating specific stuff, returns a pointer to a window, if it fails to create a window it will send a nullptr
	if (_window == nullptr) {
		fatalError("SDL Window could not be created!"); //error check
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window); //creating an OpenGL context, stores all of the OpenGL related things like textures, vertex buffer objects, etc.
	if (glContext == nullptr) { //error check
		fatalError("SDL_GL context could not be created!");
	}
	//GLenum is like an error code
	GLenum error = glewInit(); //initializes glew, get all extensions set up, if your hardware doesn't suppport everything then this will take care of that (optional but recommended)
	if (error != GLEW_OK) { //if didn't initialize glew
		fatalError("Could not initialize glew!");
	}
	//tells SDL to double buffer(window), allowing one window to be drawn to while the other one is being cleared, keeps the window from flickering, which requires SWAP function to swap windows
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//0, 0, 0 is black. 1, 1, 1 is white. Percentage of colors called, 0.0f bc/ it's floats
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //everytime GL_COLOR_BUFFER_BIT is called in drawGame(), it clears the color to this color

	initShaders();
}

void MainGame::initShaders() { //set up our color program, compile it, link it
	_colorProgram.compileShaders("Shaders/colorShading.vert.txt", "Shaders/colorShading.frag.txt");
	_colorProgram.addAttribute("vertexPosition"); //all inside NotePad++ GLSL
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	//Will loop until setting _gameState to EXIT, constatnly drawing and clearing buffers
	while (_gameState != GameState::EXIT) { //will never return until the game state equals EXIT
		processInput();
		_time += 0.003; //incrimentation of time
		drawGame();
	}
}
void MainGame::processInput() {
	SDL_Event evnt;
	
	//&evnt makes it a pointer
	while (SDL_PollEvent(&evnt)) { //checks if there is an event
		switch (evnt.type) {//from SDL library for SDL_Event, google it
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl; //tracks mouse movement
				break;
		}
	} //asks the operating system what events to process, where the mouse has been moving over or typing in. While(1) is true. While(0) is false
}

void MainGame::drawGame() {
	
	glClearDepth(1.0); //tells OpenGL what depth it should clear to
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the screen/ depth and color buffer, each time you draw the game you want to clear your color and depth buffer. One vertical line "|" is combine, called the bitwise operator

	_colorProgram.use();

	GLuint timeLocation = _colorProgram.getUniformLocation("time"); //gets the uniform location for time
	//will send the time variable unifrom to the graphics card,
	glUniform1f(timeLocation, _time); //type on the end is 1f or one float; (ie. 3v, v is vector or array)

	//Draws the sprite
	_sprite.draw();

	_colorProgram.unuse();
	
	//flush everything you've drawn to the screen, Swap function that swaps buffers
	SDL_GL_SwapWindow(_window); 
}