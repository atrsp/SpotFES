#pragma once

#include "musica.h"

#define QTD_PLAYLISTS 100
#define TAM_NOME_PLAYLIST 100
#define QTD_MUSICAS 2

typedef struct playlist *Playlist;

// estrutura:
Playlist Playlist_cria(char *nome);
Playlist *Playlists_vetor_constroi();
void Playlist_id_musica_realoca(Playlist p);
void Playlists_destroi(Playlist *p, int qtd_playlists);

// funcionalidades:
void Playlists_listar(Playlist *p, int qtd_playlists);
void Playlist_lista(Playlist *p, Musica *m, int musicas_usado, int playlist_usado);
Playlist *Playlist_add_musica(Playlist *p, int indice_musica, int indice_playlist);

// auxiliares:
char *Playlist_nome_busca(Playlist *p, int indice_playlist);
int Playlist_verifica_indice(Playlist *p, int indice_musica, int indice_playlist);
