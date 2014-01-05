/**
 * @file Liste.h
 * @brief En-tête de liste doublement chaînée.
 */

#ifndef LISTE_H_
#define LISTE_H_

/**
 * Un élément de la liste double chaînée.
 */
struct _ElementListe {
	struct _ElementListe* precedent;	/**< Pointeur vers l'élément suivant dans la liste. */
	struct _ElementListe* suivant;		/**< Pointeur vers l'élément précédent dans la liste. */
	void* ptr;							/**< Objet stocké. */
};

typedef struct _ElementListe ElementListe;

/**
 * Liste doublement chaînée.
 */
typedef struct {
	ElementListe* tete;		/**< Pointeur vers le début de la liste. */
	ElementListe* queue;	/**< Pointeur vers la fin de la liste. */
	ElementListe* courant;	/**< Pointeur vers l'élément courant. */
} Liste;

/**
 * Créé un élément de liste.
 * On ne devrait pas avoir à s'en servir en dehors des fonctions de Liste.
 *
 * @return L'élément créé. NULL en cas d'erreur.
 */
ElementListe* ElementListe_creer();

/**
 * Détruit un élément de liste.
 * On ne devrait pas avoir à s'en servir en dehors des fonctions de Liste.
 *
 * @param element L'élément à détruire.
 */
void ElementListe_detruire(ElementListe* element);

/**
 * Créé une liste vide.
 *
 * @return La liste ! NULL en cas de problème. (ça devrait pas arriver mais bon...)
 */
Liste* Liste_creer();

/**
 * Détruit une liste.
 * Attention à désallouer les éléments (si besoin est) avant pour pas avoir de grosses fuites mémoire...
 *
 * @param liste La liste à désallouer.
 */
void Liste_detruire(Liste* liste);

/**
 * Se place en début de liste.
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
 * Vérifie si une liste est vide.
 *
 * @param liste
 * @return 1 si la liste est vide, 0 sinon.
 */
int Liste_estVide(Liste* liste);

#endif
