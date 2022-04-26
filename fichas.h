#include "colores.h"
#ifndef FICHAS_H
#define FICHAS_H

struct tFicha {
	int numero = -1;
	tColor color = libre;
};

typedef tFicha tArrayFichas[MaxFichas];

#endif
