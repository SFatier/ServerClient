#include "trayGame.h"

TrayGame::TrayGame()
{
	Draw();
	//Demande de tour
	int _tour = 0;
	Jouer(_tour);
}

TrayGame::~TrayGame()
{
}

void TrayGame::Jouer(int _case) {
	Jouer(_case);
	Draw();
}

void TrayGame::Draw() {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void TrayGame::JeuJoueur(int x, int y) {
	
	if (_case == 1)
	{
		if (matrix[0][0] == '1')
			matrix[0][0] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 2)
	{
		if (matrix[0][1] == '2')
			matrix[0][1] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 3)
	{
		if (matrix[0][2] == '3')
			matrix[0][2] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 4)
	{
		if (matrix[1][0] == '4')
			matrix[1][0] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 5)
	{
		if (matrix[1][1] == '5')
			matrix[1][1] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 6)
	{
		if (matrix[1][2] == '6')
			matrix[1][2] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 7)
	{
		if (matrix[2][0] == '7')
			matrix[2][0] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 8)
	{
		if (matrix[2][1] == '8')
			matrix[2][1] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
	else if (_case == 9)
	{
		if (matrix[2][2] == '9')
			matrix[2][2] = player;
		else
		{
			cout << "Case d�j� utilis�!" << endl;
			JeuJoueur(_case);
		}
	}
}

char TrayGame::Win()
{
	//first player
	if (matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X')
		return 'X';
	if (matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X')
		return 'X';
	if (matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if (matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X')
		return 'X';
	if (matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X')
		return 'X';
	if (matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
		return 'X';
	if (matrix[2][0] == 'X' && matrix[1][1] == 'X' && matrix[0][2] == 'X')
		return 'X';

	//second player
	if (matrix[0][0] == 'O' && matrix[0][1] == 'O' && matrix[0][2] == 'O')
		return 'O';
	if (matrix[1][0] == 'O' && matrix[1][1] == 'O' && matrix[1][2] == 'O')
		return 'O';
	if (matrix[2][0] == 'O' && matrix[2][1] == 'O' && matrix[2][2] == 'O')
		return 'O';

	if (matrix[0][0] == 'O' && matrix[1][0] == 'O' && matrix[2][0] == 'O')
		return 'O';
	if (matrix[0][1] == 'O' && matrix[1][1] == 'O' && matrix[2][1] == 'O')
		return 'O';
	if (matrix[0][2] == 'O' && matrix[1][2] == 'O' && matrix[2][2] == 'O')
		return 'O';

	if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O')
		return 'O';
	if (matrix[2][0] == 'O' && matrix[1][1] == 'O' && matrix[0][2] == 'O')
		return 'O';

	return '/';
}