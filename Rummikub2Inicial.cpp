// Autor/a: Hugo Aguilera y Javier Ramírez de Andrés
//Hemos cambiado tanto en mostrarSeries como en mostrarEscaleras el paso del soporte. En vez de pasarlo con un const lo hemos pasado por referencia. Esto es para poder ordenarlos por color o por número para que el algoritmo sea más fácil. Hemos contado con la aprobación del profesor en la sala de prácticas 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <crtdbg.h>
#include <cstdlib>


using namespace std;

const int NumJugadores = 3;
const int NumFichas = 9;
const int IniFichas = 7;
const int MaxFichas = 50;
const int MaxJugadas = NumFichas * 2;

typedef enum { rojo, verde, azul, amarillo, blanco, libre }tColor;

struct tFicha {
	int numero = -1;
	tColor color = libre;
};

typedef tFicha* ptrFicha;

struct tSoporte {
	int contador = 0;
	int capacidad = 8;
	ptrFicha fichas;
};
typedef ptrFicha tArrayBolsaFichas[8][NumFichas];
struct tBolsa
{
	int contador = 0;
	tArrayBolsaFichas ficha;
};
typedef tSoporte tSoportes[NumJugadores];


typedef tFicha tJugada[NumFichas + 1];
typedef tJugada* tArrayJugadas[MaxJugadas];

struct tTablero
{
	tArrayJugadas jugada;
	int contador = 0;
};

int menu();//Muestra el menu
void inicializarBolsa(tBolsa& bolsa);//Inicializa la bolsa poniendo todas las fichas posibles segun el parámetro numFichas
void repartir(tBolsa& bolsa, tSoportes& soportes);//Reparte las fichas iniciales a todos los jugadores
tFicha* robar(tBolsa& bolsa);//Roba si se puede, una ficha de la bolsa y la añade al soporte. Elimina la ficha de la bolsa
void mostrarBolsa(const tBolsa& bolsa);//Muestra la bolsa, enseñando las fichas que quedan y las que faltan
void mostrarSoporte(const tSoporte& soporte);//Muestra el soporte de un jugador
void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int turno);//Roba una ficha de la bolsa y la coloca en el soporte
void colorTexto(tColor color);//Da color a la ficha según el tipo definido tColor
void mostrarFicha(tFicha* ficha);// Muestra el color y el número de una ficha




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
	mostrarBolsa(bolsa);
	//do//Mientras que el turno no sea -1 el bucle reproduce todas las jugadas
	//{
	//	opcion = menu();
	//	if (opcion == 0)
	//	{
	//		if (!haJugado)
	//		{
	//			obtenerFicha(bolsa, soportes, turno);
	//		}
	//		haJugado = false;
	//		mostrarSoporte(soportes[turno]);
	//		turno = avanzarTurno(turno);
	//		cout << "Turno para el jugador " << turno + 1 << " ..." << endl << endl;
	//		mostrarTablero(tablero);
	//		mostrarSoporte(soportes[turno]);
	//	}
	//	else if (opcion == 1)
	//	{
	//		ordenarPorNum(soportes[turno]);
	//		mostrarSoporte(soportes[turno]);
	//	}
	//	else if (opcion == 2)
	//	{
	//		ordenarPorColor(soportes[turno]);
	//		mostrarSoporte(soportes[turno]);
	//	}
	//	else if (opcion == 3)
	//	{
	//		mostrarEscaleras(soportes[turno]);
	//		mostrarSeries(soportes[turno]);
	//		mostrarSoporte(soportes[turno]);
	//	}
	//	else if (opcion == 4)
	//	{
	//		haJugado = jugar(tablero, soportes[turno]);
	//		mostrarSoporte(soportes[turno]);

	//		if (soportes[turno].contador == 0)
	//		{
	//			ganador = true;
	//			cout << "El Jugador " << turno + 1 << " ha ganado!!" << endl;
	//		}
	//	}
	//} while (!ganador && (opcion >= 0 && opcion <= 4));
	_CrtDumpMemoryLeaks();
	return 0;
}
int menu()//Muestra el menu
{
	int opcion;
	cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
	cin >> opcion;//El jugador elige la accion que quiere llevar a cabo de entre las 4 que ofrece el menu
	return opcion;
}

