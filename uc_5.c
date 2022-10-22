//Emitir Notal Fiscal

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


typedef struct carrinho{
    Produto produto;
    int quantidade;
    struct carrinho *prox;
}Carrinho;

Carrinho * topoCarrinho = NULL; 
int contador_carrinho = 0;


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



// Gerar Nota
void gerar_Nota(int id,float troco, float pago){ 
    Conta* found = buscar_Conta(id, raizContas);
    FILE *arquivo;
    Carrinho * aux;
    float valorProd = 0.0;
    float valorTotal = 0.0;
    arquivo = fopen("Nota Fiscal.txt","w");
    fprintf(arquivo,"========================================================\n");
    fprintf(arquivo,"                       NOTA FISCAL\n");
    fprintf(arquivo,"========================================================\n");
    fprintf(arquivo,"Cliente: %s %s || ID: %d\n",found->p_nome,found->s_nome,found->id);
    fprintf(arquivo,"========================================================\n");
    fprintf(arquivo, "%-20s  %-13s  %-10s %-10s\n","Produto","Preco", "Qtd","Valor");
    fprintf(arquivo,"--------------------------------------------------------\n");
    for (aux = topoCarrinho; aux != NULL; aux = aux->prox){
        valorProd = aux->produto.preco * aux->quantidade;
        valorTotal += valorProd;
        fprintf(arquivo, "%-20s  %-13.2f  %-10d %-10.2f\n", aux->produto.nome, aux->produto.preco, aux->quantidade, valorProd);
    }
    fprintf(arquivo,"--------------------------------------------------------\n");
    fprintf(arquivo,"Valor total da compra: R$%.2f\n", valorTotal);
    fprintf(arquivo,"Valor pago: R$%.2f\n", pago);
    fprintf(arquivo,"Valor do troco: R$%.2f\n", troco);
    fclose(arquivo);
}
