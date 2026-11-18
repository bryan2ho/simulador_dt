#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h> // TODO: PROBAR SI FUNCIONA EN WINDOWS
    #define ssleep(ms) Sleep(ms)
#elif __linux__
    #include <unistd.h> 
    #define ssleep(ms) usleep((ms) * 1000)
#endif
#include "sistema_eventos.h"
#include "estructuras.h"
#include "misc.h"

typedef struct {
    TipoEvento id;
    const char* desc;
    int peso;
    bool disponible;
} Evento;

static Evento eventos[TOTAL_EVENTOS] = {
    {EVENTO_NADA, "Nada interesante ocurrió.\n", 30, true},
    {EVENTO_PATROCINADOR, "Tienes un nuevo patrocinador.\n", 10, true},
    {EVENTO_LESION, "Un jugador se lesionó, su media bajó.\n", 15, true},
    {EVENTO_LESION, "A un jugador le dio un infarto durante el entrenamiento. Murió.\n", false}
    // AGREGAR EVENTOS

};

static TipoEvento eventos_seleccionar() {
    srand(time(NULL));
    int peso_total = 0;

    for (int i = 0; i < TOTAL_EVENTOS; i++) {
        if (eventos[i].disponible && eventos[i].peso > 0) {
            peso_total += eventos[i].peso;
        }
    }

    if (peso_total <= 0) {
        return EVENTO_NADA;
    }

    int num_aleatorio = rand() % peso_total;
    int acumulado = 0;

    for (int i = 0; i < TOTAL_EVENTOS; i++) {
        if (eventos[i].disponible && eventos[i].peso >= 0) {
            acumulado += eventos[i].peso;
            if (acumulado < peso_total) {
                return eventos[i].id;
            }
        }
    }

    return EVENTO_NADA;
}

static void eventos_cambiar_estado(TipoEvento id, bool estado) {
    if (id >= 0 && id < TOTAL_EVENTOS) {
        eventos[id].disponible = estado;
    }
}

static int calcular_promedio(Club *club) {
    int suma = 0;
    for (int i = 0; i < 11; i++) {
        suma += club->plantilla[i].media;
    }
    
    return suma / 11;
}

static void imprimir_repetido(const char* texto, int veces) {
    for (int i = 0; i < veces; i++) {
        printf("%s", texto);
    }
}

void eventos_ejecutar(Club *club) {
    if (club->total_jugadores <= 11) {
        eventos_cambiar_estado(EVENTO_MUERTE, false);
    } else {
        eventos_cambiar_estado(EVENTO_MUERTE, true);
    }
    
    TipoEvento elegido = eventos_seleccionar();

    int r;
    switch (elegido) {
        case EVENTO_NADA:
            break;
        case EVENTO_PATROCINADOR:
            club->presupuesto += 3000000;
            break;
        case EVENTO_LESION:
            r = rand() % club->total_jugadores;
            club->plantilla[r].media -= 5;
            if (club->plantilla[r].media <= 0) {
                club->plantilla[r].media = 1;
            }
            printf("Media de %s: %d -> %d.\n\n", club->plantilla[r].nombre, club->plantilla[r].media + 5, club->plantilla[r].media);
            break;
        case EVENTO_MUERTE:
            r = rand() % club->total_jugadores;
            printf("%s se ha quitado de la plantilla.\n\n",  club->plantilla[r].nombre);
            // como eliminar a jugador r del arreglo??? metodo en utils?
            break;
        default:
            break;
    }
}

void eventos_final(Club *club) {
    int media = calcular_promedio(club);
    int min = 10, max = 20;
    int media_rival = (media - min) + rand() % (media + max - media - min + 1);
    // TODO: más printf aquí
    if (media_rival < media) {
        printf("Eres campeón!!!\n");
    } else if (media_rival > media) {
        printf("Perdiste...\n");
    } else {
        printf("Anotado: A\tFallado: F\n");
        printf("Penales\n");
        printf("0 - 0\n");
        printf("Tú: \n");
        printf("\t X X X X X\n");
        printf("Rival: \n");
        printf("\t X X X X X\n");
        printf("Cobrando penal...\n");
        ssleep(2000); 

        int goles_propios = 0;
        int goles_rival = 0;

        for (int i = 0; i < 5; i++) {
            int r_propio = rand() % 2;
            int r_rival = rand() % 2;
            // Cobro propio
            goles_propios += r_propio;
            goles_rival += r_rival;
            borrar_lineas(6);
            printf("%d - %d\n", goles_propios, goles_rival);
            printf("Tú: \n");
            imprimir_repetido("A ", goles_propios); imprimir_repetido("F ", goles_propios - 5); printf("\n");
            printf("Rival: \n");
            imprimir_repetido("A ", goles_rival); imprimir_repetido("F ", goles_rival - 5); printf("\n");
            printf("Cobrando siguientes dos penales...\n");
            ssleep(2000);
            // TODO: Agregar condicion de victoria y muerte súbita.
        }

    }

}