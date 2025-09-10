#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"

// Inicializa a lista de filmes vazia
void inicializarListaFilmes(ListaFilmes* lf){
    lf->inicio = NULL;   
    lf->fim = NULL;
    lf->qtd = 0;
}

//Inicializa a lista de atores vazia
void inicializarListaAtores(ListaAtores *la){
    la->inicio = NULL;
    la->fim = NULL;
    la->qtd = 0;
}

//Cria um novo filme
Filme* criarFilme(char *titulo){
    Filme *f;
    f = (Filme*)malloc(sizeof(Filme));  //alocação de memoria
    strcpy(f->titulo, titulo);          //copia o titulo para o filme
    f->num_atores = 0;                  //numero de atores = 0 inicialmente
    
    f->atores = (ListaAtores*)malloc(sizeof(ListaAtores)); //aloca memoria para a lista de atores
    inicializarListaAtores(f->atores);                     
    
    f->prox = NULL;   //ponteiros começam nulos
    f->ant = NULL;
    return f;
}

//Cria um novo ator
Ator* criarAtor(char *nome){
    Ator *a;
    a = (Ator*)malloc(sizeof(Ator));  //aloca memoria para ator
    strcpy(a->nome, nome);            //copia o nome para ator
    
    a->prox = NULL;  //ponteiros começam nulos
    a->ant = NULL;
    return a;
}

//inserção de filme no fim da Lista
void inserirFilme(ListaFilmes *lf, char *titulo){
    Filme *novo;
    novo = criarFilme(titulo);  //cria um novo filme
    if(lf->inicio == NULL){     //confere se a lista esta vazia
        lf->inicio = novo;      //o inicio da lista recebe o novo filme criado
        lf->fim = novo;         //o fim da lista tambem recebe o novo filme
    }else{                      //caso a lista não esteja vazia...
        lf->fim->prox = novo;   //o ultimo filme da lista passsa a apontar para o novo
        novo->ant = lf->fim;    //o ponteiro anterior do novo aponta para o fim da lista
        lf->fim = novo;         //o fim da lista passa a ser o novo filme
    }
    lf->qtd++;                  //acresecenta um filme à lista
}

//inserção de ator no fim da lista
void inserirAtor(Filme *f, char *nome){
    Ator *novo;
    novo = criarAtor(nome);         //cria um novo ator
    if(f->atores->inicio == NULL){  //confere se a lista de atores esta vazia
        f->atores->inicio = novo;   //o inicio da lista recebe o novo ator
        f->atores->fim = novo;      //o fim da lista recebe o novo ator
    }else{                          //caso a lista não esteja vazia inserimos no fim
        f->atores->fim->prox = novo;  //o ultimo ator da fila passa a apontar para o novo
        novo->ant = f->atores->fim;  //o ponteiro anterior de novo aponta para o fim da lista
        f->atores->fim = novo;      //o fim da lista passa a ser o novo ator
    }
    f->num_atores++;        //acrescenta o numero de atores no filme
    f->atores->qtd++;       //acrescenta o numero de atores na lista de atores
}

//Busca um filme na lista
Filme* buscarFilme(ListaFilmes *lf, char *titulo){
    Filme *aux;
    aux = lf->inicio;                               //auxiliar recebe o primeiro filme da lista
    while(aux) {                                    //enquanto aux != NULL
        if(strcmp(aux->titulo, titulo) == 0){       //compara se o titulo do filme é o mesmo que o fornecido
            return aux;                             //se for, retorna o filme
        }
        aux = aux->prox;                            //caso não seja, aux recebe o proximo filme
    }
    return NULL;                                    //retorna NULL se não estiver na lista
}

//Busca um ator na lista de atores
Ator* buscarAtor(Filme *f, char *nome){
    Ator *aux;
    aux = f->atores->inicio;                //aux recebe o primeiro ator da lista de atores do filme passado
    while(aux){                             //enquanto aux != NULL
        if(strcmp(aux->nome, nome) == 0){   //compara se o nome do ator é o mesmo que foi passado
            return aux;                     //se for, retorna o ator
        }else{
            aux = aux->prox;                //caso não seja, o aux recebe o proximo ator da lista
        }
    }
    return NULL;                            //retorna NULL se não estiver na lista
}

