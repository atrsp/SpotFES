#pragma once

#define QTD_INICIAL 100

typedef struct spotfes *Spotfes;

typedef enum
{

    BUSCA = 1,
    LISTA_MUS = 2,
    EXECUTA = 3,
    CRIA = 4,
    LISTA_TOT_PLAYL = 5,
    LISTA_PLAYL = 6,
    ADD = 7,
    RECOMENDA = 8,
    RELAT = 9,
    ENCERRA = 10,

} FunctionType;

// estrutura:
Spotfes Spotfes_constroi();
void Musicas_realoca(Spotfes s);
void Spotfes_destroi(Spotfes s);
void Artistas_realoca(Spotfes s);
void Playlists_realoca(Spotfes s);
void Musicas_add_playlist_realoca(Spotfes s);
void Spotfes_interrompe (Spotfes s, int arquivos_lidos);


// leitura:
Spotfes Spotfes_le(Spotfes s, int argc, char **argv);

// funcionalidades:
void Imprime_Menu();
Spotfes Adiciona_musica(Spotfes s);
void Spotfes_funcionalidades(Spotfes s);
