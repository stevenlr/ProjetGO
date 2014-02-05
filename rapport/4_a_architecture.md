
Architecture du programme
==============================

Le programme a été structuré de façon à rendre l'implémentation des contextes console et graphique la plus séparée possible de la logique du jeu et à éliminer le maximum de redondances.

Les écrans et leurs états
--------------------------------

Le programme fonctionne comme une machine à états, chaque état étant un écran. Les écrans sont : le menu, le tutoriel, les options de partie et le jeu. Chaque écran est donc une partie différente du programme qui se caractérise par une logique, des entrées et des sorties différentes. Ainsi chaque écran possède sa fonction logique (exemple `EcranJeu_main`) et des fonctions d'interface dont nous reparlerons plus tard. Chaque écran possède également ses états, c'est-à-dire des variables statiques à l'écran en cours qui définissent par exemple si on doit continuer à exécuter l'écran actuel, dans quelle partie on se trouve actuellement, etc. Les états sont initialisés à l'initialisation de l'écran. Lorsque le programme doit passer à un autre écran, l'écran courant initialise l'écran suivant avec éventuellement les paramètres associés, puis s'auto-détruit. Le gestionnaire d'écrans est alors notifié du changement et, à moins que la fermeture de l'application soit demandée, va lancer la fonction `main` du nouvel écran.

Les contextes
--------------------------------

Etant donné le besoin de pouvoir exécuter le programme à la fois en console et en mode graphique, il a fallu séparer au maximum ce qui était spécifique au contexte d'exécution de la logique du jeu, afin d'éviter toute redondance. Ainsi deux contextes sont définis : le contexte graphique et le contexte console. Au début du programme, le contexte d'exécution est choisi et initialisé. L'initialisation permet par exemple dans le cas du contexte graphique d'ouvrir la fenêtre, de charger les textures, de créer les boutons, etc. De même, à la fin du programme le contexte est détruit. Une structure similaire aux états pour les écrans contient les variables utiles à l'exécution du contexte dans la suite de l'application. Par exemple, le contexte graphique contient le pointeur `SDL_Surface` représentant l'écran.

Les interfaces
--------------------------------

Pour pouvoir interagir en entrée et en sortie avec l'utilisateur, nous avons défini des interfaces. Chaque écran possède une interface de sortie et une d'entrée pour chacun des contextes. Ces fonctions ont connaissance des états mais ne peuvent pas les modifier. En effet, elles ne gèrent strictement que les entrées et sorties et ne doivent en aucun cas avoir conscience de la logique du jeu.

Les événements
--------------------------------

Afin donc de pouvoir faire évoluer les états de jeu, les interfaces appellent des fonctions événements. Chaque écran possède ses propres fonctions d'événements. Par exemple pour l'écran de jeu : un événement pour la pose d'un pion, un pour l'enregistrement de la partie, un pour le retour à un tour précédent, etc. Ces fonctions sont alors le cœur de la logique du jeu.
