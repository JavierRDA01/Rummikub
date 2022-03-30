// Autor/a: Nombre y apellidos
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

const int NumJugadores = 3;
const int NumFichas = 10;
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

int menu();
void inicializarBolsa(tBolsa& bolsa, int numFichas);
void repartir(tBolsa& bolsa, tSoportes& soportes, int numFichas, int numJugadores, int iniFichas);
tFicha robar(tBolsa& bolsa, int fila, int columna, int numFichas);
void mostrarBolsa(const tBolsa& bolsa, int numFichas);
void mostrarSoporte(const tSoporte& soporte);
bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna, int numFichas);
string toString(tColor color);
void resuelveCaso();
void ordenarPorColor(tSoporte& soporte, int numFichas);
void ordenarPorNum(tSoporte& soporte, int numFichas);
void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int fila, int columna, int turno, int numFichas);
void mostrarSeries(const tSoporte& soporte);
void mostrarEscaleras(const tSoporte& soporte);
void eliminarFichas(tSoporte& soporte, const tJugada jugada);
int buscar(const tJugada& jugada, const tFicha& ficha);
int nuevaJugada(tSoporte& soporte, tJugada& jugada);


int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

int menu()
{
	int opcion;
	cin >> opcion;
	if (opcion != -1)
	{
		cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
		cout << opcion << endl;
	}
	return opcion;
}

void inicializarBolsa(tBolsa& bolsa, int numFichas)
{
	for (int i = 0; i < 8; i++)//Por cada fila
	{
		for (int j = 0; j < numFichas; j++)//Por cada columna
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
tFicha robar(tBolsa& bolsa, int fila, int columna, int numFichas)
{
	bool encontrado = false;
	tFicha ficha;
	ficha.color = libre;//Inicializamos la ficha
	ficha.numero = -1;//Inicializamos la ficha
	if (bolsa.bolsaFicha[fila][columna].numero == -1) //Si la ficha de la posición introducida está libre, entonces busca la siguiente icha a partir de esa posición
	{
		encontrado = recorrerBolsa(bolsa, fila, columna, numFichas);//Busca la ficha

	}
	else
	{
		encontrado = true;//Si encuentra la ficha
	}
	if (!encontrado)//Si no encuentra la ficha comienza a buscar desde el principio
	{
		fila = 0;
		columna = 0;
		encontrado = recorrerBolsa(bolsa, fila, columna, numFichas);//Busca la ficha
	}
	if (encontrado)
	{
		ficha = bolsa.bolsaFicha[fila][columna];//Si finalmente encuentra la ficha, coge la ficha a partir de la posición encontrada
		bolsa.bolsaFicha[fila][columna].color = libre;//Libera la posición donde esta guardada la ficha cogida
		bolsa.bolsaFicha[fila][columna].numero = -1;
	}
	return ficha;
}


bool recorrerBolsa(tBolsa& bolsa, int& fila, int& columna, int numFichas)//Busca la posición donde haya una ficha en la bolsa
{
	bool encontrado = false;
	while (!encontrado && fila < 8)//Se repite mientras que no haya encontrado la ficha y mientras que no haya llegado al final del array
	{
		while (!encontrado && columna < numFichas)//Mientras que no haya llegado al final de la columna y no se haya encontrado la ficha
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
		if (!encontrado)
		{
			columna = 0;
			fila++;
		}
	}
	return encontrado;
}

void repartir(tBolsa& bolsa, tSoportes& soportes, int numFichas, int numJugadores, int iniFichas)
{
	int fila, columna;
	for (int i = 0; i < numJugadores; i++)//Una vuelta por cada jugador
	{
		for (int j = 0; j < iniFichas; j++)//Vuelta por cada ficha del soporte
		{
			cin >> fila;//fila
			cin >> columna;//columna
			obtenerFicha(bolsa, soportes, fila, columna, i, numFichas);//Roba la ficha y la pone en el soporte correspondiente
		}
	}
}

void obtenerFicha(tBolsa& bolsa, tSoportes& soportes, int fila, int columna, int turno, int numFichas)
{
	if (soportes[turno].contador < MaxFichas)
	{
		soportes[turno].ficha[soportes[turno].contador] = robar(bolsa, fila, columna, numFichas);
		soportes[turno].contador++;
	}
}
void mostrarFicha(const tFicha& ficha)
{
	cout << toString(ficha.color) << " " << ficha.numero << "  ";
}
void mostrarBolsa(const tBolsa& bolsa, int numFichas)
{
	cout << endl << "Bolsa..." << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < numFichas; j++)
		{
			if (bolsa.bolsaFicha[i][j].color == libre || bolsa.bolsaFicha[i][j].numero == -1)
			{
				cout << "    " << "-1" << "  ";
			}
			else
			{
				mostrarFicha(bolsa.bolsaFicha[i][j]);
			}
		}
		cout << endl;
	}
}

