#pragma once
#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);



	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID; //vertex buffer object ID is an unsigned int. GLuint (GL unsigned int) is the same as unsigned, but promises 32bits. Unsigned int could be 8, 64bits, etc.
};

