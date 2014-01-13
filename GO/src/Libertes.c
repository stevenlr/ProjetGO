/**
 * @file Libertes.c
 * @brief
 */

#include <stdlib.h>
#include "assert.h"

#include "include/Libertes.h"
#include "include/Couleur.h"
#include "include/Pion.h"
#include "include/Liste.h"
#include "include/Position.h"
#include "include/Plateau.h"

// Fonctions privées ==========================================================

/**
 * Créé un pion l'ajoute à la liste de libertés si la case lui correspondant est bien vide
 * et que sa position ne se trouve pas déjà dans les libertés.
 *
 * @param plateau
 * @param position
 * @param libertes
 * @return Le pion créé si besoin, 0 sinon.
 */
static void Libertes_creerPionSiEstLiberte(Plateau plateau, Position position, Libertes libertes)
{
	Pion pion = Pion_creer(position, Plateau_get(plateau, position));

	if(Pion_getCouleur(pion) == VIDE && !(Libertes_appartient(libertes, position)))
	{
		Liste_insererQueue(libertes, pion);
		return;
	}

	Pion_detruire(pion);
}

// Fonctions publiques ========================================================

Libertes Libertes_determinerLibertes(Plateau plateau, Chaine chaine)
{
	Libertes libertes;
	Position position;
	int taille;

	if((libertes = Liste_creer()) == NULL)
		return NULL;

	Matrice_getTaille(plateau, NULL, &taille);

	do
	{
		position = Pion_getPosition(Liste_courant(chaine));

		// Haut
		position.y--;
		if(position.y >= 0)
			Libertes_creerPionSiEstLiberte(plateau, position, libertes);

		// Gauche
		position.y++;
		position.x--;
		if(position.x >= 0)
			Libertes_creerPionSiEstLiberte(plateau, position, libertes);

		// Bas
		position.y++;
		position.x++;
		if(position.y < taille)
			Libertes_creerPionSiEstLiberte(plateau, position, libertes);

		// Droite
		position.y--;
		position.x++;
		if(position.x < taille)
			Libertes_creerPionSiEstLiberte(plateau, position, libertes);

	} while(Liste_suivant(chaine));

	return libertes;
}

int Libertes_appartient(Libertes libertes, Position position)
{
	Position posCourant;

	assert(libertes);

	if(Liste_estVide(libertes))
		return 0;

	Liste_tete(libertes);

	do
	{
		posCourant = Pion_getPosition(Liste_courant(libertes));

		if(posCourant.x == position.x && posCourant.y == position.y)
			return 1;

	} while(Liste_suivant(libertes));

	return 0;
}
