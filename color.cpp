#include "Colores.h"
#include <iostream>
#include <string>
using namespace std;

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
