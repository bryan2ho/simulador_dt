#ifndef MISC_H
#define MISC_H
#include "estructuras.h"

void borrar_lineas(int n);
int agregar_jugador(Club *club, const char *nombre, const char *posicion, int media, int valor);
int eliminar_jugador(Club *club, int indice);


#endif