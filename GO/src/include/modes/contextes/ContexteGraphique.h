/**
 * @file ContexteGraphique.h
 * @brief 
 */

#ifndef CONTEXTEGRAPHIQUE_H_
#define CONTEXTEGRAPHIQUE_H_

#include <SDL/SDL.h>

#include "Contexte.h"
#include "include/graphics/Bouton.h"
#include "include/graphics/ChoixMultiple.h"
#include "include/graphics/EntreeTexte.h"

#define NBOUTONS 18

/**
 * Boutons disponibles dans le jeu.
 */
typedef enum {
	JEU_PASSER,            //!< JEU_PASSER
	JEU_SAUVEGARDER,       //!< JEU_SAUVEGARDER
	JEU_QUITTER,           //!< JEU_QUITTER
	JEU_PRECEDENT,         //!< JEU_PRECEDENT
	JEU_SUIVANT,           //!< JEU_SUIVANT

	MENU_NOUVELLEPARTIE,   //!< MENU_NOUVELLEPARTIE
	MENU_REPRENDREPARTIE,  //!< MENU_REPRENDREPARTIE
	MENU_GUIDE,            //!< MENU_GUIDE
	MENU_QUITTER,          //!< MENU_QUITTER

	GUIDE_QUITTER,         //!< GUIDE_QUITTER
	GUIDE_PRECEDENT,       //!< GUIDE_PRECEDENT
	GUIDE_SUIVANT,         //!< GUIDE_SUIVANT

	OPTIONS_RETOUR,        //!< OPTIONS_RETOUR
	OPTIONS_COMMENCER,     //!< OPTIONS_COMMENCER
	OPTIONS_HANDICAP_MOINS,//!< OPTIONS_HANDICAP_MOINS
	OPTIONS_HANDICAP_PLUS, //!< OPTIONS_HANDICAP_PLUS
	OPTIONS_KOMI_MOINS,    //!< OPTIONS_KOMI_MOINS
	OPTIONS_KOMI_PLUS      //!< OPTIONS_KOMI_PLUS
} Boutons;

#define NCHOIXMULTIPLES 4

/**
 * Boutons � choix multiple disponibles dans le jeu.
 */
typedef enum {
	OPTIONS_TYPEJ1,  //!< OPTIONS_TYPEJ1
	OPTIONS_TYPEJ2,  //!< OPTIONS_TYPEJ2
	OPTIONS_HANDICAP,//!< OPTIONS_HANDICAP
	OPTIONS_TAILLE   //!< OPTIONS_TAILLE
} ChoixMultiples;

#define NENTREETEXTE 2

/**
 * Champ de texte disponibles dans le jeu.
 */
typedef enum {
	OPTIONS_NOMJ1,//!< OPTIONS_NOMJ1
	OPTIONS_NOMJ2 //!< OPTIONS_NOMJ2
} EntreesTexte;

typedef struct ContexteGraphique* ContexteGraphique;

/**
 * Cr�e un contexte en mode SDL.
 *
 * @return Le contexte cr��.
 */
ContexteGraphique ContexteGraphique_creer();

/**
 * D�truit un contexte en mode SDL.
 *
 * @param Contexte � d�truire
 */
void ContexteGraphique_detruire(ContexteGraphique ctx);

/**
 * Retourne la surface de la fen�tre du contexte graphique courant.
 *
 * @return Surface de la fen�tre.
 */
SDL_Surface* ContexteGraphique_getWindow();

/**
 * Retourne la largeur de la fen�tre.
 *
 * @return Largeur de la fen�tre.
 */
int ContexteGraphique_getTailleX();

/**
 * Retourne la hauteur de la fen�tre.
 * @return hauteur de la fen�tre.
 */
int ContexteGraphique_getTailleY();

/**
 * R�cup�re un bouton.
 *
 * @param idBouton ID du bouton.
 * @return Le bouton.
 */
Bouton ContexteGraphique_getBouton(Boutons idBouton);

/**
 * R�cup�re un bouton � choix multiple.
 *
 * @param idChoix ID Du bouton � choix multiple.
 * @return Le bouton � choix multiple.
 */
ChoixMultiple ContexteGraphique_getChoixMultiple(ChoixMultiples idChoix);

/**
 * R�cup�reun champ de texte.
 *
 * @param idTexte ID du champ de texte.
 * @return Le champ de texte.
 */
EntreeTexte ContexteGraphique_getEntreeTexte(EntreesTexte idTexte);

#endif
