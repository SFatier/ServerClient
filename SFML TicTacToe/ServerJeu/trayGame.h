#pragma once
#include <iostream>
using namespace std;

class  TrayGame
{
public:
	 TrayGame();
	~ TrayGame();
	void Draw();
	void JeuJoueur(int _case);
	char Win();
	void Jouer(int _case);

	private:
		char matrix[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		char player = 'X';
};

