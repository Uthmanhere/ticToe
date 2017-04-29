#include "GLgraphics.h"

#include <SFML/OpenGL.hpp>
#include <iostream>
#include <math.h>
#include <unistd.h>

using namespace std;

#define PI 3.14

void GLgraphics::set_lineColor(GLfloat r, GLfloat g, GLfloat b) const
{
	glColor3f(r, g, b);
}
void GLgraphics::set_bgColor(GLfloat r, GLfloat g, GLfloat b) const
{
	glClearColor (r, g, b, 0.0);
	glClear (GL_COLOR_BUFFER_BIT);
}
void GLgraphics::set_size(double size)
{
	this->size = size;
}
double GLgraphics::get_size() const
{
	return size;
}
void GLgraphics::set_lineWidth(GLfloat width)
{
	glLineWidth(width);
}
void GLgraphics::get_board()
{
	set_lineWidth(1.0);
	double factor = get_size() / 4;
	double step = get_size() / 2;
	glBegin(GL_LINES);
		glVertex3f (0.5 - factor, 0.5 - factor - step, 0.0);    //      |
		glVertex3f (0.5 - factor, 0.5 + factor + step, 0.0);    //      |
		glVertex3f (0.5 + factor, 0.5 - factor - step, 0.0);    //              |
		glVertex3f (0.5 + factor, 0.5 + factor + step, 0.0);    //              |
									//      _________
		glVertex3f (0.5 - factor - step, 0.5 - factor, 0.0);    //      
		glVertex3f (0.5 + factor + step, 0.5 -  factor, 0.0);   //      ---------
									//      _________
									//      ---------
		glVertex3f (0.5 - factor - step, 0.5 + factor, 0.0);    //
		glVertex3f (0.5 + factor + step, 0.5 + factor, 0.0);    //      _________
	glEnd();

}
void GLgraphics::get_circle(int xPos, int yPos)
{
	set_lineWidth(3.0);
	int i;
	GLfloat x = 0.5 + (xPos * get_size() / 2);
	GLfloat y = 0.5 + (yPos * get_size() / 2);
	int lineAmount = 100; //# of triangles used to draw circle
	//GLfloat radius = 0.8f; //radius
	GLfloat radius = get_size() / 5;
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i <= lineAmount;i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / lineAmount)),
			y + (radius* sin(i * twicePi / lineAmount))
		);
		}
	glEnd();
}
void GLgraphics::get_cross(int xPos, int yPos)
{
	set_lineWidth(3.0);
	GLfloat x = 0.5 + (xPos * get_size() / 2);
	GLfloat y = 0.5 + (yPos * get_size() / 2);
	GLfloat size = get_size() / 5;
	glBegin(GL_LINES);
		glVertex3f (x - (size), y - (size), 0.0);       //      *  *
		glVertex3f (x + (size), y + (size), 0.0);       //       **
		glVertex3f (x - (size), y + (size), 0.0);       //       **
		glVertex3f (x + (size), y - (size), 0.0);       //      *  *
	glEnd();
}
int GLgraphics::set_mouseBlocX(double x)
{
	double factor = get_size() / 4;
	if(x >= 0.5 - 3 * factor && x <= 0.5 - factor)
		return -1;
	else if (x >= 0.5 - factor && x <= 0.5 + factor)
		return 0;
	else if (x >= 0.5 + factor && x <= 0.5 + 3 * factor)
		return 1;
	else
		return 3;
}
int GLgraphics::set_mouseBlocY(double y)
{
	double factor = get_size() / 4;
	if(y >= 0.5 - 3 * factor && y <= 0.5 - factor)
		return 1;
	else if (y >= 0.5 - factor && y <= 0.5 + factor)
		return 0;
	else if (y >= 0.5 + factor && y <= 0.5 + 3 * factor)
		return -1;
	else
		return 3;
}
void GLgraphics::get_displayMoves()
{
	for (int y = 1; y >= -1; --y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			switch (static_cast<int>(get_square(3 * (1 - y) + (x + 2))))
			{
				case 'o':
					get_circle(x, y);
					break;
				case 'x':
					get_cross(x, y);
					break;
			}
		}
	}
}
void GLgraphics::get_displayOpt(int x, int y)
{
	if (get_square(3 * (1 - y) + (x + 2)) >= '1' && get_square(3 * (1 - y) + (x + 2)) <= '9')
	{
		switch (static_cast<int>(get_square(0)))
		{
			case 'o':
				get_circle(x, y);
				break;
			case 'x':
				get_cross(x, y);
				break;
			default:
				cout << "(get_square(3 * (1 - y) + (x + 2)" << 3 * (1 - y) + (x + 2) << endl;
		}
	}
}
bool GLgraphics::get_winnerDisp(int x, int y)
{
	switch(set_mark(x, y))
	{
		case 0:
			get_winCircle();
			get_winCross();
			set_defaultSquareFile();
			get_squareFile();
			return 1;	
			break;
		case 1:
			switch(get_player())
			{
				case 'x':
					get_winCircle();
					break;
				case 'o':
					get_winCross();
					break;
			}
			set_defaultSquareFile();
			get_squareFile();
			return 1;
			break;
	}
	return 0;
}
void GLgraphics::get_winCircle()
{
	set_lineWidth(5.0);
	int i;
	GLfloat x = 0.5;
	GLfloat y = 0.5;
	int lineAmount = 100; //# of triangles used to draw circle
	//GLfloat radius = 0.8f; //radius
	GLfloat radius = get_size() / 2;
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i <= lineAmount;i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / lineAmount)),
			y + (radius* sin(i * twicePi / lineAmount))
		);
		}
	glEnd();

}
void GLgraphics::get_winCross()
{
	set_lineWidth(5.0);
	GLfloat x = 0.5;
	GLfloat y = 0.5;
	GLfloat size = get_size() / 2;
	glBegin(GL_LINES);
		glVertex3f (x - (size), y - (size), 0.0);       //      *  *
		glVertex3f (x + (size), y + (size), 0.0);       //       **
		glVertex3f (x - (size), y + (size), 0.0);       //       **
		glVertex3f (x + (size), y - (size), 0.0);       //      *  *
	glEnd();

}
