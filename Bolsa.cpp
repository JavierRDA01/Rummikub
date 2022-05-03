#include <iostream>
#include <string>

#include "Bolsa.h"
using namespace std;

void inicializarBolsa(tBolsa& bolsa)//Inicializa la bolsa poniendo todas las fichas posibles segun el parámetro numFichas
{
	for (int i = 0; i < 8; i++)//Por cada fila
	{
		for (int j = 0; j < NumFichas; j++)//Por cada columna
		{
			bolsa.bolsaFicha[i][j].numero = j + 1;//Rellena cada ficha con su número corresponiente

			if (i < 4)//Rellena cada ficha con su color correspondiente.
			{
				bolsa.bolsaFicha[i][j].color = tColor(i);//Si es menor que 4 coge el color de i
			}
			else
			{
				bolsa.bolsaFicha[i][j].color = tColor(i - 4);//Si es mayor que 4 vuelve a rellenar desde el primer color para que haya 2 fichas de cada color con el mismo número
			}
		}
	}

}

tFicha robar(tBolsa& bolsa)//Roba si se puede, una ficha de la bolsa y la añade al soporte. Elimina la ficha de la bolsa
{
	bool encontrado = false;
	int iniFila, iniColumna, fila, columna;
	tFicha ficha;
	ficha.color = libre;//Inicializamos la ficha
	ficha.numero = -1;//Inicializamos la ficha
	iniFila = rand() % 8;
	iniColumna = rand() % NumFichas;
	fila = iniFila;
	columna = iniColumna;
	if (bolsa.bolsaFicha[fila][columna].numero == -1) //Si la ficha de la posición introducida está libre, entonces busca la siguiente icha a partir de esa posición
	{
		while (!encontrado && fila < 8)//Se repite mientras que no haya encontrado la ficha y mientras que no haya llegado al final del array
		{
			while (!encontrado && columna < NumFichas)//Mientras que no haya llegado al final de la columna y no se haya encontrado la ficha
			{
				if (bolsa.bolsaFicha[fila][columna].numero != -1)//Si la posición no está vacía, encuentra la ficha y el bucle se detiene
				{
					encontrado = true;
				}
				if (!encontrado)
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
				if (bolsa.bolsaFicha[fila][columna].numero != -1)//Si la posición no está vacía, encuentra la ficha y el bucle se detiene
				{
					encontrado = true;
				}
				if (!encontrado)
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
		ficha = bolsa.bolsaFicha[fila][columna];//Si finalmente encuentra la ficha, coge la ficha a partir de la posición encontrada
		bolsa.bolsaFicha[fila][columna].color = libre;//Libera la posición donde esta guardada la ficha cogida
		bolsa.bolsaFicha[fila][columna].numero = -1;
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
		soportes[turno].ficha[soportes[turno].contador] = robar(bolsa);//Roba la ficha y la añade a su soporte
		soportes[turno].contador++;//Suma el contador en 1
	}
}

void mostrarBolsa(const tBolsa& bolsa)//Muestra la bolsa, enseñando las fichas que quedan y las que faltan
{
	cout << endl << "Bolsa..." << endl;
	for (int i = 0; i < 8; i++)//Recorre por filas
	{
		for (int j = 0; j < NumFichas; j++)//Recorre por columnas
		{
			if (bolsa.bolsaFicha[i][j].color == libre || bolsa.bolsaFicha[i][j].numero == -1)//Si no hay ficha muestra un -1
			{
				cout << "-1" << "  ";
			}
			else//Si hay ficha muestra la ficha
			{
				mostrarFicha(bolsa.bolsaFicha[i][j]);
			}
		}
		cout << endl;
	}
}
