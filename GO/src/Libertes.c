
#include <stdlib.h>

#include "include/Libertes.h"
#include "include/Couleur.h"
#include "include/Pion.h"
#include "include/Liste.h"
#include "include/Position.h"
#include "include/Plateau.h"

Libertes determineLiberte(Plateau plateau,Chaine chaine)
{
	Libertes libertes;
	Position position;
	Pion pion;
	Couleur couleur;
	int taille;

	if((libertes = Chaine_creer()) == NULL)
		return NULL;

	taille = Matrice_getTaille(plateau, NULL, &taille);

	do
	{
		position = Pion_getPosition( Chaine_courant(libertes) );

		//Cas 1
		position.y--;
		if(position.y >= 0)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, libertes, VIDE);
		}
		//Cas 2
		position.y++;
		position.x--;
		if(position.x >= 0)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, libertes, VIDE);
		}
		//Cas 3
		position.y++;
		position.x++;
		if(position.y < taille)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, libertes, VIDE);
		}
		//Cas 4
		position.y--;
		position.x++;
		if(position.x < taille)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, libertes, VIDE);
		}
	}while(Chaine_suivant(libertes));

	return libertes;
}



