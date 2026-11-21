#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sistema_mercado.h"

int cargar_jugadores(Jugador jugador[]){
    FILE *archivo_jugadores = fopen("jugadores.txt", "r");

    if(archivo_jugadores == NULL){
        printf("Error: el archivo no se pudo abrir\n");
        return 0;
    }
    int total_jugadores = 0;
    printf("Archivo abierto correctamente.\n");
    char linea[80];
    
    while (fgets(linea, sizeof(linea), archivo_jugadores) != NULL){
        char *nombre = strtok(linea, ",");
        char *posicion = strtok(NULL, ",");
        char *media = strtok(NULL, ",");
        char *valor = strtok(NULL, ",");

        strcpy(jugador[total_jugadores].nombre, nombre);
        strcpy(jugador[total_jugadores].posicion, posicion);
        jugador[total_jugadores].media = atoi(media);
        jugador[total_jugadores].valor = atoi(valor);

        total_jugadores++; 
    }
    fclose(archivo_jugadores);
    printf("Se cargaron %d jugadores.\n", total_jugadores);
    return total_jugadores;
}

void variar_precios(Jugador jugador[], int total_jugadores){
    for(int i=0; i < total_jugadores; i++){
        int cambio = rand() % 2;
        int variacion=0;
        if (cambio == 1){
                variacion = (rand() % 21) -10; //El porcentaje de variacion de valor circula en un rango de -10 a 10
                jugador[i].valor += (jugador[i].valor * variacion) / 100; //actualiza el valor del jugador segun el porcentaje a aumentar/descontar
        } 
    }
}

void seleccionar_jugadores(Jugador jugador[], int total_jugadores, Jugador tienda[]){
    int cont_por=0;
    int cont_def=0;
    int cont_med=0;
    int cont_del=0;
    int seleccionados[50] = {0};
    int indice; //indice dentro de seleccionados, indicará si un jugador fue seleccionado (1), o si aun no se selecciona (0) 
    
    while(cont_por < 5 || cont_del < 5 || cont_med < 5 || cont_def < 5){
        indice = rand() % total_jugadores;
        if (seleccionados[indice] == 0){
            if(strcmp(jugador[indice].posicion, "POR") == 0){ //compara si el jugador obtenido por rand coindice con la posicion
                if(cont_por < 5){ //evalua si aun faltan por seleccionar de esa posicion
                    seleccionados[indice] = 1;
                    tienda[cont_por] = jugador[indice]; //agrega a la tienda al jugador seleccionado de acuerdo al contador de porteros
                    cont_por++;
                }
            }else if(strcmp(jugador[indice].posicion, "DEF") == 0){ 
                if(cont_def < 5){
                    seleccionados[indice] = 1;
                    tienda[5 + cont_def] = jugador[indice]; //5 + cont_def comienza a agregar a las defensas despues de los porteros sin sobreescribirlos
                    cont_def++;
                }
            }else if(strcmp(jugador[indice].posicion, "MED") == 0){ 
                if(cont_med < 5){
                    seleccionados[indice] = 1;
                    tienda[10 + cont_med] = jugador[indice]; //agrega a los medios sin sobreescribir a los dos anteriores
                    cont_med++;
                }            
            }else if(strcmp(jugador[indice].posicion, "DEL") == 0){ 
                if(cont_del < 5){
                    seleccionados[indice] = 1;
                    tienda[15 + cont_del] = jugador[indice];
                    cont_del++;
                }
            }
        }
    }    
}

