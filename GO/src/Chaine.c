/**
 * @file Chaine.c
 * @brief
 * @date 9 janv. 2014
 * @author Gautier
 **/

#include <stdlib.h>
#include <assert.h>

#include "include/Liste.h"
#include "include/Couleur.h"
#include "include/Chaine.h"

/*========Fonction privée==============
 */

static int Chaine_determinerSiEstOeil(Plateau plateau, Position position)
{
	Couleur couleurOeil;
	int x, y, taille;

	taille = Matrice_getTaille(plateau);

	x = Position_getX(position);
	y = Position_getY(position);
	couleurOeil = VIDE;

	// Haut
	Position_setY(position, --y);
	if(y >= 0)
		if(Plateau_get(plateau, position) == VIDE)
			return 0;
		else
			couleurOeil = Plateau_get(plateau, position);	//Car la couleur est encore inconnue.


	// Gauche
	Position_setY(position, ++y);
	Position_setX(position, --x);
	if(x >= 0)
		if(couleurOeil != Plateau_get(plateau, position))	//Car la couleur est obligatoirement déjà devinée.
			return 0;

	// Bas
	Position_setY(position, ++y);
	Position_setX(position, ++x);
	if(y < taille)
		if(couleurOeil != Plateau_get(plateau, position))
			return 0;

	// Droite
	Position_setY(position, --y);
	Position_setX(position, ++x);
	if(x < taille)
		if(couleurOeil != Plateau_get(plateau, position))
			return 0;

	Position_setX(position, --x);

	return 1;
}

/*========Fonction publique============
 */


/**
 * Chaine.
 */
struct Chaine {
	Liste liste;		/**< Liste de position. */
	Couleur couleur;	/**< Couleur de la chaine. */
};

Chaine Chaine_creer()
{
	Chaine chaine;

	chaine = (Chaine) malloc(sizeof(struct Chaine));
	if(chaine == NULL)
		return NULL;

	if((chaine->liste = Liste_creer()) == NULL)
	{
		free(chaine);
		return NULL;
	}

	chaine->couleur = VIDE;

	return chaine;
}

void Chaine_detruire(Chaine chaine)
{
	assert(chaine);

	Liste_detruire(chaine->liste);
	free(chaine);
}

void Chaine_vider(Chaine chaine)
{
	Position pos;

	assert(chaine);

	if(Chaine_estVide(chaine))
		return;

	Chaine_tete(chaine);

	do
	{
		pos = Chaine_courant(chaine);
		assert(pos);
		free(pos);

		Liste_supprimerCourant(chaine->liste);
	} while(!Chaine_estVide(chaine));
}

int Chaine_appartient(Chaine chaine, Position position)
{
	Position positionCourant;

	assert(chaine);

	if(Chaine_estVide(chaine))
		return 0;

	Chaine_tete(chaine);

	do
	{
		positionCourant = Chaine_courant(chaine);

		if(Position_estIdentique(positionCourant, position))
			return 1;

	} while(Chaine_suivant(chaine));

	return 0;
}

int Chaine_estVide(Chaine chaine)
{
	assert(chaine);

	return Liste_estVide(chaine->liste);
}

Position Chaine_courant(Chaine chaine)
{
	assert(chaine);

	return Liste_courant(chaine->liste);
}

int Chaine_suivant(Chaine chaine)
{
	assert(chaine);

	return Liste_suivant(chaine->liste);
}

void Chaine_tete(Chaine chaine)
{
	assert(chaine);

	Liste_tete(chaine->liste);
}

void Chaine_inserer(Chaine chaine, Position position)
{
	assert(chaine);

	Liste_insererQueue(chaine->liste, position);
}

void Chaine_setCouleur(Chaine chaine, Couleur couleur)
{
	assert(chaine);

	chaine->couleur = couleur;
}

Couleur Chaine_getCouleur(Chaine chaine)
{
	assert(chaine);

	return chaine->couleur;
}

Positions Chaine_determinerYeux(Plateau plateau, Chaine chaine)
{
	Positions positions;
	Libertes libertes;
	Position position;
	Couleur couleurOeil;
	int x, y, taille;

	libertes = Libertes_determinerLibertes(plateau, chaine);
	positions = Liste_creer();
	taille = Matrice_getTaille(plateau);

	if(libertes == NULL)
		return NULL;

	Liste_tete(libertes);

	do
	{
		position = Liste_courant(libertes);

		if(Chaine_determinerSiEstOeil(plateau, position))	//Très pratique d'utiliser une sous-fonction à part pour éviter les sous cas à rallonge :)
			Liste_insererCourant(positions, position);

	}while( Liste_suivant(libertes) );

	return positions;
}
