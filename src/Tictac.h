#pragma once
class Tictac
{
public:
	//constructor
	Tictac();
	//setters...
	int set_mark(int, int);
	void set_choice(int c);
	void set_defaultSquareFile();
	void set_squareFile();
	void set_nextPlayer();
	void set_prevPlayer();
	//getters...
	void get_squareFile();
	int get_win();
	char get_player();
	void get_result();
	char get_square(int) const;
	//destructor...
	~Tictac();
private:
	char square[10];
	int choice;
	char mark;
};

