#include "Jugadas.h"

#include <iostream>
#include <string>

using namespace std;

int buscar(const tJugada& jugada, const tFicha& ficha)//Busca una ficha dentro de una jugada. Si la encuentra, devulve su índice
{
	bool encontrado = false;
	int  i = 0, indice = -1;
	while (!encontrado && i < NumFichas + 1)
	{
		if (jugada[i].color == ficha.color && jugada[i].numero == ficha.numero)
		{
			indice = i;
			encontrado = true;
		}
		else
			i++;
	}
	return indice;
}
void eliminarFichas(tSoporte& soporte, const tJugada& jugada)//Elimina una ficha de un soporte
{
	tJugada jugadaAux;
	int numFichasEliminadas = 0, ind, num;
	bool fichaEliminada;
	for (int i = 0; i < soporte.contador; i++)
	{
		ind = buscar(jugada, soporte.ficha[i]);
		fichaEliminada = false;
		num = 0;

		while (num < numFichasEliminadas && ind != -1)
		{
			if (soporte.ficha[i].numero == jugadaAux[num].numero && soporte.ficha[i].color == jugadaAux[num].color)
				fichaEliminada = true;
			num++;
		}


		if (!fichaEliminada && ind != -1)
		{
			jugadaAux[numFichasEliminadas] = soporte.ficha[i];
			numFichasEliminadas++;
			soporte.ficha[i].numero = -1;
			soporte.ficha[i].color = libre;
		}
	}
	ordenarPorColor(soporte);
	soporte.contador = soporte.contador - numFichasEliminadas;
}
bool coloresRepetidos(tJugada& jugada)//Comprueba si hay por lo menos dos fichas del mismo color en una jugada
{
	int numFichasJugada = 0;
	bool repetidos = false;
	while (jugada[numFichasJugada].numero != -1)//Cuenta el número de fichas de una jugada
	{
		numFichasJugada++;
	}
	for (int i = 0; i < numFichasJugada - 1; i++)//Va comparando de una a una con todas las fichas de puestos posteriores
	{
		for (int j = i + 1; j < numFichasJugada; j++)
		{
			if (jugada[i].color == jugada[j].color)//Si hay al menos dos fichas con el mismo color es que hay repetidos
			{
				repetidos = true;
			}
		}
	}
	return repetidos;
}
int nuevaJugada(tSoporte& soporte, tJugada& jugada)//Permite hacer y comprobar si se puede hacer directamente una jugada desde el soporte
{
	tJugada njugada;
	int num = 1, numFichasJugada = 0, cont = 0, fichasRecorridas = 0;
	bool serie = true, escalera = true, colRepetidos = false, soloUnaFicha = false;
	int es = 0;
	mostrarSoporte(soporte);
	mostrarIndice(soporte.contador);

	cout << endl << "Fichas (0 al final) : ";

	while (num > 0 && num < soporte.contador + 1)// Guarda los valores introducidos en una jugada
	{
		cin >> num;
		if (num != 0)
		{
			njugada[numFichasJugada] = soporte.ficha[num - 1];
			numFichasJugada++;
		}
	}
	if (numFichasJugada == 1)//Si hay solo una ficha guarda una ficha y se salta directamente todo lo demás
	{
		jugada[0] = njugada[0];
		soloUnaFicha = true;
	}
	cout << "Jugada: ";
	mostrarJugada(njugada);
	if (numFichasJugada >= 3 && !soloUnaFicha)//Si cumple las condiciones para que sea una jugada
	{
		colRepetidos = coloresRepetidos(njugada);//Comprueba si hay colores repetidos en la jugada
		if (colRepetidos)//Si los hay no puede haber series
		{
			serie = false;
		}
		else//Si no los hay no puede haber escaleras
		{
			escalera = false;
		}
		if (numFichasJugada < 5) //Comprueba las series
		{
			while (fichasRecorridas < (numFichasJugada - 1) && serie)
			{
				if (njugada[fichasRecorridas].numero != njugada[fichasRecorridas + 1].numero)
				{
					serie = false;
				}
				fichasRecorridas++;
			}
		}
		else
		{
			serie = false;
		}
		fichasRecorridas = 0;
		while (fichasRecorridas < (numFichasJugada - 1) && escalera)//Comprueba las escaleras
		{
			if ((njugada[fichasRecorridas].color != njugada[fichasRecorridas + 1].color) || (njugada[fichasRecorridas].numero + 1 != njugada[fichasRecorridas + 1].numero))//Si son ascendentes
			{
				escalera = false;
			}
			fichasRecorridas++;
		}
		if (!escalera)//Comprueba si las escaleras son descendentes
		{
			while (fichasRecorridas < (numFichasJugada - 1) && escalera)
			{
				if ((njugada[fichasRecorridas].color == njugada[fichasRecorridas + 1].color) && (njugada[fichasRecorridas].numero == njugada[fichasRecorridas + 1].numero + 1))
				{
					escalera = true;
				}
				fichasRecorridas++;
			}
		}


		if (escalera || serie)//Si hay serie o escalera lo muestra
		{

			for (int i = 0; i < numFichasJugada; i++)
			{
				jugada[i] = njugada[i];
			}
			eliminarFichas(soporte, jugada);
			if (serie) {
				cout << " - Serie correcta!!";
			}
			else {
				cout << " - Escalera correcta!!";
			}
			// Si es = 1 es una serie, si es -1 será una escalera, mientras que 0 sera una jugada invalida;
		}
		else//Si no lo hay muestra que no es una jugada correcta
		{
			cout << " - No es una jugada correcta! Prueba de nuevo..." << endl;
			numFichasJugada = 0;
		}
		cout << endl << endl;
		// Falta por eliminar los datos que se introducen a jugada si esta no es correcta.
	}
	return numFichasJugada;
}
void mostrarJugada(const tJugada& jugada)//Muestra las fichas de una jugada
{
	int i = 0;
	while (jugada[i].numero != -1)//Mientras que no llegue al final de la jugada
	{
		mostrarFicha(jugada[i]);//Muestra la ficha recorrida
		i++;//Indice de la ficha a mostrar
	}
}
bool ponerFicha(tJugada& jugada, tFicha& ficha)//Comprueba si es posible poner una ficha en una jugada a elegir del tablero. Si es así la pone.
{

	int numFichas = 0;
	tFicha aux;
	bool paraEscalera = true, paraSerie = true, hayJugada = false, descendente = true, ascendente = true;

	while (jugada[numFichas].numero != -1)//Recorre toda la jugada y cuenta las fichas que tiene ésta
	{
		numFichas++;
	}

	for (int i = 0; i < numFichas; i++)//Recorre toda la jugada
	{
		if (ficha.color == jugada[i].color || ficha.numero != jugada[i].numero)//Si la ficha es del mismo color o no tiene el mismo número no vale para series
		{
			paraSerie = false;
		}
		else//Si la ficha es de diferente color o tiene el mismo número que una de las fichas de la jugada significa que no sirve para escaleras
		{
			paraEscalera = false;
		}
	}
	if (paraSerie)//Si la ficha cumple los requisitos para una serie se pone
	{
		hayJugada = true;
		jugada[numFichas] = ficha;
	}
	if (paraEscalera)//Comprueba si la ficha puede ser puesta en una escalera una vez ha cumplido el primer requisito
	{
		for (int i = 0; i < numFichas - 1; i++)//Comprueba si la escalera de la jugada es ascendente o descendente
		{
			if (jugada[i].numero + 1 != jugada[i + 1].numero)
			{
				ascendente = false;
			}
			if (jugada[i].numero != jugada[i + 1].numero + 1)
			{
				descendente = false;
			}
		}
		if (ascendente)//Si es ascendente
		{
			if ((ficha.numero == jugada[numFichas - 1].numero + 1) && ficha.numero <= NumFichas)//Comprueba el caso 1- jugada: 1 azul 2 azul 3 azul, ficha: 4 azul
			{
				jugada[numFichas] = ficha;//Pone la ficha en última posición
				hayJugada = true;
			}
			else if ((ficha.numero + 1 == jugada[0].numero) && ficha.numero > 0)//Comprueba el caso 2- jugada: 2 azul 3 azul 4 azul, ficha: 1 azul
			{
				for (int i = numFichas; i > 0; i--)//Si lo cumple introduce la ficha moviendo todas un espacio a la derecha y poniendo la ficha en primera posición
				{
					jugada[i] = jugada[i - 1];
				}
				jugada[0] = ficha;
				hayJugada = true;
			}
		}
		else if (descendente)//Si es descendente
		{
			if ((ficha.numero == jugada[0].numero + 1) && ficha.numero <= NumFichas)//Comprueba el caso 3- jugada: 5 azul 4 azul 3 azul, ficha: 6 azul
			{
				for (int i = numFichas; i > 0; i--)//Si lo cumple introduce la ficha moviendo todas un espacio a la derecha y poniendo la ficha en primera posición
				{
					jugada[i] = jugada[i - 1];
				}
				jugada[0] = ficha;
				hayJugada = true;
			}
			else if ((ficha.numero + 1 == jugada[numFichas - 1].numero) && ficha.numero > 0)//Comprueba el caso 4- jugada: 5 azul 4 azul 3 azul, ficha: 2 azul
			{
				jugada[numFichas] = ficha;//Pone la ficha en última posición
				hayJugada = true;
			}
		}
	}
	if (numFichas == 0)//Si el número de fichas es 0 no hay jugada
	{
		hayJugada = false;
	}
	return hayJugada;
}
