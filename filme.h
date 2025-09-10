#ifndef _FILME_H
#define _FILME_H

#define MAX 100

typedef struct ator{
    char nome[MAX];  //nome do ator
    struct ator *prox; //proximo no
    struct ator *ant;  //no anterior
} Ator;

typedef struct lista{
    Ator *inicio; //inicio da lista
    Ator *fim;  //fim da lista
    int qtd;  //quantidade de atores
} ListaAtores;

typedef struct filme{
    char titulo[MAX];  //titulo do filme
    int num_atores;   //numero de atores no filme
    ListaAtores *atores; //ponteiro para a lista de atores
    int favorito;        // 0 = não favorito, 1 = favorito
    struct filme *prox;  //proximo no
    struct filme *ant;  //no anterior
} Filme;

typedef struct {
    Filme *inicio;  //inicio da Lista
    Filme *fim;    //fim da lista
    int qtd;      //quantidade de filmes
} ListaFilmes;

//---declaração de funções---

void inicializarListaFilmes(ListaFilmes *lf);
void inicializarListaAtores(ListaAtores *la);

Filme* criarFilme(char *titulo);
Ator* criarAtor(char *nome);

void inserirFilme(ListaFilmes *lf, char *titulo);
void inserirAtor(Filme *f, char *nome);

Filme* buscarFilme(ListaFilmes *lf, char *titulo);
Ator* buscarAtor(Filme *f, char *nome);

void removerFilme(ListaFilmes *lf, char *titulo);
void removerAtor(Filme *f, char *nome);

void imprimirFilmes(ListaFilmes *lf);
void imprimirAtores(Filme *f);

void imprimirAtoresInvertido(Filme *f);
void imprimirFilmesInvertido(ListaFilmes *lf);

void imprimirQtdAtoresPorFilme(ListaFilmes *lf);
void imprimirQtdFilmes(ListaFilmes *lf);

void liberarListaFilmes(ListaFilmes *lf);
void liberarListaAtores(ListaAtores *la);

void favoritarFilme(ListaFilmes *lf, char *titulo);
void imprimirFavoritos(ListaFilmes *lf);

void carregarArquivo(ListaFilmes *lf, char *nomeArquivo);
void menu();



#endif