//Remove um filme da lista de filmes
void removerFilme(ListaFilmes *lf, char *titulo){
    Filme *f;
    f = buscarFilme(lf, titulo);    //busca o filme na lista
    if(!f){
        return;                     //se o filme não existir, retorna
    }
    
    liberarListaAtores(f->atores);  //caso exista, libera a lista de atores daquele filme
    
    if(f->ant){                     //se não for o primeiro filme da lista...
        f->ant->prox = f->prox;     //o ponteiro proximo do filme anterior aponta para o proximo filme
    }else{
        lf->inicio = f->prox;       //atualiza o ponteiro da cabeça para o proximo nó
    }
    
    if(f->prox){                    //se não for o ultimo filme da lista...
        f->prox->ant = f->ant;      //o ponteiro anterior do proximo filme aponta para o filme anterior
    }else{
        lf->fim = f->ant;           //atualiza o ponteiro da cauda para o nó anterior
    }
    
    free(f);                        //libera o filme
    lf->qtd--;                      //diminui a quantidade de filmes na lista 
}

//Remove um ator do filme
void removerAtor(Filme *f, char *nome){
    Ator *a;
    a = buscarAtor(f, nome);        //busca o ator
    
    if(!a){                         //se o ator não estiver na lista de atores, retorna
        return;
    }
    
    if(a->ant){                     //se o ator não for o primeiro da lista
        a->ant->prox = a->prox;     //o ponteiro proximo do anterior aponta para o proximo ator
    }else{
        f->atores->inicio = a->prox; //se o ator é o primeiro, atualiza a cabeça da lista
    }
    
    if(a->prox){                    //se o ator não for o ultimo da lista
        a->prox->ant = a->ant;      //o ponteiro anterior do proximo ator aponta para o ator anterior
    }else{
        f->atores->fim = a->ant;    //se o ator é o ultimo, atualiza a cauda da lista 
    }
    free(a);                        //libera a memoria
    f->num_atores--;                //diminui o numero de atores do filme
    f->atores->qtd--;               //diminui o numero de atores da lista de atores
}

//Imprime os atores do inicio para o fim
void imprimirAtores(Filme *f){
    Ator *aux;
    aux = f->atores->inicio;
    while(aux){
        printf("   - %s\n", aux->nome);
        aux = aux->prox;                    //aux percorre a lista do inicio ao fim, imprimindo o nome dos atores
    }
}

//Imprime os filmes do inicio para o fim
void imprimirFilmes(ListaFilmes *lf){
    Filme *aux;
    aux = lf->inicio;
    while(aux){
        printf("Filme : %s (%d atores) \n", aux->titulo, aux->num_atores);
        imprimirAtores(aux);
        printf("-----------------------------\n");
        aux = aux->prox;                            //aux percorre a lista de filmes do inicio ao fim
    }
}

// Imprime os atores na ordem inversa, percorrendo a lista do final para o inicio
void imprimirAtoresInvertido(Filme *f) {
    Ator *aux = f->atores->fim;
    if (aux == NULL) {
        printf("   Nenhum ator cadastrado.\n");
        return;
    }

    while (aux) {
        printf("   - %s\n", aux->nome);
        aux = aux->ant;                     //aux percorre a lista de atores do fim para o inicio (invertido)
    }
}

//Imprime os filmes na ordem inversa, percorrendo a lista do final para o inicio
void imprimirFilmesInvertido(ListaFilmes *lf) {
    Filme *aux = lf->fim;
    if (aux == NULL) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    while (aux) {
        printf("Filme: %s (%d atores)\n", aux->titulo, aux->num_atores);
        imprimirAtoresInvertido(aux);
        printf("-----------------------------\n");
        aux = aux->ant;                             //aux percorre a lista de filmes do fim para o inicio (invertido)
    }
}

