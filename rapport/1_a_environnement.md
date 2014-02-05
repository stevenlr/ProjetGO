
Environnement de développement
======================================

Le programme a été réalisé principalement sous Windows, avec l'IDE Eclipse et l'environnement MingW. Nous avons utilisé la librairie SDL 1.2 ainsi que ses addons SDL_image et SDL_ttf. La librairie matrice écrite en TP a été réécrite pour correspondre aux conventions établies pour ce projet. Nous avons utilisé Git comme système de versionnage afin de faciliter le travail depuis de multiples stations de travail, et GitHub comme dépôt central. (http://github.com/stevenlr/ProjetGO)

Chaque sous projet était organisé comme ceci : un dossier `assets` contenant les images, les fontes et autres ressources, un dossier `lib` contenant les librairies nécessaires à la compilation, un dossier `include` contenant les fichiers d'en-tête des librairies et un dossier `src` contenant le code source et un dossier `include` contenant les en-têtes.

Des conventions d'écriture ont été adoptées : nous avons utilisé le CamelCase, le code était écrit le plus possible en français (à l'exception des mots `get` et `set`) et les prototypes de fonctions suivaient le style `Type_nomFonction` où `Type` est le type sur lequel opère la fonction.

Les fichiers sources étant organisés en sous-dossiers, un fichier `Makefile` a été placé dans chaque dossier en appelant un autre commun à tous ceux-ci contenant les instructions de compilation pour chaque sous dossiers. Tous les fichiers objets générés étaient alors placés dans un dossiers `obj` d'où ils étaient assemblés en l'exécutable final. Les instructions de compilation sont spécifiées dans le fichier README.md.

Ce rapport a été écrit en Markdown puis compilé en LaTeX puis en PDF grâce à l'utilitaire Pandoc.

