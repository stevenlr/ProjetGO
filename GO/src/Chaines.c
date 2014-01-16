#include "include/Chaines.h"


int Chaines_positionAppartient(Chaines chaines, Position position)
{
	Chaine chaine;
	int appartientChaine = 0;

	if(Liste_estVide(chaines))
		return 0;

	Liste_tete(chaines);

	do
	{
		chaine = Liste_courant(chaines);
		if(Chaine_appartient(chaine, position))
		{
			appartientChaine = 1;
		}
	}while(Liste_suivant(chaines));

	return appartientChaine;
}

