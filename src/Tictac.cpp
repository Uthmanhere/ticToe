#include "Tictac.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Tictac::Tictac()
{
	get_squareFile();
}
//get square array from the file.
void Tictac::get_squareFile()
{
	ifstream sqIn("square.txt", ios::in);
	unsigned int counter = 0;
	while (sqIn >> square[counter])	//initial inputs from file
		++counter;		//whether saved or unsaved
}
//set present state of square arrray to the file.
void Tictac::set_squareFile()
{
	ofstream sqOut("square.txt", ios::out);

	for (unsigned int counter = 0; counter < 10; ++counter)
		sqOut << square[counter] << " ";

}
//reset the array to its default values.
void Tictac::set_defaultSquareFile()
{
	ofstream sqOut("square.txt", ios::out);
	for (unsigned int counter = 0; counter < 10; ++counter)
	{
		if (counter == 0)
			sqOut << 'o' << " ";
		else
		{
			sqOut << counter << " ";
		}
	}
}
int Tictac::set_mark(int x, int y)
{
	mark = square[0];
//	cout << "Player " << square[0]
//		<< ", enter a number:  ";
//	cin >> choice;			???

	//A mathematical hack :D
	choice = 3 * (1 - y) + (x + 2);

	if (choice == 1 && square[1] == '1')
		square[1] = mark;
	else if (choice == 2 && square[2] == '2')

		square[2] = mark;
	else if (choice == 3 && square[3] == '3')

		square[3] = mark;
	else if (choice == 4 && square[4] == '4')

		square[4] = mark;
	else if (choice == 5 && square[5] == '5')

		square[5] = mark;
	else if (choice == 6 && square[6] == '6')

		square[6] = mark;
	else if (choice == 7 && square[7] == '7')

		square[7] = mark;
	else if (choice == 8 && square[8] == '8')

		square[8] = mark;
	else if (choice == 9 && square[9] == '9')

		square[9] = mark;
	else if (choice == -1)	//everything is saved in the file.
		return 0;
	else if (choice == 0)	//setting up the file to default.
	{
		set_defaultSquareFile();
		return 2;
	}
	else
	{
		cout << "Invalid move ";

		set_prevPlayer();
//		cin.ignore();
//		cin.get();
	}
	set_nextPlayer();
	set_squareFile();

	return get_win();
}
//change players...
void Tictac::set_nextPlayer()
{
	square[0] = (square[0] == 'o') ? 'x' : 'o';
}
void Tictac::set_prevPlayer()
{
	square[0] = (square[0] == 'o') ? 'x' : 'o';
}
void Tictac::set_choice(int c)
{
	choice = c;
}
/*********************************************
FUNCTION TO RETURN GAME STATUS
1 FOR GAME IS OVER WITH RESULT
-1 FOR GAME IS IN PROGRESS
O GAME IS OVER AND NO RESULT
**********************************************/
int Tictac::get_win()
{
	if (square[1] == square[2] && square[2] == square[3])

		return 1;
	else if (square[4] == square[5] && square[5] == square[6])

		return 1;
	else if (square[7] == square[8] && square[8] == square[9])

		return 1;
	else if (square[1] == square[4] && square[4] == square[7])

		return 1;
	else if (square[2] == square[5] && square[5] == square[8])

		return 1;
	else if (square[3] == square[6] && square[6] == square[9])

		return 1;
	else if (square[1] == square[5] && square[5] == square[9])

		return 1;
	else if (square[3] == square[5] && square[5] == square[7])

		return 1;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3'
		&& square[4] != '4' && square[5] != '5' && square[6] != '6'
		&& square[7] != '7' && square[8] != '8' && square[9] != '9')

		return 0;
	else
		return -1;
}
//whose turn is this
char Tictac::get_player()
{
	return square[0];
}
//the final result!
void Tictac::get_result()
{
	set_prevPlayer();
	if (get_win() == 1)
	{
		cout << "==>\aPlayer " << get_player() << " win ";
		set_defaultSquareFile();
	}
	else if (get_win() == 0)
	{
		cout << "==>\aGame draw";
		set_defaultSquareFile();

	}
}
char Tictac::get_square(int pos) const
{
	return square[pos];
}
Tictac::~Tictac()
{
}
