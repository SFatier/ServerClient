#include "Jeu.h"


int main() {



	Jeu partie(55001);
	partie.Init();
	partie.CreationJeu();
	partie.Loop();

	return 0;
	
}