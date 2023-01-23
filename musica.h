#pragma once

#include "criterios.h"
#include "artista.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM_DATA 90
#define QTD_INICIAL 100
#define ARTISTAS_ALOCADOS 2
#define TAM_ID_ARTISTA 10000
#define TAM_NOME_ARTISTA_MUSICA 10000

typedef struct musica *Musica;

// estrutura:
Musica Musica_cria();
Musica *Musicas_vetor_constroi();
Musica Artistas_mus_realoca(Musica m);
Musica Id_artistas_mus_realoca(Musica m);
void Musicas_destroi(Musica *m, int qtd_alocada);
void Musica_artistas_destroi(int artistas_usado, int id_artista_usado, char **artistas, char **id_artistas);

// leitura:
Musica Musica_le(Musica m, FILE *f);

// funcionalidades:
void Gera_relatorio(Musica *m, int qtd_musicas_playlist, int *vet_indices);
void Executa_Musica(Musica *m, int musicas_usado);
void Musica_busca(Musica *musicas, int qtd_musicas);
void Lista_uma_musica(Musica *m, int musica_usado, Artista *a, int artistas_usado);

// auxiliares:
void lwrcase(char *str);
char *Musica_nome_busca(int indice_musica, Musica *m);
Musica *Musica_adicionada_atualiza(int indice, Musica *m);
void Musica_adicionada_playlist(Musica *m, int indice, int musicas_usado);
