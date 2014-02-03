/**
 * @file ContexteConsole.h
 * @brief 
 */

#ifndef CONTEXTECONSOLE_H_
#define CONTEXTECONSOLE_H_

typedef struct ContexteConsole* ContexteConsole;

/**
 * Créé le contexte du jeu en mode console.
 * @return
 */
ContexteConsole ContexteConsole_creer();

/**
 * Détruit le contexte du jeu en mode console.
 * @param contexte
 */
void ContexteConsole_detruire(ContexteConsole contexte);

#endif
