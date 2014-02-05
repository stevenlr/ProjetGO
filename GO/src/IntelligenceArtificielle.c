/**
 * @file IntelligenceArtificielle.c
 * @brief 
 */

#include <stdlib.h>
#include <matrice.h>

#include "include/IntelligenceArtificielle.h"
#include "include/Partie.h"
#include "include/Position.h"
#include "include/Plateau.h"
#include "include/Libertes.h"
#include "include/modes/etats/EtatsJeu.h"
#include "include/modes/ecrans/EcranJeu.h"

/**
 * Essaye de placer un pion au hasard dans une liste de positions.
 * La liste est vidée mais pas détruite lors de l'exécution.
 *
 * @param etats Etats du jeu.
 * @param positions Liste de positions.
 * @return 1 si un pion a pu être placé, 0 sinon.
 */
int IA_placerHasardDansListe(EtatsJeu* etats, Liste positions)
{
	int valide = 0, id;
	Position pos;

	while(!Liste_estVide(positions))
	{
		id = rand() % Liste_getNbElements(positions);
		Liste_setCourant(positions, id);
		pos = Liste_courant(positions);
		valide = EcranJeu_eventPlacerPion(Position_getX(pos), Position_getY(pos));

		if(valide)
			break;

		Position_detruire(pos);
		Liste_supprimerCourant(positions);
	}

	Liste_tete(positions);

	while(!Liste_estVide(positions))
	{
		Position_detruire(Liste_courant(positions));
		Liste_supprimerCourant(positions);
	}

	return valide;
}

/**
 * Tente de jouer au hasard sur le plateau.
 *
 * @param etats Etats de jeu.
 * @return 1 si on a pu placer un pion, 0 sinon.
 */
int IA_jouerHasard(EtatsJeu* etats)
{
	Liste positions;
	int valide;

	positions = Partie_getPositionsLibres(etats->partie);
	valide = IA_placerHasardDansListe(etats, positions);

	Liste_detruire(positions);

	return valide;
}

/**
 * Tente de se défendre : si une chaîne n'a plus qu'une libertée, on essaye d'occuper cette liberté.
 *
 * @param etats Etats de jeu.
 * @return 1 si on a pu jouer un tour, 0 sinon.
 */
int IA_defendre(EtatsJeu* etats)
{
	int valide = 0, taille, x, y;
	Couleur couleur;
	Matrice casesTraitees;
	Position origine = Position_creer(0, 0), pos;
	Plateau plateau = Partie_getPlateauActuel(etats->partie);
	Chaine chaine;
	Libertes libertes;

	taille = Partie_getTaille(etats->partie);
	casesTraitees = Matrice_creer(taille, taille, 0);

	couleur = Partie_getJoueurActuel(etats->partie);

	for(y = 0; y < taille && !valide; y++)
	{
		Position_setY(origine, y);

		for(x = 0; x < taille && !valide; x++)
		{
			Position_setX(origine, x);

			if(Matrice_get(casesTraitees, y, x)) continue;

			if(Plateau_get(plateau, origine) != couleur)
			{
				Matrice_set(casesTraitees, y, x, 1);
				continue;
			}

			chaine = Plateau_determinerChaine(plateau, origine);
			libertes = Libertes_determinerLibertes(plateau, chaine);

			if(Liste_getNbElements(libertes) == 1)
			{
				Liste_tete(libertes);
				pos = Liste_courant(libertes);
				valide = EcranJeu_eventPlacerPion(Position_getX(pos), Position_getY(pos));
			}

			Libertes_vider(libertes);
			Liste_detruire(libertes);

			Chaine_tete(chaine);

			do
			{
				pos = Chaine_courant(chaine);
				Matrice_set(casesTraitees, Position_getY(pos), Position_getY(pos), 1);
			} while(Chaine_suivant(chaine));

			Chaine_vider(chaine);
			Chaine_detruire(chaine);
		}
	}

	Matrice_detruire(casesTraitees);
	Position_detruire(origine);

	return valide;
}

/**
 * Tente d'attaquer : tente de réduire les libertés des chaînes ennemis en ayant le moins.
 *
 * @param etats Etats de jeu.
 * @return 1 si on a pu jouer un tour, 0 sinon.
 */
int IA_attaque(EtatsJeu* etats)
{
	int valide, taille, x, y, minLibertes = 1000;
	Couleur couleur, ennemi;
	Matrice casesTraitees;
	Position origine = Position_creer(0, 0), pos;
	Plateau plateau = Partie_getPlateauActuel(etats->partie);
	Chaine chaine;
	Libertes libertes, libertesChaineMinimale = NULL, tmp;

	taille = Partie_getTaille(etats->partie);
	casesTraitees = Matrice_creer(taille, taille, 0);

	couleur = Partie_getJoueurActuel(etats->partie);
	ennemi = (couleur == BLANC) ? NOIR : BLANC;

	for(y = 0; y < taille && minLibertes > 1; y++)
	{
		Position_setY(origine, y);

		for(x = 0; x < taille && minLibertes > 1; x++)
		{
			Position_setX(origine, x);

			if(Matrice_get(casesTraitees, y, x)) continue;

			if(Plateau_get(plateau, origine) != ennemi)
			{
				Matrice_set(casesTraitees, y, x, 1);
				continue;
			}

			chaine = Plateau_determinerChaine(plateau, origine);
			libertes = Libertes_determinerLibertes(plateau, chaine);

			if(Liste_getNbElements(libertes) < minLibertes)
			{
				minLibertes = Liste_getNbElements(libertes);

				tmp = libertesChaineMinimale;
				libertesChaineMinimale = libertes;
				libertes = tmp;
			}

			if(libertes != NULL)
			{
				Libertes_vider(libertes);
				Liste_detruire(libertes);
			}

			Chaine_tete(chaine);

			do
			{
				pos = Chaine_courant(chaine);
				Matrice_set(casesTraitees, Position_getY(pos), Position_getY(pos), 1);
			} while(Chaine_suivant(chaine));

			Chaine_vider(chaine);
			Chaine_detruire(chaine);
		}
	}

	Matrice_detruire(casesTraitees);
	Position_detruire(origine);

	if(libertesChaineMinimale == NULL)
		return 0;

	valide = IA_placerHasardDansListe(etats, libertesChaineMinimale);
	Libertes_vider(libertesChaineMinimale);
	Liste_detruire(libertesChaineMinimale);

	return valide;
}

void IA_tourOrdinateur(EtatsJeu *etats)
{
	if(Partie_getToursPasses(etats->partie) == 1) // Si un joueur a passé un tour, l'autre a une chance sur 4 de passer aussi.
	{
		if(rand() % 4 == 0)
		{
			EcranJeu_eventPasserTour();
			return;
		}
	}

	if(IA_defendre(etats)) // Les problèmes arrivent vers 650 coups
		return;

	if(IA_attaque(etats)) // Les problèmes arrivent vers 1000 coups
		return;

	if(IA_jouerHasard(etats)) // Aucun problèmes
		return;

	EcranJeu_eventPasserTour();
}
