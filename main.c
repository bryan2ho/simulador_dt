#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "sistema_guardado.h"

/*
Recuerden incluir la cabecera estructuras.h en las cabeceras que creen y llamar su cabecera .h correspondiente para cada modulo .c que hagan;
al final todas deben estar incluidas aqui, pueden ver los archivos de sistema_guardado como ejemplola c
*/

//ejecuten el archivo escribiendo gcc main.c sistema_guardado.c -o test_guardado.exe (pero incluyan todos los .c que hayan hasta el momento, o los que ocupen probar)

int main(){

    //LO QUE HAY EN MAIN AHORA ES UNA PRUEBA PARA VER QuE FUNCIONE EL MODULO DE SISTEMA DE GUARDADO, BORRENLO CUANDO QUIERAN O DEJENLO SI OCUPAN PARA VERIFICAR ALGO UDS
    //o guardenlo en un txt por algun lado idk

    Club mi_club;

    strcpy(mi_club.nombre_equipo, "Tigres UANL");
    mi_club.presupuesto = 5000000;
    mi_club.dia_actual = 3;
    mi_club.total_jugadores = 2;

    mi_club.plantilla = (Jugador *) malloc(mi_club.total_jugadores * sizeof(Jugador));

    strcpy(mi_club.plantilla[0].nombre, "Andre-Pierre Gignac");
    strcpy(mi_club.plantilla[0].posicion, "DEL");
    mi_club.plantilla[0].media = 94;
    mi_club.plantilla[0].valor = 100000;

    strcpy(mi_club.plantilla[1].nombre, "Nahuel Guzman");
    strcpy(mi_club.plantilla[1].posicion, "POR");
    mi_club.plantilla[0].media = 89;
    mi_club.plantilla[0].valor = 200000;

    printf("///ANTES DE GUARDAR///\n");
    printf("Equipo: %s | Presupuesto: %d | Dia: %d | Jugadores: %d\n", mi_club.nombre_equipo, mi_club.presupuesto, mi_club.dia_actual, mi_club.total_jugadores);
    printf("Jugador 1: %s | Media: %d\n", mi_club.plantilla[0].nombre, mi_club.plantilla[0].media);
    printf("Jugador 2: %s | Media: %d\n\n", mi_club.plantilla[1].nombre, mi_club.plantilla[1].media);

    guardar_partida(&mi_club);

    strcpy(mi_club.nombre_equipo, "Basura");
    mi_club.presupuesto = 0;
    mi_club.dia_actual = 99;
    mi_club.total_jugadores = 0;

    printf("///DESPUES DE MODIFICAR (antes de cargar)///\n");
    printf("Equipo: %s | Presupuesto: %d | Dia: %d | Jugadores: %d\n\n", 
    mi_club.nombre_equipo, mi_club.presupuesto, mi_club.dia_actual, mi_club.total_jugadores);

    cargar_partida(&mi_club);


    printf("///DESPUES DE CARGAR///\n");
    printf("Equipo: %s | Presupuesto: %d | Dia: %d | Jugadores: %d\n", mi_club.nombre_equipo, mi_club.presupuesto, mi_club.dia_actual, mi_club.total_jugadores);
    printf("Jugador 1: %s | Media: %d\n", mi_club.plantilla[0].nombre, mi_club.plantilla[0].media);
    printf("Jugador 2: %s | Media: %d\n\n", mi_club.plantilla[1].nombre, mi_club.plantilla[1].media);

    return 0;
}