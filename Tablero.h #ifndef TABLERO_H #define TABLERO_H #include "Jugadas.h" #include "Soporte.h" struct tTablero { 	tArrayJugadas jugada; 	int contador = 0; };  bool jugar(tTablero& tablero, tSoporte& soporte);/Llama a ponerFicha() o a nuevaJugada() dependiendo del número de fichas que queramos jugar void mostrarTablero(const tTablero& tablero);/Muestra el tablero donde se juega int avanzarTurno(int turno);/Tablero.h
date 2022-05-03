
#ifndef TABLERO_H
#define TABLERO_H
#include "Jugadas.h"
#include "Soporte.h"
struct tTablero
{
	tArrayJugadas jugada;
	int contador = 0;
};

bool jugar(tTablero& tablero, tSoporte& soporte);//Llama a ponerFicha() o a nuevaJugada() dependiendo del número de fichas que queramos jugar
void mostrarTablero(const tTablero& tablero);//Muestra el tablero donde se juega
int avanzarTurno(int turno);//Una vez termina la jugada, se pasa turno al siguiente jugador

#endif
