/**
 * @file Chaine.c
 * @brief
 * @date 9 janv. 2014
 * @author Gautier
 **/

#include <stdlib.h>
#include "include/Liste.h"
#include "include/Pion.h"
#include "include/Chaine.h"

Chaine Chaine_creer()
{
	return Liste_creer();
}

void Chaine_detruire(Chaine* chaine)
{
	Liste_detruire(*chaine);
	*chaine = NULL;
}

void Chaine_tete(Chaine chaine)
{
	Liste_tete(chaine);
}

void Chaine_suivant(Chaine chaine)
{
	Liste_suivant(chaine);
}

Pion* Chaine_courant(Chaine chaine)
{
	return Liste_courant(chaine);
}

void Chaine_inserer(Chaine chaine, Pion* pion)
{
	Liste_insererCourant(chaine, pion);
}

/*
 * En attente de discussion avec toi :
 * 	Pas de Chaine_supprimer pour la raison suivante ->
 * 		On recalcule toutes les chaines � chaque tour.
 * 		A aucun moment on a besoin de supprimer un �l�ment d'une chaine.
 * 		N�anmoins, peut �tre dans le calcul final il y aura besoin de supprimer des Pions du plateau (Pion mort)
 * 		Mais m�me dans ce cas, apr�s la suppression de tous les pions inutiles, on peut � nouveau recalculer chaque chaine.
 * 		Et m�me, ces pions morts forment une chaine morte... Donc la chaine sera automatiquement supprimer d�s le recalcul.
 * 		Donc en fait, pour moi, pas besoin de "Chaine_supprimer".
 *
 *	Pouvant me tromper, j'attends ta r�flexion ;)
 */

int Chaine_appartient(Chaine chaine, Pion pion)
{
	if(Liste_estVide(chaine))
		return 0;

	Liste_tete(chaine);

	do
	{
		Pion* pionCourant = Liste_courant(chaine);

		if(Pion_estIdentique(*pionCourant,pion))
			return 1;
	}while(Liste_suivant(chaine));

	return 0;
}


