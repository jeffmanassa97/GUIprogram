#pragma once

#include <GL/glew.h>

struct Position { 
	float x;
	float y;
};
// these structs are ourside Vertex, then we can use them everywhere
struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

//GLubyte is the same as unsigned char, only need one byte = 8 bits = 256
//4 colors for an extra byte for padding, red green blue alpha. Alpha is transparencey


//the vertex Definition
struct Vertex { //want the vertex struct to be a multible of 4 bytes to avaoid alignment issues
	//This is the position struct. When you store a struct or class
	//inside of another struct or class, it is call composition. This is
	//layed out exactly the same in memory as if we had a float position[2],
	//but doing it this way makes more sense.
	
	Position position;
	
	Color color;
};