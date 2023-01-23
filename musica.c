#include "musica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musica
{
    char id[30];

    char **artistas;
    char **id_artistas;

    int id_artistas_usado;
    int id_artistas_alocado;

    int artistas_usado;
    int artistas_alocado;

    int qtd_add_playlists;

    char nome[TAM_NOME];
    int popularidade;
    int explicito;
    int duracao_ms;
    char data[TAM_DATA];

    Criterios criterios;
};

// ============ ESTRUTURA ============

Musica Musica_cria()
{
    Musica m = (struct musica *)calloc(1, sizeof(struct musica));
    m->criterios = Criterios_constroi();

    m->artistas = (char **)malloc(ARTISTAS_ALOCADOS * sizeof(char *));
    m->id_artistas = (char **)malloc(ARTISTAS_ALOCADOS * sizeof(char *));

    m->artistas_alocado = ARTISTAS_ALOCADOS;
    m->artistas_usado = 0;

    m->id_artistas_alocado = ARTISTAS_ALOCADOS;
    m->id_artistas_usado = 0;
    m->qtd_add_playlists = 0;

    return m;
}

Musica *Musicas_vetor_constroi()
{
    Musica *m = (Musica *)calloc(QTD_INICIAL, sizeof(Musica));

    return m;
}

Musica Artistas_mus_realoca(Musica m)
{
    if (m->artistas_alocado == m->artistas_usado)
    {
        m->artistas_alocado *= 2;
        m->artistas = (char **)realloc(m->artistas, m->artistas_alocado * sizeof(char *));
    }

    return m;
}

Musica Id_artistas_mus_realoca(Musica m)
{
    if (m->id_artistas_alocado == m->id_artistas_usado)
    {
        m->id_artistas_alocado *= 2;
        m->id_artistas = (char **)realloc(m->id_artistas, m->id_artistas_alocado * sizeof(char *));
    }

    return m;
}

void Musicas_destroi(Musica *m, int qtd_alocada)
{
    int i = 0;
    for (i = 0; i < qtd_alocada; i++)
    {
        Musica_artistas_destroi(m[i]->artistas_usado, m[i]->id_artistas_usado, m[i]->artistas, m[i]->id_artistas);

        free(m[i]->criterios);
        free(m[i]);
    }

    free(m);
}

void Musica_artistas_destroi(int artistas_usado, int id_artista_usado, char **artistas, char **id_artistas)
{

    for (int i = 0; i < artistas_usado; i++)
    {
        free(artistas[i]);
    }

    for (int i = 0; i < id_artista_usado; i++)
    {
        free(id_artistas[i]);
    }

    free(artistas);
    free(id_artistas);
}

// ============ LEITURA ============

Musica Musica_le(Musica m, FILE *f)
{

    char artistas_mus[TAM_NOME_ARTISTA_MUSICA];
    char id_artistas[TAM_ID_ARTISTA];
    const char s[2] = "|";
    int i = 0;
    int j = 0;

    fscanf(f, "%[^;];", m->id);
    fscanf(f, "%[^;];", m->nome);
    fscanf(f, "%d;", &m->popularidade);
    fscanf(f, "%d;", &m->duracao_ms);
    fscanf(f, "%d;", &m->explicito);
    fscanf(f, "%[^;];", artistas_mus);
    fscanf(f, "%[^;];", id_artistas);
    fscanf(f, "%[^;];", m->data);
    m->criterios = Criterios_le(m->criterios, f);

    char *trecho = strtok(artistas_mus, s);

    if (trecho == NULL)
    {
        m->artistas[i] = strdup(trecho);
    }

    else
    {
        while (trecho != NULL)
        {

            m = Artistas_mus_realoca(m);
            m->artistas[i] = strdup(trecho);
            trecho = strtok(NULL, s);

            i++;
            m->artistas_usado++;
        }
    }

    char *trecho_id = strtok(id_artistas, s);

    if (trecho_id == NULL)
    {
        m->id_artistas[j] = strdup(trecho_id);
    }

    else
    {
        while (trecho_id != NULL)
        {
            m = Id_artistas_mus_realoca(m);
            m->id_artistas[j] = strdup(trecho_id);
            trecho_id = strtok(NULL, s);

            j++;
            m->id_artistas_usado++;
        }
    }

    return m;
}

// ============ FUNCIONALIDADES ============

void Gera_relatorio(Musica *m, int qtd_musicas_playlist, int *vet_indices)
{

    int aux;

    for (int i = 0; i < qtd_musicas_playlist; i++)
    {
        for (int j = i; j < qtd_musicas_playlist; j++)
        {
            if (m[vet_indices[j]]->qtd_add_playlists >= m[vet_indices[i]]->qtd_add_playlists)
            {
                aux = vet_indices[j];
                vet_indices[j] = vet_indices[i];
                vet_indices[i] = aux;
            }
        }
    }

    char *filename_mus = "relatorio_mus.txt";

    FILE *mus_file = fopen(filename_mus, "w");

    printf("\033[93m==Relatorio disponivel no arquivo '%s'==\n\n\033[0m", filename_mus);
    fprintf(mus_file, "=== Relatorio das Musicas ===\n\n");

    for (int i = 0; i < qtd_musicas_playlist; i++)
    {
        fprintf(mus_file, "[%d] - %s [adicionada em %d playlist(s)]\n", vet_indices[i], m[vet_indices[i]]->nome, m[vet_indices[i]]->qtd_add_playlists);
    }

    fclose(mus_file);
}

