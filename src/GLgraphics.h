#include <SFML/OpenGL.hpp>

#include "Tictac.h"

class GLgraphics : public Tictac
{
private:
	double size = 0;
public:
	void set_lineColor(GLfloat, GLfloat, GLfloat) const;
	void set_bgColor(GLfloat, GLfloat, GLfloat) const;
	void set_size(double);
	void set_lineWidth(GLfloat);
	double get_size() const;
	void get_board();
	void get_circle(int, int);
	void get_cross(int, int);
	int set_mouseBlocX(double);
	int set_mouseBlocY(double);
	void get_displayMoves();
	void get_displayOpt(int, int);
	bool get_winnerDisp(int, int);
	void get_winCircle();
	void get_winCross();
};