void mostrarSoporte(const tSoporte& soporte)
{
	cout << "Soporte:";
	for (int i = 0; i < soporte.contador; i++)
	{
		mostrarFicha(soporte.ficha[i]);
	}
	cout << endl << endl;
}
void mostrarJugada(const tJugada& jugada, int numFichas)
{
	int i = 0;
	cout << "Jugada: ";
	while(jugada[i].numero < numFichas && jugada[i].numero > 0)
	{
		mostrarFicha(jugada[i]);
		i++;
	}
}
void mostrarTablero(const tTablero& tablero, int numFichas)
{
	cout << "Tablero:" << endl;
	for (int i = 0; i < tablero.contador; i++)
	{
		cout << i + 1 << ": ";
		mostrarJugada(tablero.jugada[i], numFichas);
		cout << endl;
	}
}
void comprobarSeries()
{

}
void comprobarEscaleras()
{

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
void ordenarPorNum(tSoporte& soporte, int numFichas)
{
	int  pos;
	tFicha elemento;
	for (int i = 1; i < soporte.contador; i++)
	{
		pos = i;
		while (pos > 0 && soporte.ficha[pos].numero < soporte.ficha[pos - 1].numero)
		{
			elemento = soporte.ficha[pos];
			soporte.ficha[pos] = soporte.ficha[pos - 1];
			soporte.ficha[pos - 1] = elemento;
			pos--;
		}
		if (pos > 0 && soporte.ficha[pos].color < soporte.ficha[pos - 1].color && soporte.ficha[pos].numero == soporte.ficha[pos - 1].numero)
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
void ordenarPorColor(tSoporte& soporte, int numFichas)
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
int avanzarTurno(int numJugadores, int turno)
{
	if (turno == numJugadores - 1)
	{
		turno = 0;
	}
	else
	{
		turno++;
	}
	return turno;
}
void mostrarSeries(tSoporte& soporte, int numFichas)
{
	int jugada = 0;
	tSoporte soporteAux;
	bool escalera = true;
	soporteAux = soporte;

	ordenarPorNum(soporte, numFichas);

	for (int t = 0; t < soporte.contador - 2; t++)
	{
		int numiguales = 1;
		escalera = true;

		while (escalera) 
		{
			if (soporte.ficha[t].numero == soporte.ficha[t + numiguales].numero && soporte.ficha[t].color != soporte.ficha[t + numiguales].color)
			{
				numiguales++;
			}
			else
			{
				if (numiguales >= 3)
				{
					for (int j = t; j < t + numiguales; j++)
					{
						cout << toString(soporte.ficha[j].color) << " " << soporte.ficha[j].numero << "  ";
					}
					cout << endl;
				}
				escalera = false;
			}
		}
	}
	soporte = soporteAux;
}
void mostrarEscaleras(tSoporte& soporte, int numFichas)
{
	tSoporte aux;
	bool escalera = true;
	ordenarPorColor(soporte, numFichas);

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
				{
					if (numiguales >= 3)
					{
						for (int j = i; j < i + numiguales; j++)
						{
							cout << toString(soporte.ficha[j].color) << " " << soporte.ficha[j].numero << "  ";
						}
						cout << endl;
					}
					escalera = false;
				}
			}
		}
	}
}
int nuevaJugada(tSoporte& soporte, tJugada& jugada, int numFichas)
{
	int indFicha, cont = 0;
	cout << "   Fichas (0 al final): ";
	do
	{
		cin >> indFicha;
		cout << indFicha << " ";
		if (indFicha != 0)
		{
			jugada[cont] = soporte.ficha[indFicha];
			cont++;
		}
	} while (indFicha == 0);
	mostrarJugada(jugada, numFichas);
	cout << endl;
}
int buscar(const tJugada& jugada, const tFicha& ficha)
{
	bool encontrado = false;
	int vueltas = 0, indice = -1;
	while (!encontrado && vueltas < NumFichas + 1)
	{
		if (jugada[vueltas].color == ficha.color && jugada[vueltas].numero == ficha.numero)
		{
			indice = vueltas;
			encontrado = true;
		}
		vueltas++;
	}
	return indice;
}
void eliminarFichas(tSoporte& soporte, const tJugada& jugada)
{
	for (int i = 0; i < soporte.contador; i++) {

		if (buscar(jugada, soporte.ficha[i]) != -1) 
		{
			soporte.ficha[i].color = libre;
			soporte.ficha[i].numero = -1;
		}
	}
}
void resuelveCaso()
{
	tBolsa bolsa;
	tSoportes soportes;
	int numFichas, iniFichas, numJugadores, fila, columna, turno, opcion,numFicha;
	cin >> numFichas;
	cin >> iniFichas;
	cin >> numJugadores;

	inicializarBolsa(bolsa, numFichas);//Rellena la bolsa con las fichas iniciales
	mostrarBolsa(bolsa, numFichas);//Muestra la bolsa para comprobar que se ha rellenado efectivamente
	//Inicializa la bolsa

	repartir(bolsa, soportes, numFichas, numJugadores, iniFichas);
	//Reparte las fichas

	cout << endl << "Fichas de la bolsa con todas las fichas repartidas" << endl;
	mostrarBolsa(bolsa, numFichas);//Muestra la bolsa
	//Muestra la bolsa después de repartir las fichas

	cin >> turno;//Recoge el turno del jugador al que le toca jugar
	cout << endl << "Turno para el jugador " << turno << " ..." << endl;
	turno = turno - 1;
	mostrarSoporte(soportes[turno]);//Bucle de jugadas
	cin >> opcion;
	do//Mientras que el turno no sea -1 el bucle reproduce todas las jugadas
	{
		opcion = menu();
		if (opcion == 0)
		{
			cin >> fila;
			cin >> columna;
			obtenerFicha(bolsa, soportes, fila, columna, turno, numFichas);
			mostrarSoporte(soportes[turno]);
			turno = avanzarTurno(numJugadores, turno);
			cout << "Turno para el jugador " << turno + 1 << " ..." << endl;
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 1)
		{
			ordenarPorNum(soportes[turno], numFichas);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 2)
		{
			ordenarPorColor(soportes[turno], numFichas);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 3)
		{
			mostrarEscaleras(soportes[turno], numFichas);
			mostrarSeries(soportes[turno], numFichas);
			mostrarSoporte(soportes[turno]);
		}
		else if (opcion == 4)
		{
			
		}
	} while (opcion != -1);

}
