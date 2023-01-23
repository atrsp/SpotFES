#pragma once

#include <stdio.h>
#include <stdlib.h>

#define TAM_ID 30
#define TAM_NOME 1000
#define QTD_INICIAL 100
#define TAM_GENEROS 1000
#define TAM_N_SEGUIDORES 50
#define TAM_NOME_ARTISTA 1000

typedef struct artista *Artista;

// estrutura:
Artista Artista_cria();
Artista *Artistas_vetor_constroi();
void Artistas_destroi(Artista *a, int qtd_alocada);

// leitura:
Artista Artista_le(Artista a, FILE *f);

// funcionalidade:
void Lista_artistas(char *artista, Artista *a, int artistas_usado);
