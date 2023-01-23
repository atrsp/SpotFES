#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"
#include "musica.h"

struct playlist
{
    int *id_musicas;
    char nome[TAM_NOME_PLAYLIST];
    int musicas_usado;
    int musicas_alocado;


};

// ============ ESTRUTURA ============

Playlist Playlist_cria(char *nome)
{
    Playlist p = (Playlist)calloc(1, sizeof(struct playlist));

    strcpy(p->nome, nome);

    printf("\n\033[93m==Playlist '%s' criada com sucesso==\033[0m\n\n", p->nome);
    p->id_musicas = (int *)calloc(QTD_INICIAL, sizeof(int));

    p->musicas_alocado = QTD_INICIAL;
    p->musicas_usado = 0;

    return p;
}

Playlist *Playlists_vetor_constroi()
{
    Playlist *p = (Playlist *)malloc(QTD_PLAYLISTS * sizeof(Playlist));

    return p;
}

void Playlist_id_musica_realoca(Playlist p)
{
    if (p->musicas_usado == p->musicas_alocado)
    {
        p->musicas_alocado *= 2;
        p->id_musicas = (int *)realloc(p->id_musicas, p->musicas_alocado * sizeof(int));
    }
}

void Playlists_destroi(Playlist *p, int qtd_playlists)
{
    for (int j = 0; j < qtd_playlists; j++)
    {
        free(p[j]->id_musicas);
        free(p[j]);
    }
    free(p);
}

// ============ FUNCIONALIDADES ============

void Playlists_listar(Playlist *p, int qtd_playlists)
{
    // playlists existentes
    printf("\n\033[93m==Playlists existentes==\033[0m\n\n");
    for (int i = 0; i < qtd_playlists; i++)
    {
        printf(" \033[96m   [\033[0m%d\033[96m]\033[0m - \033[3m'%s'\033[0m; %d musica(s);\n\n",
               i, p[i]->nome, p[i]->musicas_usado);
    }
}

void Playlist_lista(Playlist *p, Musica *m, int musicas_usado, int playlist_usado)
{
    int indice;

    printf("Digite o indice da playlist a ser listada: \033[92m");
    scanf("%d", &indice);

    if (indice < 0 || indice >= playlist_usado)
    {
        printf("\033[91m\nPlaylist de indice '%d' nao existe, tente novamente.\n", indice);
        printf("Tente digitar um numero entre 0 e %d :)\033[0m\n\n", playlist_usado - 1);
    }

    else
    {
        printf("\n\033[93m==Playlist selecionada==\033[0m\n");
        printf("\033[95m\nNome da playlist:\033[0m '\033[3m%s\033[0m'\n\n", p[indice]->nome);

        printf(" \033[93m> \033[0m\033[4mMusicas\033[0m:\n");
        for (int i = 0; i < p[indice]->musicas_usado; i++)
        {
            Musica_adicionada_playlist(m, p[indice]->id_musicas[i], musicas_usado);
        }
    }
}

Playlist *Playlist_add_musica(Playlist *p, int indice_musica, int indice_playlist)
{
    Playlist_id_musica_realoca(p[indice_playlist]);

    // a nova musica da playlist recebe o indice da musica digitado pelo usuario
    p[indice_playlist]->id_musicas[p[indice_playlist]->musicas_usado] = indice_musica;

    p[indice_playlist]->musicas_usado++;

    return p;
}

// ============ AUXILIARES ============

char *Playlist_nome_busca(Playlist *p, int indice_playlist)
{
    return p[indice_playlist]->nome;
}

int Playlist_verifica_indice(Playlist *p, int indice_musica, int indice_playlist)
{
    for (int i = 0; i < p[indice_playlist]->musicas_usado; i++)
    {
        if (p[indice_playlist]->id_musicas[i] == indice_musica)
        {
            return 1;
        }
    }

    return 0;
}
