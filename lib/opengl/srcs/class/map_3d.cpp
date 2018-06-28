/*
** EPITECH PROJECT, 2018
** mdr
** File description:
** mdr
*/

#include "opengl.hpp"

void u_opengl::drawCube(float x, float y, float size, int r, int g, int v, size_t map_size)
{
	x = map_size / 2 - x - size;
	y = map_size / 2 - y - size;

	glTranslatef(-x, -y, static_cast<GLfloat>(size + 0.1));
	glBegin(GL_QUADS);

	glColor3ub(static_cast<GLubyte>(r), static_cast<GLubyte>(g), static_cast<GLubyte>(v));

	// FRONT
	glVertex3f(-size,-size,size);
	glVertex3f(size,-size,size);
	glVertex3f(size,size,size);
	glVertex3f(-size,size,size);

	// BACK
	glVertex3f(-size,-size,-size);
	glVertex3f(-size,size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,-size,-size);

	// LEFT
	glVertex3f(-size,-size,size);
	glVertex3f(-size,size,size);
	glVertex3f(-size,size,-size);
	glVertex3f(-size,-size,-size);

	// RIGHT
	glVertex3f(size,-size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,size,size);
	glVertex3f(size,-size,size);

	// TOP
	glVertex3f(-size,size,size);
	glVertex3f(size,size,size);
	glVertex3f(size,size,-size);
	glVertex3f(-size,size,-size);

	// BOTTON
	glVertex3f(-size,-size,size);
	glVertex3f(-size,-size,-size);
	glVertex3f(size,-size,-size);
	glVertex3f(size,-size,size);

	glEnd();
	glTranslatef(x, y, static_cast<GLfloat>(-(size + 0.1)));
}

void u_opengl::drawSquare(float x, float y, float size, int r, int g, int v, size_t map_size)
{
	x = map_size / 2 - x - size;
	y = map_size / 2 - y - size;

	glTranslatef(-x, -y, static_cast<GLfloat>(size + 0.1));
	glBegin(GL_QUADS);

	glColor3ub(static_cast<GLubyte>(r), static_cast<GLubyte>(g), static_cast<GLubyte>(v));

	// BACK
	glVertex3f(-size,-size,-size);
	glVertex3f(-size,size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,-size,-size);

	glEnd();
	glTranslatef(x, y, static_cast<GLfloat>(-(size + 0.1)));
}


void u_opengl::draw3dMap(std::vector<std::string> &array)
{
	for (auto x = 0 ; x <= static_cast<int>(array.size() - 1) ; ++x) {
		for (auto y = 0 ; y <= static_cast<int>(array[x].size() - 1); ++y) {
			char character = array[x][y];
			if (character == '#')
				drawCube(x, y, CUBE_SIZE, 0, 255, 0, array.size());
			else if (character == ' ')
				drawSquare(x, y, CUBE_SIZE, 50, 50, 50, array.size());
			else if (character == 'o')
				drawCube(x, y, CUBE_SIZE, 255, 0, 255, array.size());
			else if (character >= '0' && character <= '5')
				drawCube(x, y, CUBE_SIZE, 102, 51, 0, array.size());
			else if (character >= 'A' && character <= 'D')
				drawCube(x, y, CUBE_SIZE, 70, 240, 240, array.size());
			else if (character >= 'E' && character <= 'H')
				drawCube(x, y, CUBE_SIZE, 0, 120, 255, array.size());
			else if (character >= 'I' && character <= 'L')
				drawCube(x, y, CUBE_SIZE, 255, 225, 25, array.size());
			else if (character >= 'M' && character <= 'P')
				drawCube(x, y, CUBE_SIZE, 145, 30, 180, array.size());
			else if (character == 'b')
				drawCube(x, y, CUBE_SIZE, 245, 130, 48, array.size());
		}
	}
}

void u_opengl::clearOpengl()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void u_opengl::refreshOpengl()
{
	glFlush();
}