void inicializarBolsa(tBolsa& bolsa)//Inicializa la bolsa poniendo todas las fichas posibles segun el parámetro numFichas
{
	tFicha auxFicha;
	for (int i = 0; i < 8; i++)//Por cada fila
	{
		for (int j = 0; j < NumFichas; j++)//Por cada columna
		{
			auxFicha.numero = j + 1;//Rellena cada ficha con su número corresponiente

			if (i < 4)//Rellena cada ficha con su color correspondiente.
			{
				auxFicha.color = tColor(i);//Si es menor que 4 coge el color de i
			}
			else
			{
				auxFicha.color = tColor(i - 4);//Si es mayor que 4 vuelve a rellenar desde el primer color para que haya 2 fichas de cada color con el mismo número
			}
			bolsa.ficha[i][j] = new tFicha(auxFicha);
		}
	}
}
void mostrarSoporte(const tSoporte& soporte)//Muestra el soporte de un jugador
{
	cout << "Soporte: ";
	for (int i = 0; i < soporte.contador; i++)//Recorre el soporte
	{
		mostrarFicha(soporte.fichas[i]);//Muestra la ficha recorrida
	}
	cout << endl;
}
void mostrarFicha(tFicha* ficha)// Muestra el color y el número de una ficha
{
	colorTexto(ficha->color);
	if (ficha->color != blanco);
	{
		cout << " ";
	}
	cout << ficha->numero << "  ";//Muestra el color y el número de la ficha
	colorTexto(blanco);
}
void mostrarBolsa(const tBolsa& bolsa)//Muestra la bolsa, enseñando las fichas que quedan y las que faltan
{
	cout << endl << "Bolsa..." << endl;
	for (int i = 0; i < 8; i++)//Recorre por filas
	{
		for (int j = 0; j < NumFichas; j++)//Recorre por columnas
		{
			if (bolsa.ficha[i][j] == NULL)//Si no hay ficha muestra un -1
			{
				cout << "-1" << "  ";
			}
			else//Si hay ficha muestra la ficha
			{
				mostrarFicha(bolsa.ficha[i][j]);
			}
		}
		cout << endl;
	}
}
tFicha* robar(tBolsa& bolsa)//Roba si se puede, una ficha de la bolsa y la añade al soporte. Elimina la ficha de la bolsa
{
	bool encontrado = false;
	int iniFila, iniColumna,fila,columna;
	tFicha* ficha = NULL;
	iniFila = rand() % 8;
	iniColumna = rand() % NumFichas;
	fila = iniFila;
	columna = iniColumna;
	if (bolsa.ficha[iniFila][iniColumna] == NULL) //Si la ficha de la posición introducida está libre, entonces busca la siguiente icha a partir de esa posición
	{
		while (!encontrado && fila < 8)//Se repite mientras que no haya encontrado la ficha y mientras que no haya llegado al final del array
		{
			while (!encontrado && columna < NumFichas)//Mientras que no haya llegado al final de la columna y no se haya encontrado la ficha
			{
				if (bolsa.ficha[fila][columna] != NULL)//Si la posición no está vacía, encuentra la ficha y el bucle se detiene
				{
					encontrado = true;
				}
				else
				{
					columna++;//Si no la encuentra pasa a la asiguiente posición
				}
				
			}
			if (!encontrado)//Vuelta del bucle
			{
				columna = 0;
				fila++;
			}
		}
	}
	else
	{
		encontrado = true;//Si encuentra la ficha
	}
	if (!encontrado)//Si no encuentra la ficha comienza a buscar desde el principio
	{
		fila = 0;
		columna = 0;
		while (!encontrado && fila < iniFila)//Se repite mientras que no haya encontrado la ficha y mientras que no haya llegado al final del array
		{
			while (!encontrado && columna < iniColumna)//Mientras que no haya llegado al final de la columna y no se haya encontrado la ficha
			{
				if (bolsa.ficha[fila][columna] != NULL)//Si la posición no está vacía, encuentra la ficha y el bucle se detiene
				{
					encontrado = true;
				}
				else
				{
					columna++;//Si no la encuentra pasa a la asiguiente posición
				}
			}
			if (!encontrado)//Vuelta del bucle
			{
				columna = 0;
				fila++;
			}
		}
	}
	if (encontrado)
	{
		ficha = bolsa.ficha[fila][columna];//Si finalmente encuentra la ficha, coge la ficha a partir de la posición encontrada
		bolsa.ficha[fila][columna] = NULL;
	}
	return ficha;
}
void repartir(tBolsa& bolsa, tSoportes& soportes)//Reparte las fichas iniciales a todos los jugadores
{
	for (int i = 0; i < NumJugadores; i++)//Una vuelta por cada jugador
	{
		for (int j = 0; j < IniFichas; j++)//Vuelta por cada ficha del soporte
		{
			obtenerFicha(bolsa, soportes, i);//Roba la ficha y la pone en el soporte correspondiente
		}
	}
}
void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int turno)//Roba una ficha de la bolsa y la coloca en el soporte
{
	if (soportes[turno].contador < MaxFichas)//Si el soporte no llega a su máxima capacidad
	{
		soportes[turno].fichas[soportes[turno].contador] = robar(bolsa);//Roba la ficha y la añade a su soporte
		soportes[turno].contador++;//Suma el contador en 1
	}
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

void nuevaFicha(tSoporte& soporte, tFicha ficha)
{
	tFicha *auxFichas;
	if(soporte.contador == soporte.capacidad)
	{
		soporte.capacidad = soporte.capacidad + 8;
		auxFichas = new tFicha[soporte.capacidad];

		for(int i = 0; i < soporte.contador;i++)
		{
			auxFichas[i] = soporte.fichas[i];
		}
		delete[] soporte.fichas;

		soporte.fichas = auxFichas;
	}
	soporte.fichas[soporte.contador] = ficha;
	soporte.contador++;
}
void delBolsa(tBolsa& bolsa)
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < NumFichas;j++)
		{
			delete[] bolsa.ficha[i][j];
		}
	}
}
void colorTexto(tColor color)//Da color a la ficha según el tipo definido tColor
{
	switch (color) {
	case amarillo:
		cout << "\033[1;40;33m";
		break;
	case azul:
		cout << "\033[40;34m";
		break;
	case rojo:
		cout << "\033[40;31m";
		break;
	case verde:
		cout << "\033[40;32m";
		break;
	case blanco:
		cout << "\033[40;37m";
		break;
	}
}
