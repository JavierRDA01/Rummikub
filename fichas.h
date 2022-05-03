
#ifndef FICHAS_H
#define FICHAS_H
#include "Colores.h"
#include "Constantes.h"
struct tFicha {
	int numero = -1;
	tColor color = libre;
};

typedef tFicha tArrayFichas[MaxFichas];
void mostrarFicha(const tFicha& ficha);//Muestra el color y el número de una ficha
#endif
