#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

const int NumJugadores = 3;
const int  NumFichas = 10;
const int IniFichas = 7;
const int MaxFichas = 50;
const int MaxJugadas = NumFichas * 2;

typedef enum { rojo, verde, azul, amarillo, blanco, libre }tColor;

struct tFicha {
	int numero;
	tColor color;
};

typedef tFicha tArrayFichas[MaxFichas];

struct tSoporte {
	int contador = 0;
	tArrayFichas ficha;
};

typedef tSoporte tSoportes[NumJugadores];

typedef tFicha tBolsaFicha[8][NumFichas];

struct tBolsa
{
	tBolsaFicha bolsaFicha;
	int contador = 0;
};

typedef tFicha tJugada[NumFichas + 1];
typedef tJugada tArrayJugadas[MaxJugadas];

struct tTablero
{
	tArrayJugadas jugada;
	int contador = 0;
};

void inicializarBolsa(tBolsa& bolsa);

tFicha robar(tBolsa& bolsa);

void recorrerBolsa(tFicha ficha, tBolsa& bolsa, int fila, int columna);

void colorTexto(tColor color);


int main()
{
	srand(time(NULL));
	return 0;
}

int menu()
{

}

void inicializarBolsa(tBolsa& bolsa)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < NumFichas; j++)
		{
			bolsa.bolsaFicha[i][j].numero = j + 1;

			if (i < 4)
				bolsa.bolsaFicha[i][j].color = tColor(i);

			else
				bolsa.bolsaFicha[i][j].color = tColor(i - 4);
		}
	}
}

tFicha robar(tBolsa& bolsa)
{
	bool encontrado = false;
	tFicha ficha;
	int fila = rand() % 8, columna = rand() % NumFichas;
	if (bolsa.bolsaFicha[fila][columna].color != libre)
	{
		ficha = bolsa.bolsaFicha[fila][columna];
		encontrado = true;
	}
	else
	{
		recorrerBolsa(ficha,bolsa, fila, columna);
	}
	if (!encontrado)
	{
		fila = 0;
		columna = 0;
		recorrerBolsa(ficha,bolsa, fila, columna);
	}
	return ficha;
}

void recorrerBolsa(tFicha ficha,tBolsa& bolsa, int fila, int columna)
{
	bool encontrado = false;
	while (!encontrado && fila < 8)
	{
		while (!encontrado && columna < NumFichas)
		{
			if (bolsa.bolsaFicha[fila][columna].color != libre)
			{
				ficha = bolsa.bolsaFicha[fila][columna];
				encontrado = true;
			}
			columna++;
		}
		columna = 0;
		fila++;
	}
}

void repartir(tBolsa& bolsa, tSoportes& soportes)
{
	int numVueltas = 0;
	for(int i = 0; i < NumJugadores; i++)
	{
		for(int j = 0; j < IniFichas; j++)
		{
			soportes[i].ficha = robar(bolsa);
			soportes[i].contador++;
		}
	}
}

void colorTexto(tColor color)
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

