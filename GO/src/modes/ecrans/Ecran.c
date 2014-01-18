/**
 * @file Ecrans.c
 * @brief 
 */

#include <stdlib.h>

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranJeu.h"

static TypeEcran idEcran = NONE;
static TypeEcran idProchainEcran;

TypeEcran Ecran_getID()
{
	return idEcran;
}

TypeEcran Ecran_getIDProchain()
{
	return idProchainEcran;
}

void Ecran_setIDProchain(TypeEcran type)
{
	idProchainEcran = type;
}

int Ecran_doitChanger()
{
	return idEcran != idProchainEcran;
}

void Ecran_changer()
{
	idEcran = idProchainEcran;
}

FonctionMainEcran Ecran_getFonctionMain()
{
	switch(idEcran)
	{
		case NONE:
			return NULL;
		case JEU:
			return EcranJeu_main;
			break;
		default:
			return NULL;
			break;
	}
}
