#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "criterios.h"

struct criterios
{

    double danceability;
    double energy;
    int key;
    double loudness;
    int mode;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveness;
    double valence;
    double bpm;
    int time_signature;
};

// ============ ESTRUTURA ============

Criterios Criterios_constroi()
{
    Criterios c = (Criterios)calloc(1, sizeof(struct criterios));
    return c;
}

// ============ LEITURA ============

Criterios Criterios_le(Criterios c, FILE *f)
{

    fscanf(f, "%lf;", &c->danceability);
    fscanf(f, "%lf;", &c->energy);
    fscanf(f, "%d;", &c->key);
    fscanf(f, "%lf;", &c->loudness);
    fscanf(f, "%d;", &c->mode);
    fscanf(f, "%lf;", &c->speechiness);
    fscanf(f, "%lf;", &c->acousticness);
    fscanf(f, "%lf;", &c->instrumentalness);
    fscanf(f, "%lf;", &c->liveness);
    fscanf(f, "%lf;", &c->valence);
    fscanf(f, "%lf;", &c->bpm);
    fscanf(f, "%d\n", &c->time_signature);

    return c;
}

// ============ FUNCIONALIDADES ============

void Lista_criterios(Criterios c)
{

    printf("    -danceability: \033[90m%.2lf\033[0m;\n", c->danceability);
    printf("    -energy: \033[90m%.2lf\033[0m;\n", c->energy);
    printf("    -key: \033[90m%d\033[0m;\n", c->key);
    printf("    -loudness: \033[90m%.2lf\033[0m;\n", c->loudness);
    printf("    -mode: \033[90m%d\033[0m;\n", c->mode);
    printf("    -speechiness: \033[90m%.2lf\033[0m;\n", c->speechiness);
    printf("    -acousticness: \033[90m%.2lf\033[0m;\n", c->acousticness);
    printf("    -instrumentalness: \033[90m%.2lf\033[0m;\n", c->instrumentalness);
    printf("    -liveness: \033[90m%.2lf\033[0m;\n", c->liveness);
    printf("    -valence: \033[90m%.2lf\033[0m;\n", c->valence);
    printf("    -bpm: \033[90m%.2lf\033[0m;\n", c->bpm);
    printf("    -time signature: \033[90m%d\033[0m;\n\n", c->time_signature);
}