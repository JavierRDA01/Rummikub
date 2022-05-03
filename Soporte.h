#ifndef SOPORTE_H
#define SOPORTE_H
#include "Fichas.h"
#include "Jugadas.h"
struct tSoporte {
	int contador = 0;
	tArrayFichas ficha;
};
void mostrarSoporte(const tSoporte& soporte);//Muestra el soporte de un jugador
void ordenarPorColor(tSoporte& soporte);//Ordena las fichas por color. Una vez ordenadas, ordena las fichas del mismo color por números
void ordenarPorNum(tSoporte& soporte);//Ordena las fichas por números. Una vez ordenadas, ordena las fichas del mismo número por color.
void mostrarSeries(tSoporte& soporte);//Muestra todas las posibles series que se pueden colocar directamentes desde un soporte
void mostrarEscaleras(tSoporte& soporte); // Muestra todas las posibles escaleras que se pueden colocar directamentes desde un soporte
void mostrarIndice(int numFichasSoporte);//Muestra el ínidce de las fichas que se pueden jugar del soporte
#endif
