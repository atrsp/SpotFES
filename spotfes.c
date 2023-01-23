#include "artista.h"
#include "musica.h"
#include "spotfes.h"
#include "playlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct spotfes
{

    int artistas_alocado;
    int artistas_usado;
    Artista *artista;

    int musicas_alocado;
    int musicas_usado;
    Musica *musica;

    int playlists_alocado;
    int playlists_usado;
    int *musicas_add_playlist;
    int qtd_musicas_playlist;
    int qtd_musicas_playlist_alocado;
    Playlist *playlist;
};

// ============ ESTRUTURA ============

Spotfes Spotfes_constroi()
{
    Spotfes s = (Spotfes)calloc(1, sizeof(struct spotfes));

    s->artista = Artistas_vetor_constroi();
    s->artistas_alocado = QTD_INICIAL;
    s->artistas_usado = 0;

    s->musica = Musicas_vetor_constroi();
    s->musicas_alocado = QTD_INICIAL;
    s->musicas_usado = 0;

    s->playlist = Playlists_vetor_constroi();
    s->playlists_alocado = QTD_INICIAL;
    s->playlists_usado = 0;
    s->qtd_musicas_playlist = 0;
    s->qtd_musicas_playlist_alocado = QTD_INICIAL;

    s->musicas_add_playlist = (int *)calloc(QTD_INICIAL, sizeof(int));

    return s;
}

void Musicas_realoca(Spotfes s)
{
    if (s->musicas_alocado == s->musicas_usado)
    {
        s->musicas_alocado *= 2;
        s->musica = (Musica *)realloc(s->musica, s->musicas_alocado * sizeof(Musica));
    }
}

void Spotfes_destroi(Spotfes s)
{

    Musicas_destroi(s->musica, s->musicas_usado);
    Artistas_destroi(s->artista, s->artistas_usado);
    Playlists_destroi(s->playlist, s->playlists_usado);

    free(s->musicas_add_playlist);

    free(s);
}

void Artistas_realoca(Spotfes s)
{
    if (s->artistas_alocado == s->artistas_usado)
    {
        s->artistas_alocado *= 2;
        s->artista = (Artista *)realloc(s->artista, s->artistas_alocado * sizeof(Artista));
    }
}

void Playlists_realoca(Spotfes s)
{
    if (s->playlists_alocado == s->playlists_usado)
    {
        s->playlists_alocado *= 2;
        s->playlist = (Playlist *)realloc(s->playlist, s->playlists_alocado * sizeof(Playlist));
    }
}

void Musicas_add_playlist_realoca(Spotfes s)
{
    if (s->qtd_musicas_playlist_alocado == s->qtd_musicas_playlist)
    {
        s->qtd_musicas_playlist_alocado *= 2;
        s->musicas_add_playlist = (int *)realloc(s->musicas_add_playlist, s->qtd_musicas_playlist_alocado * sizeof(int));
    }
}

void Spotfes_interrompe (Spotfes s, int arquivos_lidos){

    if (arquivos_lidos == 0){
        free (s->musicas_add_playlist);
        free (s->artista);
        free (s->musica);
        free (s->playlist);
        free (s);
    }

    else if (arquivos_lidos == 1){
        Artistas_destroi(s->artista, s->artistas_usado);
        free (s->musicas_add_playlist);
        free (s->musica);
        free (s->playlist);
        free(s);
    }
}


// ============ LEITURA ============

