// Manter Estoque

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

// Manter Produtos
void cadastrar_Produto(char *nome, int codigo,int quantidade_prod, float preco){
    Produto* aux = buscar_Prod(codigo, raizProduto);
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
    }
}

void adicionar_Produto(){ 
    char nome[30] = "\0";
    int codigo = 0;
    int quantidade_prod = 0;
    float preco = 0.0;
    printf("===============================\n");   
    printf("      Cadastro de Produto\n");
    printf("===============================\n");

    printf("Informe o nome do produto: ");
    fflush(stdin);
    scanf("%s", nome);

    printf("Informe o codigo do produto: ");
    fflush(stdin);
    scanf("%d", &codigo);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &quantidade_prod);
    printf("-------------------------------\n");

    printf("Informe o preco do produto: ");
    scanf("%f", &preco);
    printf("-------------------------------\n");

    printf("\nAdcionado ao sistema! -> Produto: %s | Cod: %d | Qtd: %d | Preco: R$%.2f \n", nome,codigo, quantidade_prod, preco);
    printf("----------------------------------------------------------\n");
    cadastrar_Produto(nome, codigo, quantidade_prod, preco);}

Produto* remover_produto_quantidade(Produto *codigo, int quantidade_rem){ // Equipe 1
    Produto* aux = buscar_Prod(codigo, raizProduto);
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

void remover_Produto(){ 
    int codigo;
    printf("===============================\n");   
    printf("      Remocao de Produto\n");
    printf("===============================\n");

    listar_Produtos();

    printf("Informe o codigo do produto que deseja remover: ");
    fflush(stdin);
    scanf("%d", &codigo);

    Produto* aux = buscar_Prod(codigo, raizProduto);
    while (aux->codigo == NULL){ 
        printf("Informe um codigo válido: ");
        fflush(stdin);
        scanf("%d", &codigo);
        Produto* aux = buscar_Prod(codigo, raizProduto);
    }
    remover_produto_estoque(raizProduto,codigo);
}

void imprimir_Produtos(Produto *aux){
    if(aux->esq != NULL){
        imprimir_Produtos(aux->esq);
    }
    printf("\n%-5.3d  %-25s %-14d  %.2f", aux->codigo, aux->nome,aux->quantidade_prod, aux->preco);
    if(aux->dir != NULL){
        imprimir_Produtos(aux->dir);
    }
}

void listar_Produtos(){ 
    printf("===============================================\n");
    printf("            Produtos disponiveis               \n");
    printf("===============================================\n");
	if(codigo > 0){
		Produto * aux;
        printf("\n%-5s  %-20s %-20s %s", "Cod","Produto","Quantidade","Preco");
        printf("\n--------------------------------------------------------");
        imprimir_Produtos(raizProduto);
	}else{
		printf("Nao temos produtos disponiveis no momento :(\n");
	}
    printf("\n--------------------------------------------------------\n");
}
