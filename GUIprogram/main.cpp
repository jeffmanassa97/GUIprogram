#include <iostream>
#include "MainGame.h" //includes header file with our classes and information

#include <Windows.h> //give windows stuff that glew needs to function properly

int main(int argc, char ** argv) { //argument count, and list of arguments
	MainGame maingame; //calls class constructor
	maingame.run(); //calls initSystems(), gameLoop()
	

	
	return 0;
}