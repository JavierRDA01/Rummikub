
#ifndef BOLSA_H
#define BOLSA_H
#include "Fichas.h"
#include "Soportes.h"
typedef tFicha tBolsaFicha[8][NumFichas];

struct tBolsa
{
	tBolsaFicha bolsaFicha;
	int contador = 0;
};

void inicializarBolsa(tBolsa& bolsa);//Inicializa la bolsa poniendo todas las fichas posibles segun el parámetro numFichas
void repartir(tBolsa& bolsa, tSoportes& soportes);//Reparte las fichas iniciales a todos los jugadores
tFicha robar(tBolsa& bolsa);//Roba si se puede, una ficha de la bolsa y la añade al soporte. Elimina la ficha de la bolsa
void mostrarBolsa(const tBolsa& bolsa);//Muestra la bolsa, enseñando las fichas que quedan y las que faltan
bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna);//Es llamada por la función robar(). Recorre la bolsa en busca de una ficha
void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int turno);//Roba una ficha de la bolsa y la coloca en el soporte

#endif
