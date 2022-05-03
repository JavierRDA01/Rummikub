#include "Fichas.h"

#include <iostream>
#include <string>
using namespace std;

void mostrarFicha(const tFicha& ficha)// Muestra el color y el número de una ficha
{
	colorTexto(ficha.color);
	cout << ficha.numero << "  ";//Muestra el color y el número de la ficha
	colorTexto(blanco);
}
