
#include <stdlib.h>

#include "include/modes/contextes/ContexteConsole.h"

struct ContexteConsole {
	char estDefini;
};

ContexteConsole ContexteConsole_creer()
{
	ContexteConsole contexte;

	contexte = malloc(sizeof(ContexteConsole));

	return contexte;
}

void ContexteConsole_detruire(ContexteConsole contexte)
{
	free(contexte);
}