Spotfes Spotfes_le(Spotfes s, int argc, char **argv)
{
    FILE *file_artistas;
    FILE *file_musicas;

    char filename_artistas[100];
    char filename_musicas[100];

    int arquivos_lidos = 0;

    if (argc <= 2)
    {

        // a entrada padrão do código é o nome do arquivo contendo as informações dos artistas seguido do arquivo das musicas

        printf("\033[91mERRO: O diretorio de arquivos de configuracao nao foi informado.\n");
        printf("\nATENCAO: Favor inserir, na linha de comando, os nomes dos arquivos dos dados de artistas e de musicas, respectivamente.\n");
        printf("Exemplo: ./arquivo_executavel arquivo_artistas.csv arquivo_musicas.csv\033[0m\n\n");

        Spotfes_interrompe (s, arquivos_lidos);

        exit(0);
    }

    sprintf(filename_artistas, "TP1-SpotFES/data/%s", argv[1]);
    file_artistas = fopen(filename_artistas, "r");

    if (!file_artistas)
    {
        printf("\033[91m-Nao foi possivel ler o arquivo '%s' pelo caminho '%s'-\n", argv[1], filename_artistas);

        printf("\nATENCAO: Favor inserir, na linha de comando, os nomes dos arquivos dos dados de artistas e de musicas, respectivamente.\n");
        printf("Exemplo: ./arquivo_executavel arquivo_artistas.csv arquivo_musicas.csv\033[0m\n");
        
        Spotfes_interrompe (s, arquivos_lidos);
        exit(0);
    }

    printf("\n\n\033[93mInicializando programa... aguarde, por favor.\n\n\033[0m");
    while (1)
    {

        if (feof(file_artistas))
            break;
            
        Artistas_realoca(s);
        s->artista[s->artistas_usado] = Artista_cria();
        s->artista[s->artistas_usado] = Artista_le(s->artista[s->artistas_usado], file_artistas);
        s->artistas_usado++;
    }

    arquivos_lidos++;
    fclose(file_artistas);

    sprintf(filename_musicas, "TP1-SpotFES/data/%s", argv[2]);
    file_musicas = fopen(filename_musicas, "r");

    if (!file_musicas)
    {
        printf("\033[91m-Nao foi possivel ler o arquivo '%s' pelo caminho '%s'-\n", argv[2], filename_musicas);

        printf("\nATENCAO: Favor inserir, na linha de comando, os nomes dos arquivos dos dados de artistas e de musicas, respectivamente.\n");
        printf("Exemplo: ./arquivo_executavel arquivo_artistas.csv arquivo_musicas.csv\033[0m\n");

        Spotfes_interrompe (s, arquivos_lidos);

        exit(0);
    }

    fscanf(file_musicas, "%*[^\n]\n"); // eliminar primeira linha do tracks_full
    while (1)
    {
        if (feof(file_musicas))
            break;

        Musicas_realoca(s);
        s->musica[s->musicas_usado] = Musica_cria();
        s->musica[s->musicas_usado] = Musica_le(s->musica[s->musicas_usado], file_musicas);
        s->musicas_usado++;
    }

    arquivos_lidos++;
    fclose(file_musicas);

    return s;
}

// ============ FUNCIONALIDADES ============

void Imprime_Menu()
{
    printf("\n\033[1m\033[92m\033[3m[Spotfes]\033[0m\n\n");
    printf("\033[1m Menu: \033[0m");
    printf("\t \033[35m1. \033[90mBuscar musicas;\n");
    printf("\t \033[35m2. \033[90mListar uma musica;\n");
    printf("\t \033[35m3. \033[90mExecutar uma musica;\n");
    printf("\t \033[35m4. \033[90mCriar uma playlist;\n");
    printf("\t \033[35m5. \033[90mListar playlists;\n");
    printf("\t \033[35m6. \033[90mListar uma playlist;\n");
    printf("\t \033[35m7. \033[90mAdiciona uma musica na playlist;\n");
    printf("\t \033[35m8. \033[90mRecomendar musicas;\n");
    printf("\t \033[35m9. \033[90mGerar relatorio;\n");
    printf("\t \033[35m10.\033[90m Encerrar spotfes;\n\n\033[0m");
    printf ("Digite o numero da operacao desejada: \033[92m");
}

