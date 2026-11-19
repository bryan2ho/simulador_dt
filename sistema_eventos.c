#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    {EVENTO_MUERTE, "A un jugador le dio un infarto durante el entrenamiento. Murió.\n", 5, false}
    // AGREGAR EVENTOS

};

static const Evento* eventos_seleccionar() {
    int peso_total = 0;

    for (int i = 0; i < TOTAL_EVENTOS; i++) {
        if (eventos[i].disponible && eventos[i].peso > 0) {
            peso_total += eventos[i].peso;
        }
    }

    if (peso_total <= 0) {
        return &eventos[EVENTO_NADA];
    }

    int num_aleatorio = rand() % peso_total;
    int acumulado = 0;

    for (int i = 0; i < TOTAL_EVENTOS; i++) {
        if (eventos[i].disponible && eventos[i].peso >= 0) {
            acumulado += eventos[i].peso;
            if (num_aleatorio < acumulado) {
                return &eventos[i];
            }
        }
    }

    return &eventos[EVENTO_NADA];
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

void eventos_ejecutar(Club *club) {
    if (club == NULL) return;

    eventos_cambiar_estado(EVENTO_MUERTE, club->total_jugadores > 11);
    
    const Evento* elegido = eventos_seleccionar();
    printf("%s", elegido->desc);

    int r;
    switch (elegido->id) {
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
            eliminar_jugador(club, r);
            break;
        default:
            break;
    }
}

void eventos_final(Club *club) {
    int media = calcular_promedio(club);
    int min_diff = -3, max_diff = 3;
    int diff = min_diff + rand() % (max_diff - min_diff + 1);
    int media_rival = media + diff;
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
        char tiros_propios[5] = {'X', 'X','X', 'X', 'X'};
        char tiros_rival[5] = {'X', 'X','X', 'X', 'X'};
        bool terminado = false;

        for (int i = 0; i < 5 && !terminado; i++) {
            int r_propio = rand() % 2;
            goles_propios += r_propio;
            tiros_propios[i] = r_propio ? 'A' : 'F';
            
            int r_rival = 0;
            int restantes_propios = 4 - i;
            int restantes_rival_antes = 5 - i;
            
            if (goles_propios - goles_rival > restantes_rival_antes) {
                terminado = true;
            } else {
                r_rival = rand() % 2;
                goles_rival += r_rival;
                tiros_rival[i] = r_rival ? 'A' : 'F';

                int restantes_rival = 4 - i;

                if (goles_propios - goles_rival > restantes_rival ||
                    goles_rival - goles_propios > restantes_propios) {
                    
                    terminado = true;
                }
            }

            borrar_lineas(6);
            printf("%d - %d\n", goles_propios, goles_rival);
            printf("Tú: \n\t");
            for (int j = 0; j < 5; j++) printf("%c ", tiros_propios[j]);
            printf("\nRival: \n\t");
            for (int j = 0; j < 5; j++) printf("%c ", tiros_rival[j]);
            printf("\n");

            if (!terminado && i < 4) {
                printf("Cobrando siguientes dos penales...\n");
                ssleep(2000);
            } else if (!terminado && i == 4 && goles_propios == goles_rival) {
                printf("Empate. Vamos a muerte súbita...\n");
                ssleep(2000);
            } else {
                printf("Tanda de penales terminada.\n");
                ssleep(1000);
            }
        }

        while (goles_propios == goles_rival) {
            int r_propio = rand() % 2;
            int r_rival = rand() % 2;
            goles_propios += r_propio;
            goles_rival += r_rival;

            borrar_lineas(6);
            printf("%d - %d (Muerte Súbita)\n", goles_propios, goles_rival);
            printf("Tú: \n\t %c\n", r_propio ? 'A' : 'F');
            printf("Rival: \n\t %c\n", r_rival ? 'A' : 'F');
            
            if (goles_propios == goles_rival) {
                printf("Siguen empatados, siguiente ronda...\n");
                ssleep(2000);
            } else {
                printf("Muerte súbita definida.\n");
                ssleep(1500);
            }
        }

        if (goles_propios > goles_rival) {
            printf("\nGanaste en penales (%d - %d). Eres campeón!!!\n", goles_propios, goles_rival);
        } else {
            printf("\nPerdiste en penales (%d - %d)...\n", goles_propios, goles_rival);
        }

    }

}