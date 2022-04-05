// Autor/a: 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>

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

int menu();//Muestra el menu
void inicializarBolsa(tBolsa& bolsa);//Inicializa la bolsa poniendo todas las fichas posibles segun el parámetro numFichas
void repartir(tBolsa& bolsa, tSoportes& soportes);//Reparte las fichas iniciales a todos los jugadores
tFicha robar(tBolsa& bolsa);//Roba si se puede, una ficha de la bolsa y la añade al soporte. Elimina la ficha de la bolsa
void mostrarBolsa(const tBolsa& bolsa);//Muestra la bolsa, enseñando las fichas que quedan y las que faltan
void mostrarSoporte(const tSoporte& soporte);//Muestra el soporte de un jugador
bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna);//Es llamada por la función robar(). Recorre la bolsa en busca de una ficha
string toString(tColor color);
void resuelveCaso();
void ordenarPorColor(tSoporte& soporte);//Ordena las fichas por color. Una vez ordenadas, ordena las fichas del mismo color por números
void ordenarPorNum(tSoporte& soporte);//Ordena las fichas por números. Una vez ordenadas, ordena las fichas del mismo número por color.
void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int turno);//Roba una ficha de la bolsa y la coloca en el soporte
void mostrarSeries(tSoporte& soporte);//Muestra todas las posibles series que se pueden colocar directamentes desde un soporte
void mostrarEscaleras(tSoporte& soporte); // Muestra todas las posibles escaleras que se pueden colocar directamentes desde un soporte
void eliminarFichas(tSoporte& soporte, const tJugada& jugada);//Elimina una ficha de un soporte
int buscar(const tJugada& jugada, const tFicha& ficha);//Busca una ficha dentro de una jugada. Si la encuentra, devulve su índice
int nuevaJugada(tSoporte& soporte, tJugada& jugada);//Permite hacer y comprobar si se puede hacer directamente una jugada desde el soporte
bool coloresRepetidos(tJugada& jugada);//Comprueba si hay por lo menos dos fichas del mismo color en una jugada
bool jugar(tTablero& tablero, tSoporte& soporte);//Llama a ponerFicha() o a nuevaJugada() dependiendo del número de fichas que queramos jugar
void mostrarFicha(const tFicha& ficha);//Muestra el color y el número de una ficha
void mostrarJugada(const tJugada& jugada);//Muestra las fichas de una jugada
void mostrarTablero(const tTablero& tablero);//Muestra el tablero donde se juega
void mostrarIndice(int numFichasSoporte);//Muestra el ínidce de las fichas que se pueden jugar del soporte
int avanzarTurno(int turno);//Una vez termina la jugada, se pasa turno al siguiente jugador
bool ponerFicha(tJugada& jugada, tFicha& ficha);//Comprueba si es posible poner una ficha en una jugada a elegir del tablero. Si es así la pone.
void colorTexto(tColor color);


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
	int fila, columna;
	tFicha ficha;
	ficha.color = libre;//Inicializamos la ficha
	ficha.numero = -1;//Inicializamos la ficha
	fila = rand() % 8;
	columna = rand() % NumFichas;
	if (bolsa.bolsaFicha[fila][columna].numero == -1) //Si la ficha de la posición introducida está libre, entonces busca la siguiente icha a partir de esa posición
	{
		encontrado = recorrerBolsa(bolsa, fila, columna);//Busca la ficha

	}
	else
	{
		encontrado = true;//Si encuentra la ficha
	}
	if (!encontrado)//Si no encuentra la ficha comienza a buscar desde el principio
	{
		fila = 0;
		columna = 0;
		encontrado = recorrerBolsa(bolsa, fila, columna);//Busca la ficha
	}
	if (encontrado)
	{
		ficha = bolsa.bolsaFicha[fila][columna];//Si finalmente encuentra la ficha, coge la ficha a partir de la posición encontrada
		bolsa.bolsaFicha[fila][columna].color = libre;//Libera la posición donde esta guardada la ficha cogida
		bolsa.bolsaFicha[fila][columna].numero = -1;
	}
	return ficha;
}


bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna)//Done Busca la posición donde haya una ficha en la bolsa
{
	bool encontrado = false;
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
	return encontrado;
}

