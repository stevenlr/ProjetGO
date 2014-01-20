/**
 * @file Tutoriel.c
 * @brief Fonctions du Tutoriel
 */

#include <stdio.h>

struct Tutoriel {
	Liste plateaux;
	Liste chaines;
};

int Tutoriel_convertirTexteVersBinaire()
{
	char c;
	char chaine[400];
	FILE* fichier, fichier2;
	int n = 0, taille;

	fichier = fopen("../assets/Tutoriel.txt", "r");
	fichier2 = fopen("../assets/Tutoriel.bin", "w");

	if(fichier == NULL || fichier == NULL)
		return 0;

	while((c = fgetc(fichier)) != EOF)
	{
		if(c != '\n')
			fwrite(&c, sizeof(char), 1, fichier2);
		else
		{
			n++;

			if(n % 9 == 0)
			{
				fgets(chaine, 400, fichier);

				taille = strlen(chaine) - 1;
				chaine[taille] = '\0';	//Censé enlever le \n

				fwrite(&taille, sizeof(int), 1, fichier2);		//Stocke la taille de la chaine
				fwrite(chaine, sizeof(char), taille, fichier2);	//Stocke la chaine de taille "taille".
			}
		}
	}

	return ferror(fichier2);
}

void Tutoriel_charger(Partie partie)
{
	/**
	 * @todo Charger ce magnifique .bin (Easy, mais notime ! Je dois bosser mes exams o/)
	 */
}
