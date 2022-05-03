#include "Tablero.h"

#include <string>
#include <iostream>
using namespace std;

void mostrarTablero(const tTablero& tablero)// Muestra el tablero donde se juega
{
	cout << "Tablero:";
	if (tablero.contador == 0)
	{
		cout << " No hay jugadas" << endl;
	}
	else
	{
		cout << endl;
		for (int i = 0; i < tablero.contador; i++)//Recorre todas las jugadas del tablero
		{
			cout << i + 1 << ": ";
			mostrarJugada(tablero.jugada[i]);//Muestra la jugada recorrida
			cout << endl;

		}
	}
	cout << endl;
}
int avanzarTurno(int turno)//Una vez termina la jugada, se pasa turno al siguiente jugador
{
	if (turno == NumJugadores - 1)//Vuelve al primer jugador si el turno era del útlimo jugador
	{
		turno = 0;
	}
	else//Avanza turno si no era el turno del último jugador 
	{
		turno++;
	}
	return turno;
}
bool jugar(tTablero& tablero, tSoporte& soporte)//Llama a ponerFicha() o a nuevaJugada() dependiendo del número de fichas que queramos jugar
{
	tFicha ficha;
	tJugada jugada;
	int numFichasJugada, numJugada = 0, posicionFichaJugada = 0, numFichaDeLaJugada = 0, i = 0;
	bool hayJugada = false;
	while (jugada[i].numero != -1)//Cada vez que se invoca jugar se debe inicializar la jugada
	{
		jugada[i].numero = -1;
		jugada[i].color = libre;
		i++;
	}
	i = 0;
	numFichasJugada = nuevaJugada(soporte, jugada);//Invoca a nueva jugada
	if (numFichasJugada > 2 && tablero.contador < MaxJugadas)//Si el jugador ha introducido una jugada
	{
		while (jugada[posicionFichaJugada].numero != 0)//Pone la jugada creada en nuevaJugada en el lugar del tablero que le corresponde
		{
			tablero.jugada[tablero.contador][posicionFichaJugada] = jugada[posicionFichaJugada];
			posicionFichaJugada++;
		}
		tablero.contador++;
		hayJugada = true;
	}

	else if (numFichasJugada == 1)//Si el jugador solo ha introducido una ficha
	{
		ficha = jugada[0];//La ficha será igual al primer ínidice de la jugada introducida en la función nueva jugada
		cout << endl << "Jugadas del tablero donde poner la ficha: ";
		cin >> numJugada;//Introduce la jugada donde quiere poner la ficha
		numJugada = numJugada - 1;
		hayJugada = ponerFicha(tablero.jugada[numJugada], ficha);//Si es posible la pone y si no pasa y da un mensaje de error
		if (hayJugada)
		{
			cout << " -> Colocada!";
			eliminarFichas(soporte, tablero.jugada[numJugada]);
		}
		else
		{
			cout << " -> Ficha incorrecta!";
		}
		cout << endl << endl;
	}
	else if (numFichasJugada == 2)
		cout << "Jugada no valida" << endl;

	mostrarTablero(tablero);
	return hayJugada;
}
