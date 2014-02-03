/**
 * @file EntreeTexte.c
 * @brief 
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/graphics/Texte.h"
#include "include/graphics/EntreeTexte.h"

/**
 * Champ de texte.
 */
struct EntreeTexte {
	int x;				/**< Abscisse du champ. */
	int y;				/**< Ordonnée du champ. */
	int largeur;		/**< Largeur du champ. */
	int couleurFond;	/**< Couleur de fond du champ. */
	int couleurTexte;	/**< Couleur du texte dans le champ. */
	int tailleMax;		/**< Taille maximale d'une chaîne dans le champ. */
	int taille;			/**< Taille actuelle du texte dans le champ. */
	int focus;			/**< 1 si le champ a le focus, 0 sinon. */
	char* str;			/**< Texte contenu dans le champ. */
};

EntreeTexte EntreeTexte_creer(int x, int y, int largeur, int couleurFond, int couleurTexte, int tailleMax)
{
	EntreeTexte entree = malloc(sizeof(struct EntreeTexte));

	if(entree == NULL)
		return NULL;

	entree->x = x;
	entree->y = y;
	entree->largeur = largeur;
	entree->couleurFond = couleurFond;
	entree->couleurTexte = couleurTexte;
	entree->tailleMax = tailleMax;

	entree->taille = 0;
	entree->focus = 0;

	entree->str = malloc(sizeof(char) * (tailleMax + 2));
	memset(entree->str, '\0', tailleMax + 2);

	return entree;
}

void EntreeTexte_detruire(EntreeTexte entree)
{
	assert(entree);

	free(entree->str);
	free(entree);
}

void EntreeTexte_afficher(EntreeTexte entree, SDL_Surface* surface)
{
	SDL_Rect rect;

	rect.x = entree->x;
	rect.y = entree->y;
	rect.w = entree->largeur;
	rect.h = 40;

	SDL_FillRect(surface, &rect, entree->couleurFond);

	Texte_afficherChaine(surface, entree->x + 7, entree->y + 20, entree->str, ITALIQUE, entree->couleurTexte, CENTRE_Y | GAUCHE);
}

void EntreeTexte_setTexte(EntreeTexte entree, char* str)
{
	int len = strlen(str);

	if(len > entree->tailleMax)
		len = entree->tailleMax;

	entree->taille = len;

	strncpy(entree->str, str, len);
	entree->str[len] = '\0';
}

char* EntreeTexte_getTexte(EntreeTexte entree)
{
	return entree->str;
}

void EntreeTexte_clique(EntreeTexte entree, int x, int y)
{
	if(x < entree->x || x > entree->x + entree->largeur || y < entree->y || y > entree->y + 40)
		EntreeTexte_setFocus(entree, 0);
	else
		EntreeTexte_setFocus(entree, 1);
}

void EntreeTexte_setFocus(EntreeTexte entree, int focus)
{
	entree->focus = focus;

	if(focus)
	{
		entree->str[entree->taille] = '|';
		entree->str[entree->taille + 1] = '\0';
	}
	else
		entree->str[entree->taille] = '\0';
}

int EntreeTexte_getFocus(EntreeTexte entree)
{
	return entree->focus;
}

void EntreeTexte_retour(EntreeTexte entree)
{
	if(entree->taille == 0)
		return;

	entree->taille--;
	entree->str[entree->taille] = '|';
	entree->str[entree->taille + 1] = '\0';
}

void EntreeTexte_inserer(EntreeTexte entree, char c)
{
	if(entree->taille == entree->tailleMax)
		return;

	entree->str[entree->taille] = c;
	entree->taille++;
	entree->str[entree->taille] = '|';
	entree->str[entree->taille + 1] = '\0';
}
