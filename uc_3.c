#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

//Função de Busca na Arvore Binária
Produto* buscar(int x, Produto *aux){
    if(aux == NULL){
        return NULL; //vazia
    }else if (x == aux->codigo){
        return aux;
    }else if(x < aux->codigo){ //esq
        if(aux->esq == NULL){
            return aux;
        }else{
            return buscar(x, aux->esq);
        }
    }else{ //dir
        if(aux->dir == NULL){
            return aux;
        }else{
            return buscar(x, aux->dir);
        }
    }
}

// FUNÇÕES DO SISTEMA

// Função Adicionar produto - Função relacionada com a função Casdatrar produto, onde ele cadastra na arvoré o Nome e Preço do produto no sistema,
//o codigo gera os códigos dos produtos - Equipe 1
void adicionarProduto(char *nome, int quantidade_prod, float preco){
    Produto* aux = buscar(codigo, raizProduto);
    if(aux != NULL && aux->codigo == codigo){
        printf("insercao invalida!\n");
    }else{
        Produto* novo = malloc(sizeof(Produto));
        strcpy(novo->nome, nome);
        novo->preco = preco;
        novo->codigo = codigo;
        novo->quantidade_prod = quantidade_prod;
        novo->esq = NULL;
        novo->dir = NULL;
        if(aux == NULL){ //vazia
            raizProduto = novo;
        }else if(codigo < aux->codigo){//esq
            aux->esq = novo;
        }else{ //dir
            aux->dir = novo;
        }
        codigo++;
    }
}

Produto* remover_produto_quantidade(Produto *codigo, int quantidade_rem){ // Equipe 1
    Produto* aux = buscar(codigo, raizProduto);
    if(aux != NULL && aux->codigo == codigo){
        if (quantidade_rem < aux->quantidade_prod){
            aux->quantidade_prod = aux->quantidade_prod - quantidade_rem;}
            }}

Produto* remover_produto_estoque(Produto *raizProduto, int codigo) { // Equipe 1
    if(raizProduto == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raizProduto->codigo == codigo) {
            // remove nós folhas (nós sem filhos)
            if(raizProduto->esq == NULL && raizProduto->dir == NULL) {
                free(raizProduto);
                printf("Elemento folha removido: %d !\n", codigo);
                return NULL;
            }
            else{
                // remover nós que possuem 1 ou 2 filhos
            }
        } else {
            if(codigo < raizProduto->codigo)
                raizProduto->esq = remover_produto_estoque(raizProduto->esq, codigo);
            else
                raizProduto->dir = remover_produto_estoque(raizProduto->dir, codigo);
            return raizProduto;
        }
    }
}


void imprimir_em_ordem(Produto *aux){
    if(aux->esq != NULL){
        imprimir_em_ordem(aux->esq);
    }
    printf("\n%-5.3d  %-25s %-14d  %.2f", aux->codigo, aux->nome,aux->quantidade_prod, aux->preco);
    if(aux->dir != NULL){
        imprimir_em_ordem(aux->dir);
    }
}




// Função listar produtos - Função chamada no menu, faz a verificação se existem produtos cadastrados na arvore, se existir
//chama a função imprimir_em_ordem(), caso o contrario avisa ao cliente que não tem produtos cadastrados  - Equipe 1
void listarProdutos(){ 
	if(codigo > 0){
		Produto * aux;
        printf("\n%-5s  %-20s %-20s %s", "Cod","Produto","Quantidade","Preco");
        printf("\n--------------------------------------------------------");
        imprimir_em_ordem(raizProduto);
	}else{
		printf("Nao temos produtos disponiveis no momento :(\n");
	}
    printf("\n--------------------------------------------------------\n");
}





int main(){

    adicionarProduto("Leite",5, 10);
    adicionarProduto("Queijo",2,5);
    adicionarProduto("Pao",1,0.25);
    adicionarProduto("Presunto",3,5);
    remover_produto_estoque(raizProduto,2);
    remover_produto_quantidade(1, 3);
    listarProdutos();
    
}