Spotfes Adiciona_musica(Spotfes s)
{

    int indice_playlist, indice_musica;

    printf("Digite o indice da playlist que deseja modificar: \033[92m");
    scanf("%d", &indice_playlist);

    if (indice_playlist < 0 || indice_playlist >= s->playlists_usado)
    {
        printf("\033[91m\nPlaylist de indice '%d' nao existe, tente novamente.\n", indice_playlist);
        printf("Tente digitar um numero entre 0 e %d :)\033[0m\n\n", s->playlists_usado - 1);
    }

    else
    {
        printf("\033[0mDigite o indice da musica que deseja adicionar a playlist: \033[92m");
        scanf("%d", &indice_musica);

        if (indice_musica < 0 || indice_musica >= s->musicas_usado)
        {
            printf("\033[91m\nMusica de indice '%d' nao existe, tente novamente.\n", indice_musica);
            printf("Tente digitar um numero entre 0 e %d :)\033[0m\n\n", s->musicas_usado - 1);
        }

        else if (Playlist_verifica_indice(s->playlist, indice_musica, indice_playlist) == 1)
        {
            printf("\033[91m\nMusica de indice '%d' ja existe na playlist, tente outra.\033[0m\n\n", indice_musica);
        }

        else
        {
            s->playlist = Playlist_add_musica(s->playlist, indice_musica, indice_playlist);

            int existe = 0;
            Musicas_add_playlist_realoca(s);

            for (int i = 0; i < s->qtd_musicas_playlist; i++)
            {
                if (s->musicas_add_playlist[i] == indice_musica)
                {
                    existe = 1;
                }
            }

            if (existe == 0)
            {
                s->musicas_add_playlist[s->qtd_musicas_playlist] = indice_musica;
                s->qtd_musicas_playlist++;
            }

            char *nome_musica = strdup(Musica_nome_busca(indice_musica, s->musica));
            char *nome_playlist = strdup(Playlist_nome_busca(s->playlist, indice_playlist));

            printf("\n\n\033[93m==A musica '%s' foi adicionada com sucesso a playlist '%s'==\n\n", nome_musica, nome_playlist);

            s->musica = Musica_adicionada_atualiza(indice_musica, s->musica);

            free(nome_musica);
            free(nome_playlist);
        }
    }
    return s;
}

void Spotfes_funcionalidades(Spotfes s)
{

    int funcionalidade;
    int flagPlaylist = 0;

    while (1)
    {

        Imprime_Menu();
        scanf("%d%*c", &funcionalidade);
        printf ("\033[0m");

        if (funcionalidade == ENCERRA)
        {

            printf("\n\033[91mEncerrando \033[3m\033[1m[Spotfes]...\033[0m\n");
            break;
        }

        else if (funcionalidade == BUSCA)
        {
            Musica_busca(s->musica, s->musicas_usado);
        }

        else if (funcionalidade == LISTA_MUS)
        {
            Lista_uma_musica(s->musica, s->musicas_usado, s->artista, s->artistas_usado);
        }

        else if (funcionalidade == EXECUTA)
        {
            Executa_Musica(s->musica, s->musicas_usado);
        }

        else if (funcionalidade == CRIA)
        {
            Playlists_realoca(s);
            char nome[TAM_NOME_PLAYLIST];

            printf("Digite o nome da playlist [ate 100 caracteres]: \033[92m");
            scanf("%[^\n]", nome);

            int flagNomeIgual = 0;
            for (int i = 0; i < s->playlists_usado; i++)
            {
                if (strcmp(nome, Playlist_nome_busca(s->playlist, i)) == 0)
                {
                    flagNomeIgual = 1;
                }
            }

            if (flagNomeIgual == 1)
            {
                printf("\n\033[91mJa existe uma playlist com esse nome, tente novamente.\033[0m\n\n");
            }

            else
            {
                s->playlist[s->playlists_usado] = Playlist_cria(nome);
                s->playlists_usado++;
                flagPlaylist = 1;
            }
        }

        else if (funcionalidade == LISTA_TOT_PLAYL)
        {
            if (flagPlaylist == 1)
            {
                Playlists_listar(s->playlist, s->playlists_usado);
            }

            else
                printf("\033[91mAinda nao ha playlists criadas, digite '4' para criar.\033[0m\n\n");
        }

        else if (funcionalidade == LISTA_PLAYL)
        {
            if (flagPlaylist == 1)
            {
                Playlist_lista(s->playlist, s->musica, s->musicas_usado, s->playlists_usado);
            }

            else
                printf("\033[91mAinda nao ha playlists criadas, digite '4' para criar.\033[0m\n\n");
        }

        else if (funcionalidade == ADD)
        {
            if (flagPlaylist == 1)
            {
                s = Adiciona_musica(s);
            }

            else
                printf("\033[91mAinda nao ha playlists criadas, digite '4' para criar\033[0m\n\n");
        }

        else if (funcionalidade == RECOMENDA)
        {
            printf("\033[91mDesculpe, esse servico esta indisponivel no momento :(\n");
            printf("Estamos trabalhando nisso!\033[0m\n\n");
        }

        else if (funcionalidade == RELAT)
        {
            Gera_relatorio(s->musica, s->qtd_musicas_playlist, s->musicas_add_playlist);
        }

        else
        {
            printf("\033[91mOperacao invalida.\nFavor digitar um dos numeros do menu.\033[0m\n\n");
        }
    }
}


