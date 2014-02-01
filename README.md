Instructions de compilation
=====================

Windows
-----------------------

    make -f Makefile.win
    make -f Makefile.win install

L'ensemble de l'environnement d'exécution sera placé dans GO/bin.

Prérequis :

* MingW ou similaire
* Dossier des headers de la SDL dans GO/include
* Fichiers dans GO/lib : (Livrés avec SDL1.2-dev)
	* libSDL.dll.a
	* libSDLmain.a
	* SDL.dll
	* SDL_image.dll
	* SDL_image.lib
	* SDL_ttf.dll
	* SDL_ttf.lib
* Fichiers dans GO/installlibs/windows : (Livrés avec SDL1.2-dev)
	* libfreetype-6.dll
	* libjpeg-8.dll
	* libpng15-15.dll
	* libtiff-5.dll
	* libwebp-2.dll
	* zlib1.dll

Linux
--------------------------------

    make -f Makefile.linux
    make -f Makefile.linux install

L'ensemble de l'environnement d'exécution sera placé dans GO/bin. Veuillez installer libmatrice.so présent dans ce dossier dans un dossier scanné par LD_LIBRARY_PATH.

Prérequis :

* SDL 1.2 (version de développement)
* SDL_image 1.2 (version de développement)
* SDL_ttf 1.2 (version de développement)

Développement
=========================

libmatrice
------------------------------

* src/ Fichiers .c  
	* include/ Fichiers .h

GO
------------------------------

* src/ Fichiers.c
	* include/ Fichier.h
* lib/ Librairies nécessaires (SDL, SDL_image, SDL_ttf, matrice)
* include/ Headers des librairies
* assets/ Ressources (images, sons, polices)

Conventions
------------------------------

* En français (Pas super mais étant donné les prototypes donnés...)
* CamelCase
* `Type_nomDeLaFonction(...);` (ex `Matrice_creer(...);`)
