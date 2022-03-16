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

typedef tFicha tArray[MaxFichas];

struct tSoporte {
	int contador = 0;
	tArray ficha;
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

int menu();
void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna, tFicha& ficha);
void repartir(tBolsa& bolsa, tSoportes& soportes);
void ordenarPorColor(tSoporte& soporte);
void ordenarPorNum(tSoporte& soporte);
int buscar(const tJugada& jugada, const tFicha& ficha);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);
int nuevaJugada(tSoporte& soporte, tJugada& jugada);



int main()
{
	srand(time(NULL));
	return 0;
}

int menu()
{
	int opcion;
	cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
	cin >> opcion;
	cout << opcion << endl;
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
	ficha.color = libre;
	ficha.numero = -1;
	int fila = rand() % 8, columna = rand() % NumFichas;
	if (bolsa.bolsaFicha[fila][columna].color != libre)
	{
		ficha = bolsa.bolsaFicha[fila][columna];

		bolsa.bolsaFicha[fila][columna].color = libre;
		bolsa.bolsaFicha[fila][columna].numero = -1;

		encontrado = true;
	}
	else
	{
		encontrado = recorrerBolsa(bolsa, fila, columna, ficha);

	}
	if (!encontrado)
	{
		fila = 0;
		columna = 0;
		encontrado = recorrerBolsa(bolsa, fila, columna, ficha);
	}
	return ficha;
}

bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna, tFicha& ficha)
{
	bool encontrado = false;
	while (!encontrado && fila < 8)
	{
		while (!encontrado && columna < NumFichas)
		{
			if (bolsa.bolsaFicha[fila][columna].color != libre)
			{
				ficha = bolsa.bolsaFicha[fila][columna];
				bolsa.bolsaFicha[fila][columna].color = libre;
				bolsa.bolsaFicha[fila][columna].numero = -1;
				encontrado = true;
			}
			columna++;
		}
		columna = 0;
		fila++;
	}
	return encontrado;
}

void repartir(tBolsa& bolsa, tSoportes& soportes) {
	int j = 0;
	tFicha ficha;
	for (int i = 0; i < NumJugadores; i++) 
	{
		while (soportes[i].contador < IniFichas) 
		{
			ficha = robar(bolsa);
			soportes[i].ficha[soportes[i].contador] = ficha;
			soportes[i].contador++;
		}
	}
}

void ordenarPorNum(tSoporte& soporte)
{
	int  pos;
	tFicha elemento;
	for (int i = 0; i < MaxFichas; i++) 
	{
		pos = i;
		elemento = soporte.ficha[pos];
		while ((pos > 0) && (elemento.numero < soporte.ficha[pos - 1].numero)) 
		{
			soporte.ficha[pos] = soporte.ficha[pos - 1];
			pos--;
		}
		soporte.ficha[pos] = elemento;
	}

}


void ordenarPorColor(tSoporte& soporte)
{
	int  pos;
	tFicha elemento;
	for (int i = 0; i < MaxFichas; i++) 
	{
		pos = i;
		elemento = soporte.ficha[pos];

		while ((pos > 0) && (elemento.color < soporte.ficha[pos - 1].color)) 
		{
			soporte.ficha[pos] = soporte.ficha[pos - 1];
			pos--;
		}
		soporte.ficha[pos] = elemento;
	}
}
int buscar(const tJugada& jugada, const tFicha& ficha)
{
	bool encontrado = false;
	int vueltas = 0, indice = -1;
	while(!encontrado && vueltas < NumFichas + 1)
	{
		if(jugada[vueltas].color == ficha.color && jugada[vueltas].numero == ficha.numero)
		{
			indice = vueltas;
			encontrado = true;
		}
		vueltas++;
	}
	return indice;
}
void eliminaFichas(tSoporte& soporte, const tJugada& jugada)
{
	for(int i = 0; i < soporte.contador; i++)
	{
		if(buscar(jugada, soporte.ficha[i]) != -1)
		{
			soporte.ficha[i].color = libre;
			soporte.ficha[i].numero = -1;
		}
	}
}

int nuevaJugada(tSoporte& soporte, tJugada& jugada)
{

}

void mostrarFicha(const tFicha& ficha)
{
	colorTexto(ficha.color);
	cout << 
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





