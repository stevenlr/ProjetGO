/**
 * @file Liste.h
 * @brief En-t�te de liste doublement cha�n�e.
 */

#ifndef LISTE_H_
#define LISTE_H_

/**
 * Un �l�ment de la liste double cha�n�e.
 */
struct _ElementListe {
	struct _ElementListe* precedent;	/**< Pointeur vers l'�l�ment suivant dans la liste. */
	struct _ElementListe* suivant;		/**< Pointeur vers l'�l�ment pr�c�dent dans la liste. */
	void* ptr;							/**< Objet stock�. */
};

typedef struct _ElementListe ElementListe;

/**
 * Liste doublement cha�n�e.
 */
typedef struct {
	ElementListe* tete;		/**< Pointeur vers le d�but de la liste. */
	ElementListe* queue;	/**< Pointeur vers la fin de la liste. */
	ElementListe* courant;	/**< Pointeur vers l'�l�ment courant. */
} Liste;

/**
 * Cr�� un �l�ment de liste.
 * On ne devrait pas avoir � s'en servir en dehors des fonctions de Liste.
 *
 * @return L'�l�ment cr��. NULL en cas d'erreur.
 */
ElementListe* ElementListe_creer();

/**
 * D�truit un �l�ment de liste.
 * On ne devrait pas avoir � s'en servir en dehors des fonctions de Liste.
 *
 * @param element L'�l�ment � d�truire.
 */
void ElementListe_detruire(ElementListe* element);

/**
 * Cr�� une liste vide.
 *
 * @return La liste ! NULL en cas de probl�me. (�a devrait pas arriver mais bon...)
 */
Liste* Liste_creer();

/**
 * D�truit une liste.
 * Attention � d�sallouer les �l�ments (si besoin est) avant pour pas avoir de grosses fuites m�moire...
 *
 * @param liste La liste � d�sallouer.
 */
void Liste_detruire(Liste* liste);

/**
 * Se place en d�but de liste.
 *
 * @param liste
 */
void Liste_tete(Liste* liste);

/**
 * Se place en fin liste.
 *
 * @param liste
 */
void Liste_queue(Liste* liste);

/**
 * V�rifie si une liste est vide.
 *
 * @param liste
 * @return 1 si la liste est vide, 0 sinon.
 */
int Liste_estVide(Liste* liste);

#endif
