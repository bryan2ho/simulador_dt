#ifndef SISTEMA_EVENTOS_H
#define SISTEMA_EVENTOS_H
#include "estructuras.h"

typedef enum {
    EVENTO_NADA,
    EVENTO_PATROCINADOR,
    EVENTO_LESION,
    EVENTO_MUERTE,
    TOTAL_EVENTOS
} TipoEvento;

void eventos_ejecutar(Club *club);
void eventos_final(Club *club);

#endif