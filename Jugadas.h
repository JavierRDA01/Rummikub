
#ifndef JUGADAS_H
#define JUGADAS_H
#include "Constantes.h"
#include "Soporte.h"

typedef tFicha tJugada[NumFichas + 1];
typedef tJugada tArrayJugadas[MaxJugadas];

void eliminarFichas(tSoporte& soporte, const tJugada& jugada);//Elimina una ficha de un soporte
int buscar(const tJugada& jugada, const tFicha& ficha);//Busca una ficha dentro de una jugada. Si la encuentra, devulve su índice
int nuevaJugada(tSoporte& soporte, tJugada& jugada);//Permite hacer y comprobar si se puede hacer directamente una jugada desde el soporte
bool coloresRepetidos(tJugada& jugada);//Comprueba si hay por lo menos dos fichas del mismo color en una jugada
void mostrarJugada(const tJugada& jugada);//Muestra las fichas de una jugada
bool ponerFicha(tJugada& jugada, tFicha& ficha);//Comprueba si es posible poner una ficha en una jugada a elegir del tablero. Si es así la pone.

#endif
