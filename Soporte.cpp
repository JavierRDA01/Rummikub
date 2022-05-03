#include "Soporte.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void mostrarSoporte(const tSoporte& soporte)//Muestra el soporte de un jugador
{
	cout << "Soporte: ";
	for (int i = 0; i < soporte.contador; i++)//Recorre el soporte
	{
		mostrarFicha(soporte.ficha[i]);//Muestra la ficha recorrida
	}
	cout << endl;
}
void ordenarPorNum(tSoporte& soporte)//Ordena las fichas por números. Una vez ordenadas, ordena las fichas del mismo número por color.
{
	int  pos;
	tFicha elemento;
	for (int i = 1; i < soporte.contador; i++)//Inicio
	{
		pos = i;
		while (pos > 0 && soporte.ficha[pos].numero < soporte.ficha[pos - 1].numero)//Coloca todas las fichas de menor a mayor por número
		{
			elemento = soporte.ficha[pos];//Guarda la ficha en un auxiliar para que no se pierda
			soporte.ficha[pos] = soporte.ficha[pos - 1];//Cambia la ficha de la posición anterior por la guardada en el auxiliar
			soporte.ficha[pos - 1] = elemento;//Cambia las fichas de lugar 
			pos--;
		}
		if (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color && soporte.ficha[pos].numero == soporte.ficha[pos - 1].numero)//Coloca las fichas por colores una vez estan ordenadas de menor a mayor por color
		{
			while (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color && soporte.ficha[pos].numero == soporte.ficha[pos - 1].numero)
			{
				elemento = soporte.ficha[pos];//Guarda la ficha en un auxiliar para que no se pierda
				soporte.ficha[pos] = soporte.ficha[pos - 1];//Cambia la ficha de la posición anterior por la guardada en el auxiliar
				soporte.ficha[pos - 1] = elemento;//Cambia las fichas de lugar 
				pos--;
			}
		}
	}
}
void ordenarPorColor(tSoporte& soporte)//Ordena las fichas por color. Una vez ordenadas, ordena las fichas del mismo color por números
{
	int  pos;
	tFicha elemento;
	for (int i = 1; i < soporte.contador; i++)
	{
		pos = i;
		while (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color)//Coloca todas las fichas de menor a mayor por color
		{
			elemento = soporte.ficha[pos];//Guarda la ficha en un auxiliar para que no se pierda
			soporte.ficha[pos] = soporte.ficha[pos - 1];//Cambia la ficha de la posición anterior por la guardada en el auxiliar
			soporte.ficha[pos - 1] = elemento;//Cambia las fichas de lugar 
			pos--;
		}
		if (pos > 0 && soporte.ficha[pos].numero < soporte.ficha[pos - 1].numero && soporte.ficha[pos].color == soporte.ficha[pos - 1].color)//Coloca las fichas por colores una vez estan ordenadas de menor a mayor por color
		{
			while (pos > 0 && soporte.ficha[pos].numero < soporte.ficha[pos - 1].numero && soporte.ficha[pos].color == soporte.ficha[pos - 1].color)
			{
				elemento = soporte.ficha[pos];//Guarda la ficha en un auxiliar para que no se pierda
				soporte.ficha[pos] = soporte.ficha[pos - 1];//Cambia la ficha de la posición anterior por la guardada en el auxiliar
				soporte.ficha[pos - 1] = elemento;//Cambia las fichas de lugar 
				pos--;
			}
		}
	}
}
void mostrarIndice(int numFichasSoporte)//Muestra el ínidce de las fichas que se pueden jugar del soporte
{
	cout << "       ";
	for (int i = 0; i < numFichasSoporte; i++)//Añade el indice a las fichas del soporte
	{
		cout << setw(3) << i + 1;
	}
	cout << endl;
}
void mostrarSeries(tSoporte& soporte)//Muestra todas las posibles series que se pueden colocar directamentes desde un soporte
{
	tSoporte soporteAux;
	tJugada jugada;
	tFicha elemento;
	bool escalera = true, colorRepetido;
	int fichasJugada = 0, pos;
	soporteAux = soporte;//Guarda el soporte en un auxiliar para que no se vea afectado el orden del soporte

	ordenarPorNum(soporte);//Primero ordena por número

	for (int i = 0; i < soporte.contador - 2; i++)
	{
		int numiguales = 1;
		escalera = true;

		while (escalera)
		{
			if (soporte.ficha[i].numero == soporte.ficha[i + numiguales].numero && soporte.ficha[i].color != soporte.ficha[i + numiguales].color)//Si cumple las condiciones se suma el numero de fichas que las cumplen
			{
				numiguales++;
			}
			else
			{
				if (numiguales >= 3)//Si 3 fichas o más cumplen con las condiciones se pasa a ver si hay algún color repetido entre ellas
				{
					for (int j = i; j < i + numiguales; j++)
					{
						jugada[fichasJugada] = soporte.ficha[j];
						fichasJugada++;
					}
					colorRepetido = coloresRepetidos(jugada);//Comprueba si hay colores repetidos
					if (colorRepetido)//Si los hay elimina una de las fichas con el color repetido
					{
						for (int j = 0; j < fichasJugada - 1; j++)//Selecciona una a una las fichas del array
						{
							for (int k = j + 1; k < fichasJugada; k++)//Compara el color de la ficha seleccionada con todos los de las demás fichas de posiciones superiores
							{
								if (jugada[j].color == jugada[k].color)//Si los colores son iguales elimina la ficha y mueve las fichas que tenía delante una posición a la izquierda
								{
									jugada[k] = jugada[k + 1];
									fichasJugada--;
								}
							}
						}
					}
					if ((fichasJugada >= 3 && colorRepetido) || !colorRepetido)//Si se cumplen las condiciones 
					{
						for (int j = 0; j < fichasJugada; j++)//Muestra la jugada
						{
							mostrarFicha(jugada[j]);
						}
						for (int j = 0; j < fichasJugada; j++)//Vacía las fichas de la jugada
						{
							jugada[j].color = libre;
							jugada[j].numero = -1;
						}
						cout << endl;
					}
					fichasJugada = 0;
					colorRepetido = false;
				}
				escalera = false;
			}
		}
	}
	soporte = soporteAux;//Devuelve el orden inicial al soporte
}
void mostrarEscaleras(tSoporte& soporte)// Muestra todas las posibles escaleras que se pueden colocar directamentes desde un soporte
{
	tSoporte soporteAux;
	bool escalera = true, salto = false;;

	soporteAux = soporte;
	ordenarPorColor(soporte);//Primero ordena por color

	for (int i = 0; i < soporte.contador - 2; i++)
	{
		int numiguales = 1;
		escalera = true;
		salto = false;
		while (escalera)
		{
			if ((soporte.ficha[i].color == soporte.ficha[i + numiguales].color && soporte.ficha[i].numero + numiguales == soporte.ficha[i + numiguales].numero) && (soporte.ficha[i + numiguales].color == soporte.ficha[i + numiguales + 1].color && soporte.ficha[i + numiguales].numero + numiguales == soporte.ficha[i + numiguales].numero))//Compara las fichas una a una hasta que no cumplen las condiciones
			{
				salto = true;
			}
			if (!salto)
			{
				if (soporte.ficha[i].color == soporte.ficha[i + numiguales].color && soporte.ficha[i].numero + numiguales == soporte.ficha[i + numiguales].numero)
				{
					numiguales++;
				}
				else//Cuando no complen la condición de escalera
				{
					if (numiguales >= 3)
					{
						for (int j = i; j < i + numiguales; j++)
						{
							mostrarFicha(soporte.ficha[j]);
						}
						cout << endl;
					}
					escalera = false;
				}
				salto = false;

			}

		}
	}
	soporte = soporteAux;
}