//Imprime a quantidade de atores por filme
void imprimirQtdAtoresPorFilme(ListaFilmes *lf) {
    Filme *aux = lf->inicio;
    if (aux == NULL) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    while (aux) {
        printf("O filme \"%s\" tem %d atores cadastrados.\n",aux->titulo, aux->num_atores);
        aux = aux->prox;                    //aux percorre a lista de filmes
    }
}

//Imprime a quantidade de filmes
void imprimirQtdFilmes(ListaFilmes *lf){
    printf("Quantidade de filmes cadastrados: %d\n", lf->qtd);
}

//Libera a lista de atores
void liberarListaAtores(ListaAtores *la){
    Ator *aux;
    aux = la->inicio;
    while(aux){
        Ator *temp;         //aux percorre a lista, usando a variavel temp para guardar e liberar a memoria do ator percorrido
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    la->inicio = NULL;
    la->fim = NULL;
    la->qtd = 0;
}

//Libera a lista de filmes
void liberarListaFilmes(ListaFilmes *lf){
    Filme *aux;
    aux = lf->inicio;
    
    while(aux){
        Filme *temp;
        temp = aux;
        aux = aux->prox;
        liberarListaAtores(temp->atores);
        free(temp);
    }
    lf->inicio = NULL;
    lf->fim = NULL;
    lf->qtd = 0;
}

// Marca um filme como favorito
void favoritarFilme(ListaFilmes *lf, char *titulo) {
    Filme *f = buscarFilme(lf, titulo);   // Busca o filme pelo título
    if (!f) {
        printf("Filme não encontrado!\n");
        return;
    }
    f->favorito = 1;                      // Marca como favorito
    printf("O filme \"%s\" foi adicionado aos favoritos!\n", f->titulo);
}

// Imprime apenas os filmes favoritos
void imprimirFavoritos(ListaFilmes *lf) {
    Filme *aux = lf->inicio;
    int achou = 0;                        // Flag para verificar se há favoritos
    while (aux) {
        if (aux->favorito) {              // Se for favorito
            printf("** %s (%d atores)\n", aux->titulo, aux->num_atores);
            achou = 1;
        }
        aux = aux->prox;
    }
    if (!achou) {
        printf("Nenhum filme foi marcado como favorito ainda.\n");
    }
}


//Carrega o arquivo
void carregarArquivo(ListaFilmes *lf, char *nomeArquivo){
    FILE *arq = fopen(nomeArquivo, "r");        // Abre o arquivo para leitura
    if(!arq) {                                  // Verifica erro na abertura
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char linha[MAX];                            
    while(fgets(linha, MAX, arq)) {             // Lê uma linha (título do filme)
        linha[strcspn(linha, "\n")] = 0;        // Remove o '\n' do final
        char titulo[MAX];
        strcpy(titulo, linha);                  // Copia para a variável título

        fgets(linha, MAX, arq);                 // Lê a próxima linha (qtd de atores)
        int n = atoi(linha);                    // Converte para inteiro

        inserirFilme(lf, titulo);               // Insere o novo filme
        Filme *f = lf->fim;                     // Aponta para o último filme inserido

        for(int i=0; i<n; i++) {                // Lê cada ator
            fgets(linha, MAX, arq);
            linha[strcspn(linha, "\n")] = 0;    // Remove o '\n'
            inserirAtor(f, linha);              // Insere o ator no filme
        }
    }
    fclose(arq);                                // Fecha o arquivo
}

void menu() {
    printf("\n===== MENU =====\n");
    printf("1 - Carregar filmes do arquivo\n");
    printf("2 - Inserir filme\n");
    printf("3 - Inserir ator em filme\n");
    printf("4 - Buscar filme\n");
    printf("5 - Buscar ator em um filme\n");
    printf("6 - Remover filme\n");
    printf("7 - Remover ator de um filme\n");
    printf("8 - Imprimir todos os filmes\n");
    printf("9 - Imprimir quantidade de atores por filme\n");
    printf("10 - Imprimir a quantidade de filmes na lista\n");
    printf("11 - Imprimir filmes e atores de tras para frente\n");
    printf("12 - Favoritar um filme\n");
    printf("13 - Listar filmes favoritos\n");
    printf("14 - Sair\n");
    printf("Escolha: ");
}









