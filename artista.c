#include "artista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artista
{

    char id[TAM_ID];
    char n_seguidores[TAM_N_SEGUIDORES];
    char *generos;
    char *nome;
    int popularidade;

    int qtd_add_playlist;
};

// ============ ESTRUTURA ============

Artista Artista_cria()
{

    Artista a = (Artista)calloc(1, sizeof(struct artista));
    a->generos = (char *)malloc(TAM_GENEROS * sizeof(char));
    a->nome = (char *)malloc(TAM_NOME_ARTISTA * sizeof(char));
    a->qtd_add_playlist = 0;

    return a;
}

Artista *Artistas_vetor_constroi()
{
    Artista *a = (Artista *)calloc(QTD_INICIAL, sizeof(Artista));

    return a;
}

void Artistas_destroi(Artista *a, int qtd_alocada)
{
    for (int i = 0; i < qtd_alocada; i++)
    {
        free(a[i]->nome);
        free(a[i]->generos);
        free(a[i]);
    }

    free(a);
}

// ============ LEITURA ============

Artista Artista_le(Artista a, FILE *f)
{

    fscanf(f, "%[^;];", a->id);
    fscanf(f, "%[^;];", a->n_seguidores);
    fscanf(f, "%[^;];", a->generos);
    fscanf(f, "%[^;];", a->nome);
    fscanf(f, "%d\n", &a->popularidade);

    return a;
}

// ============ FUNCIONALIDADE ============

void Lista_artistas(char *artista, Artista *a, int artistas_usado)
{

    for (int i = 0; i < artistas_usado; i++)
    {
        if (strcmp(artista, a[i]->nome) == 0)
        {
            printf("    -nome: \033[90m%s\033[0m;\n", a[i]->nome);
            printf("    -id: \033[90m%s\033[0m;\n", a[i]->id);
            printf("    -seguidores: \033[90m%s\033[0m;\n", a[i]->n_seguidores);
            printf("    -generos: \033[90m%s\033[0m;\n", a[i]->generos);
            printf("    -popularidade: \033[90m%d\033[0m;\n\n", a[i]->popularidade);
        }
    }
}