void Executa_Musica(Musica *m, int musicas_usado)
{
    int indice;
    char caminho_executavel[100];

    printf("Digite o indice da musica que deseja tocar: \033[92m");
    scanf("%d", &indice);

    printf("\033[0m");

    if (indice >= musicas_usado || indice < 0)
    {
        printf("\033[91mNao foi possivel buscar a musica de indice '%d'.\n", indice);
        printf("Tente digitar um numero entre 0 e %d :)\033[0m\n\n", musicas_usado - 1);
    }
    else
    {
        sprintf(caminho_executavel, "https://open.spotify.com/track/%s", m[indice]->id);

        printf("\033[93mAcesse o link\033[0m: %s\n\n", caminho_executavel);

        sprintf(caminho_executavel, "firefox https://open.spotify.com/track/%s", m[indice]->id);

        system(caminho_executavel); // comando para executar a string no terminal
    }
}

void Musica_busca(Musica *m, int qtd_musicas)
{
    // transforma a string digitada pelo usuario e a string da musica em lwr case e
    // verifica se a do usuario esta contida em alguma musica do vetor;
    char str[1000];
    char *p;

    printf("Digite o nome da musica que gostaria de buscar: \033[92m");
    scanf("%[^\n]%*c", str);
    printf("\n\033[0mBuscando '\033[3m%s\033[0m'...\n\n", str);

    printf("\033[93m==Resultados obtidos==\033[0m\n\n");

    lwrcase(str);

    for (int i = 0; i < qtd_musicas; i++)
    {
        char *nome_lwr = strdup(m[i]->nome);
        lwrcase(nome_lwr);

        p = strstr(nome_lwr, str);

        if (p)
        {
            printf(" \033[91m[\033[0m%d\033[91m]\033[0m - \033[3m'%s'\033[0m; %s;",
                   i, m[i]->nome, m[i]->id);

            for (int j = 0; j < m[i]->artistas_usado; j++)
            {
                printf(" %s", m[i]->artistas[j]);
                if (j != m[i]->artistas_usado - 1)
                {
                    printf(",");
                }
            }
            printf(";\n\n");
        }
        free(nome_lwr);
    }
}

void Lista_uma_musica(Musica *m, int musica_usado, Artista *a, int artistas_usado)
{

    int num;

    printf("Digite o indice da musica que gostaria de listar seus atributos: \033[32m");
    scanf("%d", &num);

    printf("\n\033[0mBuscando indice '%d'...\n\n", num);

    if (num >= musica_usado || num < 0)
    {
        printf("\033[91mNao foi possivel buscar a musica de indice '%d' [indice invalido].\n", num);
        printf("Tente digitar um numero entre 0 e %d :)\033[0m\n\n\033[0m", musica_usado - 1);
    }

    else
    {
        printf("\033[93m==Resultado obtido==\033[0m\n\n");
        printf(" \033[91m[\033[0m%d\033[91m]\033[0m - '\033[3m%s\033[0m'; %s;", num, m[num]->nome, m[num]->id);

        for (int j = 0; j < m[num]->artistas_usado; j++)
        {
            printf(" %s", m[num]->artistas[j]);
            if (j != m[num]->artistas_usado - 1)
            {
                printf(",");
            }
        }
        printf(";\n\n");

        printf("\033[35m Criterios da musica:\033[0m\n\n");
        printf("    -nome: \033[90m%s\033[0m;\n", m[num]->nome);
        printf("    -id: \033[90m%s\033[0m;\n", m[num]->id);
        printf("    -duracao: \033[90m%d (ms)\033[0m;\n", m[num]->duracao_ms);
        printf("    -explicito: \033[90m%d\033[0m;\n", m[num]->explicito);
        printf("    -data de lancamento: \033[90m%s\033[0m;\n", m[num]->data);

        Lista_criterios(m[num]->criterios);

        printf("\033[35m Atributos do(s) artista(s):\033[0m\n\n");

        for (int i = 0; i < m[num]->artistas_usado; i++)
        {
            printf("\033[93m  > \033[0m\033[4martista %d\033[0m:\n\n", i + 1);
            Lista_artistas(m[num]->artistas[i], a, artistas_usado);
        }
    }
}

// ============ AUXILIARES ============

void lwrcase(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        int asc = str[i];

        if (asc >= 65 && asc <= 90)
        {
            asc += 32;
            str[i] = asc;
        }
        i++;
    }
}

char *Musica_nome_busca(int indice_musica, Musica *m)
{
    return m[indice_musica]->nome;
}

Musica *Musica_adicionada_atualiza(int indice, Musica *m)
{
    m[indice]->qtd_add_playlists++;
    return m;
}

void Musica_adicionada_playlist(Musica *m, int indice, int musicas_usado)
{

    printf("\n    \033[91m[\033[0m%d\033[91m]\033[0m - %s\n", indice, m[indice]->nome);
}
