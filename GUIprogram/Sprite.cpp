#include "Sprite.h"
#include "Vertex.h"

#include <cstddef> //for offsetof()

Sprite::Sprite()
{
	_vboID = 0; //always set to zero, which is like null
}


Sprite::~Sprite()
{
	if (_vboID != 0) { //you don't want to delete the buffer if it doesn't exist
		glDeleteBuffers(1, &_vboID); //delete one buffer, and which buffer (_vboID). The opposite of glGenBuffers
	}
}


void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;


	if (_vboID == 0) { //if equal to 0, then we know it hasnt been initiated yet.
		glGenBuffers(1, &_vboID); //generate buffer id and assign it to _vboID. 1 buffer, passed in as a pointer
	}
	//Vertex struct from "Vertex.h"
	Vertex vertexData[6]; //6 * 2 vertices, accounting for x & y. 6 vertices is two triangles which makes a square
	//In screen coordinates, rather than normalized device coordinates, but will convert it in init()
	//First Triangle
	vertexData[0].position.x = x + width; //top right vertice, vertexData[0] is the x position
	vertexData[0].position.y = y + height;
	
	vertexData[1].position.x = x; //top left vertice
	vertexData[1].position.y = y + height;
	
	vertexData[2].position.x = x; //bottom left
	vertexData[2].position.y = y;
	
	//Second Triangle
	vertexData[3].position.x = x; //bottom left
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width; //bottom right
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width; //top right
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++) { //set up the vertex colors, when passing them into OpenGL it was convert these bytes to floats to use them
		vertexData[i].color.r = 255; //0 - 255 is the level of intenseity of the color, 255 is the thickest and not transparent
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0; //top left corner blue
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 0; //bottom right corner green
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 255;
	
	glBindBuffer(GL_ARRAY_BUFFER, _vboID); //tells OpenGL that we want this buffer to be active, basic vertex buffer, with _vboID
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //uploads the triangle data to the buffer we just created (GL_ARRAY_BUFFER); the size says how many bits it will be; pass a pointer to tell it what the data is which is vertexData, arrays can be pointers so we don't need the &; usage (draw onece or many times?)

	glBindBuffer(GL_ARRAY_BUFFER, 0); //then unbind buffer, not required but it makes things safer, 0 indicates no buffer
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//1 vertex attribute array of just positions(not lighting or color, etc.), think of 0 index as first value like in an array
	glEnableVertexAttribArray(0); 
	
	//This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //(says point to the start of the data, 2 floats at a time, not normalized, stride is the size of Vertex struct = sizeof(Vertex), and 0 byte offset, the color struct is 8 bytes offset) 2 stands for number of elemenets, x & y, 2D ;type of variable for positions
	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); //the index; how many variables; type of variables; yes to normalize, which will convert anything from 0 - 255 to 0 - 1;


	//draws array vertices
	glDrawArrays(GL_TRIANGLES, 0, 6); //the mode(traingle, points, quads); the first element is 0; how many of elemets are we drawing(6 vertices, each is 2 floats which was said above)

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinds buffer
}