void repartir(tBolsa& bolsa, tSoportes& soportes)//Done
{
	for (int i = 0; i < NumJugadores; i++)//Una vuelta por cada jugador
	{
		for (int j = 0; j < IniFichas; j++)//Vuelta por cada ficha del soporte
		{
			obtenerFicha(bolsa, soportes, i);//Roba la ficha y la pone en el soporte correspondiente
		}
	}
}

void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int turno)//Done
{
	if (soportes[turno].contador < MaxFichas)//Si el soporte no llega a su máxima capacidad
	{
		soportes[turno].ficha[soportes[turno].contador] = robar(bolsa);//Roba la ficha y la añade a su soporte
		soportes[turno].contador++;//Suma el contador en 1
	}
}
void mostrarFicha(const tFicha& ficha)
{
	colorTexto(ficha.color);
	cout << ficha.numero << "  ";//Muestra el color y el número de la ficha
	colorTexto(blanco);
}
void mostrarBolsa(const tBolsa& bolsa)
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

void mostrarSoporte(const tSoporte& soporte)
{
	cout << "Soporte: ";
	for (int i = 0; i < soporte.contador; i++)//Recorre el soporte
	{
		mostrarFicha(soporte.ficha[i]);//Muestra la ficha recorrida
	}
	cout << endl;
}
void mostrarJugada(const tJugada& jugada)
{
	int i = 0;
	while (jugada[i].numero != -1)//Mientras que no llegue al final de la jugada
	{
		mostrarFicha(jugada[i]);//Muestra la ficha recorrida
		i++;//Indice de la ficha a mostrar
	}
}
void mostrarTablero(const tTablero& tablero)
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
void mostrarIndice(int numFichasSoporte)
{
	cout << "       ";
	for (int i = 0; i < numFichasSoporte; i++)//Añade el indice a las fichas del soporte
	{
		cout << setw(3) << i + 1;
	}
	cout << endl;
}
string toString(tColor color)
{
	string nombre;
	if (color == rojo)
	{
		nombre = "rojo";
	}
	else if (color == amarillo)
	{
		nombre = "amar";
	}
	else if (color == azul)
	{
		nombre = "azul";
	}
	else if (color == verde)
	{
		nombre = "verd";
	}
	return nombre;
}
void ordenarPorNum(tSoporte& soporte)//Done
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
		if (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color && soporte.ficha[pos].numero == soporte.ficha[pos - 1].numero)//Coloca las fichas por colores una vez estan ordenadas de menor a mayor por número
		{
			while (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color && soporte.ficha[pos].numero == soporte.ficha[pos - 1].numero)
			{
				elemento = soporte.ficha[pos];
				soporte.ficha[pos] = soporte.ficha[pos - 1];
				soporte.ficha[pos - 1] = elemento;
				pos--;
			}
		}
	}
}
void ordenarPorColor(tSoporte& soporte)//Done
{
	int  pos;
	tFicha elemento;
	for (int i = 1; i < soporte.contador; i++)
	{
		pos = i;
		while (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color)
		{
			elemento = soporte.ficha[pos];
			soporte.ficha[pos] = soporte.ficha[pos - 1];
			soporte.ficha[pos - 1] = elemento;
			pos--;
		}
		if (pos > 0 && soporte.ficha[pos].numero < soporte.ficha[pos - 1].numero && soporte.ficha[pos].color == soporte.ficha[pos - 1].color)
		{
			while (pos > 0 && soporte.ficha[pos].numero < soporte.ficha[pos - 1].numero && soporte.ficha[pos].color == soporte.ficha[pos - 1].color)
			{
				elemento = soporte.ficha[pos];
				soporte.ficha[pos] = soporte.ficha[pos - 1];
				soporte.ficha[pos - 1] = elemento;
				pos--;
			}
		}
	}
}
int avanzarTurno(int turno)
{
	if (turno == NumJugadores - 1)
	{
		turno = 0;
	}
	else
	{
		turno++;
	}
	return turno;
}
void mostrarSeries(tSoporte& soporte)//Done
{
	tSoporte soporteAux;
	tJugada jugada;
	tFicha elemento;
	bool escalera = true, colorRepetido;
	int fichasJugada = 0, pos;
	soporteAux = soporte;

	ordenarPorNum(soporte);

	for (int i = 0; i < soporte.contador - 2; i++)
	{
		int numiguales = 1;
		escalera = true;

		while (escalera)
		{
			if (soporte.ficha[i].numero == soporte.ficha[i + numiguales].numero && soporte.ficha[i].color != soporte.ficha[i + numiguales].color)
			{
				numiguales++;
			}
			else
			{
				if (numiguales >= 3)
				{
					for (int j = i; j < i + numiguales; j++)
					{
						jugada[fichasJugada] = soporte.ficha[j];
						fichasJugada++;
					}
					colorRepetido = coloresRepetidos(jugada);
					if (colorRepetido)
					{
						for (int j = 0; j < fichasJugada - 1; j++)//Selecciona una a una las fichas del array
						{
							for (int k = j + 1; k < fichasJugada; k++)//Compara el color de la ficha seleccionada con todos los de las demás fichas de posiciones superiores
							{
								if (jugada[j].color == jugada[k].color)//Si los colores son iguales
								{
									jugada[k].color = libre;
									jugada[k].numero = -1;
								}
							}
						}
						for (int j = 0; j < fichasJugada; j++)
						{
							pos = j;
							while (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color)
							{
								elemento = soporte.ficha[pos];
								soporte.ficha[pos] = soporte.ficha[pos - 1];
								soporte.ficha[pos - 1] = elemento;
								pos--;
							}
						}
						fichasJugada = 0;
						while (jugada[fichasJugada].numero != -1)
						{
							if(jugada[fichasJugada].numero != -1)
							{
								fichasJugada++;
							}
						}
					}
					if ((fichasJugada >= 3 && colorRepetido) || !colorRepetido)
					{
						for (int j = 0; j < fichasJugada; j++)
						{
							mostrarFicha(jugada[j]);
						}
						for(int j = 0; j < fichasJugada; j++)
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
	soporte = soporteAux;
}
void mostrarEscaleras(tSoporte& soporte)//Done
{
	tSoporte soporteAux;
	bool escalera = true;

	soporteAux = soporte;
	ordenarPorColor(soporte);

	for (int i = 0; i < soporte.contador - 2; i++)
	{
		int numiguales = 1;
		escalera = true;
		while (escalera)
		{
			if (soporte.ficha[i].color == soporte.ficha[i + numiguales].color && soporte.ficha[i].numero + numiguales == soporte.ficha[i + numiguales].numero)
			{
				numiguales++;
			}
			else
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
		}
	}
	soporte = soporteAux;
}
bool coloresRepetidos(tJugada& jugada)
{
	int i = 0;
	bool repetidos = false;
	while (jugada[i].numero != -1)
	{
		i++;
	}
	for (int j = 0; j < i - 1; j++)
	{
		for (int k = j; k < i - 1; k++)
		{
			if (jugada[j].color == jugada[k + 1].color)
			{
				repetidos = true;
			}
		}
	}
	return repetidos;
}
int nuevaJugada(tSoporte& soporte, tJugada& jugada)
{
	tJugada njugada;
	int num = 1, numFichasJugada = 0, cont = 0, fichasRecorridas = 0;
	bool serie = true, escalera = true, colRepetidos = false, soloUnaFicha = false;
	int es = 0;
	mostrarSoporte(soporte);
	mostrarIndice(soporte.contador);

	cout << endl << "Fichas (0 al final) : ";

	while (num > 0 && num < soporte.contador + 1)
	{
		cin >> num;
		if (num != 0)
		{
			njugada[numFichasJugada] = soporte.ficha[num - 1];
			numFichasJugada++;
		}
	}
	if (numFichasJugada == 1)
	{
		jugada[0] = njugada[0];
		soloUnaFicha = true;
	}
	cout << "Jugada: ";
	mostrarJugada(njugada);
	colRepetidos = coloresRepetidos(njugada);
	if (colRepetidos)
	{
		serie = false;
	}
	else
	{
		escalera = false;
	}
	if (numFichasJugada >= 3 && !soloUnaFicha)
	{
		if (numFichasJugada < 5) {
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
		while (fichasRecorridas < (numFichasJugada - 1) && escalera)
		{
			if ((njugada[fichasRecorridas].color != njugada[fichasRecorridas + 1].color) || (njugada[fichasRecorridas].numero + 1 != njugada[fichasRecorridas + 1].numero))
			{
				escalera = false;
			}
			fichasRecorridas++;
		}
		if(!escalera)
		{
			escalera = true;
			while (fichasRecorridas < (numFichasJugada - 1) && escalera)
			{
				if ((njugada[fichasRecorridas].color != njugada[fichasRecorridas + 1].color) || (njugada[fichasRecorridas].numero != njugada[fichasRecorridas + 1].numero + 1))
				{
					escalera = false;
				}
				fichasRecorridas++;
			}
		}


		if (escalera || serie)
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
		else
		{
			cout << " - No es una jugada correcta! Prueba de nuevo..." << endl;
			numFichasJugada = 0;
		}
		cout << endl << endl;
		// Falta por eliminar los datos que se introducen a jugada si esta no es correcta.
	}
	return numFichasJugada;
}

int buscar(const tJugada& jugada, const tFicha& ficha)//Done
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

void eliminarFichas(tSoporte& soporte, const tJugada& jugada)//Done
{
	tJugada jugadaAux;
	int numFichasEliminadas = 0, ind, num;
	bool fichaEliminada;
	for (int i = 0; i < soporte.contador; i++)
	{
		ind = buscar(jugada, soporte.ficha[i]);
		fichaEliminada = false;
		num = 0;

		while (fichaEliminada && num < numFichasEliminadas && ind != -1) {
			if (soporte.ficha[i].numero == jugadaAux[num].numero && soporte.ficha[i].color == jugadaAux[num].color)
				fichaEliminada = true;
			num++;
		}


		if (!fichaEliminada && ind != -1)
		{
			jugadaAux[numFichasEliminadas] = soporte.ficha[i];
			numFichasEliminadas++;
			for (int j = i; j < soporte.contador - 1; j++)
			{
				soporte.ficha[j] = soporte.ficha[j + 1];
			}
			soporte.contador--;
		}


	}
}
bool ponerFicha(tJugada& jugada, tFicha& ficha)
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
	if (paraSerie)
	{
		hayJugada = true;
		jugada[numFichas] = ficha;
	}
	if (paraEscalera)
	{
		for (int i = 0; i < numFichas - 1; i++)
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
		if (ascendente)
		{
			if ((ficha.numero == jugada[numFichas - 1].numero + 1) && ficha.numero < NumFichas)
			{
				jugada[numFichas] = ficha;
				hayJugada = true;
			}
			else if ((ficha.numero == jugada[0].numero - 1) && ficha.numero > 0)
			{
				for (int i = numFichas; i > 0; i--)
				{
					jugada[i] = jugada[i - 1];
				}
				jugada[0] = ficha;
				hayJugada = true;
			}
		}
		else if (descendente)
		{
			if ((ficha.numero == jugada[0].numero + 1) && ficha.numero < NumFichas)
			{
				for (int i = numFichas; i > 0; i--)
				{
					jugada[i] = jugada[i - 1];
				}
				jugada[0] = ficha;
				hayJugada = true;
			}
			else if ((ficha.numero - 1 == jugada[numFichas - 1].numero) && ficha.numero > 0)
			{
				jugada[numFichas] = ficha;
				hayJugada = true;
			}
		}
	}
	if(numFichas == 0)
	{
		hayJugada = false;
	}
	return hayJugada;
}
bool jugar(tTablero& tablero, tSoporte& soporte)
{
	tFicha ficha;
	tJugada jugada;
	int numFichasJugada, numJugada = 0, posicionFichaJugada = 0, numFichaDeLaJugada = 0, i = 0;
	bool hayJugada = false;
	while(jugada[i].numero != -1)
	{
		jugada[i].numero = -1;
		jugada[i].color = libre;
		i++;
	}
	i = 0;
	numFichasJugada = nuevaJugada(soporte, jugada);
	if (numFichasJugada > 1 && tablero.contador < MaxJugadas)
	{
		while (jugada[posicionFichaJugada].numero != 0)
		{
			tablero.jugada[tablero.contador][posicionFichaJugada] = jugada[posicionFichaJugada];
			posicionFichaJugada++;
		}

		tablero.contador++;
		hayJugada = true;
	}
	else if (numFichasJugada == 1)
	{
		ficha = jugada[0];
		cout << endl << "Jugadas del tablero donde poner la ficha: ";
		cin >> numJugada;
		numJugada = numJugada - 1;
		//cout << numJugada;
		hayJugada = ponerFicha(tablero.jugada[numJugada], ficha);
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
	mostrarTablero(tablero);
	return hayJugada;
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
