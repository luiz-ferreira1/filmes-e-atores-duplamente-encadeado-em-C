#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"

int main() {
    ListaFilmes *filmes;            //cria o ponteiro para a lista de filmes
    inicializarListaFilmes(filmes); //inicializa a lista de filmes

    int opcao;                      //armazena a escolha do usuario
    char titulo[100], nome[100];    //entrada de strings
    Filme *f;                       //ponteiro auxiliar para os filmes

    do {
        menu();                     //mostra o menu
        scanf("%d", &opcao);        //lê a opção
        getchar();                  // consumir \n

        switch(opcao) {
            case 1:
                carregarArquivo(filmes, "filme.txt");   //carrega os filmes do arquivo
                printf("Arquivo carregado!\n");
                break;

            case 2:
                printf("Digite o título do filme: ");
                fgets(titulo, 100, stdin);              //lê o titulo do filme
                titulo[strcspn(titulo, "\n")] = '\0';   //remove o '\n'
                inserirFilme(filmes, titulo);           //insere o filme
                printf("Filme inserido!\n");
                break;

            case 3:
                printf("Digite o título do filme: ");
                fgets(titulo, 100, stdin);              //lê o titulo
                titulo[strcspn(titulo, "\n")] = '\0';
                f = buscarFilme(filmes, titulo);        //busca o filme
                if(f) {
                    printf("Digite o nome do ator: ");
                    fgets(nome, 100, stdin);            //lê o nome do ator
                    nome[strcspn(nome, "\n")] = '\0';
                    inserirAtor(f, nome);               //insere o ator no filme
                    printf("Ator inserido!\n");
                } else {
                    printf("Filme não encontrado!\n");
                }
                break;

            case 4:
                printf("Digite o título do filme: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                f = buscarFilme(filmes, titulo);                //busca o filme
                if(f) {
                    printf("Filme encontrado: %s\n", f->titulo);
                    imprimirAtores(f);                          //imprime os atores
                } else {
                    printf("Filme não encontrado!\n");
                }
                break;

            case 5:
                printf("Digite o título do filme: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                f = buscarFilme(filmes, titulo);            //busca o filme
                if(f) {
                    printf("Digite o nome do ator: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    Ator *a = buscarAtor(f, nome);          //busca o ator
                    if(a)
                        printf("Ator encontrado: %s\n", a->nome);
                    else
                        printf("Ator não encontrado!\n");
                } else {
                    printf("Filme não encontrado!\n");
                }
                break;

            case 6:
                printf("Digite o título do filme a remover: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                removerFilme(filmes, titulo);               //remove o filme se existia
                printf("Filme removido (se existia).\n");
                break;

            case 7:
                printf("Digite o título do filme: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                f = buscarFilme(filmes, titulo);            //busca o filme
                if(f) {
                    printf("Digite o nome do ator a remover: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    removerAtor(f, nome);                   //remove o ator, se existia
                    printf("Ator removido (se existia).\n");
                } else {
                    printf("Filme não encontrado!\n");
                }
                break;

            case 8:
                imprimirFilmes(filmes);                 //imprime os filmes e atores
                break;

            case 9:
                imprimirQtdAtoresPorFilme(filmes);      //imprime a quantidade de atores por filme
                break;
            
            case 10:
                imprimirQtdFilmes(filmes);              //imprime a quantidade de filmes 
                break;
                
            case 11:
                imprimirFilmesInvertido(filmes);        //imprime os filmes e atores em ordem invertida
                break;    
            
            case 12:
                printf("Digite o título do filme a favoritar: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                favoritarFilme(filmes, titulo);
                break;

            case 13:
                imprimirFavoritos(filmes);
                break;
            
            case 14:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 14);

    liberarListaFilmes(filmes);             //libera a lista de filmes
    return 0;
}

