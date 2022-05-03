// Autor/a: Hugo Aguilera y Javier Ramírez de Andrés
//Hemos cambiado tanto en mostrarSeries como en mostrarEscaleras el paso del soporte. En vez de pasarlo con un const lo hemos pasado por referencia. Esto es para poder ordenarlos por color o por número para que el algoritmo sea más fácil. Hemos contado con la aprobación del profesor en la sala de prácticas 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>

#include "Bolsa.h"
#include "Colores.h"
#include "Constantes.h"
#include "Fichas.h"
#include "Jugadas.h"
#include "Soporte.h"
#include "Soportes.h"
#include "Tablero.h"

using namespace std;

int menu();//Muestra el menu
int main()
{
	tBolsa bolsa;
	tSoportes soportes;
	tTablero tablero;
	bool haJugado = false, ganador = false;
	int opcion = 0, turno = 0, numJugada = 0;

	srand(time(NULL));
	inicializarBolsa(bolsa);//Rellena la bolsa con las fichas iniciales
	repartir(bolsa, soportes);
	//Reparte las fichas

	cout << endl << "Turno para el jugador " << turno + 1 << " ..." << endl << endl;
	mostrarSoporte(soportes[turno]);//Bucle de jugadas
	do//Mientras que el turno no sea -1 el bucle reproduce todas las jugadas
	{
		opcion = menu();
		if (opcion == 0)
		{
			if (!haJugado)
			{
				obtenerFicha(bolsa, soportes, turno);
			}
			haJugado = false;
			mostrarSoporte(soportes[turno]);
			turno = avanzarTurno(turno);
			cout << "Turno para el jugador " << turno + 1 << " ..." << endl << endl;
			mostrarTablero(tablero);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 1)
		{
			ordenarPorNum(soportes[turno]);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 2)
		{
			ordenarPorColor(soportes[turno]);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 3)
		{
			mostrarEscaleras(soportes[turno]);
			mostrarSeries(soportes[turno]);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 4)
		{
			haJugado = jugar(tablero, soportes[turno]);
			mostrarSoporte(soportes[turno]);

			if (soportes[turno].contador == 0)
			{
				ganador = true;
				cout << "El Jugador " << turno + 1 << " ha ganado!!" << endl;
			}
		}
	} while (!ganador && (opcion >= 0 && opcion <= 4));

	return 0;
}


int menu()//Muestra el menu
{
	int opcion;
	cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
	cin >> opcion;//El jugador elige la accion que quiere llevar a cabo de entre las 4 que ofrece el menu
	return opcion;
}
