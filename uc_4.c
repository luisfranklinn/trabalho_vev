#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estrutura de Dados
typedef struct contas{
    char p_nome[30];
    char s_nome[30];
    int senha;
    int id;
    int cont_type;
    struct contas *dir;
    struct contas *esq;
}Conta;

Conta *raizContas = NULL;
int id_cont = 1;


typedef struct prod{
    char nome[30];
    int quantidade_prod;
    float preco;
    int codigo;
    struct prod *dir;
    struct prod *esq;
}Produto;

Produto *raizProduto = NULL;
int codigo = 1;

//Função de Busca nas Arvores Binárias
Produto* buscar_Prod(int x, Produto *aux){
    if(aux == NULL){
        return NULL; //vazia
    }else if (x == aux->codigo){
        return aux;
    }else if(x < aux->codigo){ //esq
        if(aux->esq == NULL){
            return aux;
        }else{
            return buscar_Prod(x, aux->esq);
        }
    }else{ //dir
        if(aux->dir == NULL){
            return aux;
        }else{
            return buscar_Prod(x, aux->dir);
        }
    }
}

Conta* buscar_Conta(int x, Conta *aux){
    if(aux == NULL){
        return NULL; //vazia
    }else if (x == aux->id){
        return aux;
    }else if(x < aux->id){ //esq
        if(aux->esq == NULL){
            return aux;
        }else{
            return buscar_Conta(x, aux->esq);
        }
    }else{ //dir
        if(aux->dir == NULL){
            return aux;
        }else{
            return buscar_Conta(x, aux->dir);
        }
    }
}
