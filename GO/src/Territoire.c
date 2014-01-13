
#include <stdlib.h>

#include "include/Territoire.h"
#include "include/Plateau.h"
#include "include/Chaine.h"
#include "include/Position.h"
#include "include/Pile.h"
#include "include/Pion.h"
#include "include/Couleur.h"

Territoire determineTerritoire(Plateau plateau,Position origine)
{
	Territoire territoire;
	Pile pile;
	Pion pion, pionTerritoire;
	Position position;
	int taille;

	if((pile = Pile_creer()) == NULL)
		return NULL;

	if((territoire = Chaine_creer()) == NULL)
		return NULL;


	pionTerritoire = Pion_creer(origine, Plateau_get(plateau, origine));
	Matrice_getTaille(plateau, NULL, &taille);

	if(Pion_getCouleur(pionTerritoire) != VIDE) //Difference par rapport à Plateau_determinerChaine
		return NULL;

	Chaine_inserer(territoire, pionTerritoire);
	Pile_empiler(pile, pionTerritoire);

	while((pionTerritoire = Pile_depiler(pile)) != NULL)
	{
		position = Pion_getPosition(pionTerritoire);

		// Cas 1, en haut
		position.y -= 1;
		if(position.y >= 0)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, territoire, VIDE);

			if(pion != NULL) // Si on l'a inséré à la chaîne, on devra le traiter plus tard.
				Pile_empiler(pile, pion);
		}

		// Cas 2, à droite
		position.y += 1;
		position.x += 1;
		if(position.x < taille)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, territoire, VIDE);

			if(pion != NULL)
				Pile_empiler(pile, pion);
		}

		// Cas 3, en bas
		position.y += 1;
		position.x -= 1;
		if(position.y < taille)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, territoire, VIDE);

			if(pion != NULL)
				Pile_empiler(pile, pion);
		}

		// Cas 4, à gauche
		position.y -= 1;
		position.x -= 1;
		if(position.x >= 0)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, territoire, VIDE);

			if(pion != NULL)
				Pile_empiler(pile, pion);
		}

	}

	return territoire;
}

