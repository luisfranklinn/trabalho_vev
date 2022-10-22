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


// Manter Contas
void cadastrar_Conta(char *p_nome, char *s_nome, int senha,int id, int cont_type){
    Conta* aux = buscar_Conta(id, raizContas);
    if(aux != NULL && aux->id == id){
        printf("insercao invalida!\n");
    }else{
        Conta* novo = malloc(sizeof(Conta));
        strcpy(novo->p_nome, p_nome);
        strcpy(novo->s_nome, s_nome);
        
        novo->senha = senha;
        novo->id = id;
        novo->cont_type = cont_type;
        novo->esq = NULL;
        novo->dir = NULL;
        if(aux == NULL){ //vazia
            raizContas = novo;
        }else if(id < aux->id){//esq
            aux->esq = novo;
        }else{ //dir
            aux->dir = novo;
        }
        id_cont++;
    }
}

Conta* remover_Conta(Conta *raizContas, int id) {
    if(raizContas == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if(raizContas->id == id) {
            if(raizContas->esq == NULL && raizContas->dir == NULL) {
                Conta *found = buscar_Conta(id,raizContas);
                printf("%s %s Removido do Sistema!\n", found->p_nome, found->s_nome);
                free(raizContas);
                return NULL;
            }
            else{
            }
        } else {
            if(id < raizContas->id)
                raizContas->esq = remover_Conta(raizContas->esq, id);
            else
                raizContas->dir = remover_Conta(raizContas->dir, id);
            return raizContas;
        }
    }
}

void imprimir_Contas(Conta *aux){
    if(aux->esq != NULL){
        imprimir_Contas(aux->esq);
    }
    printf("\n%-5.3d  %-8s %-16s  %d", aux->id, aux->p_nome,aux->s_nome, aux->cont_type);
    if(aux->dir != NULL){
        imprimir_Contas(aux->dir);
    }
}

void listar_Contas(){ 
    printf("===============================================\n");
    printf("              Contas Cadastradas               \n");
    printf("===============================================\n");
	if(id_cont > 0){
		Conta * aux;
        printf("\n%-5s  %-7s %-12s %s", "ID","Nome","Sobrenome","Tipo da Conta");
        printf("\n--------------------------------------------------------");
        imprimir_Contas(raizContas);
	}else{
		printf("Nao existem contas no Banco de Dados(\n");
	}
    printf("\n--------------------------------------------------------\n");
}

void adicionar_Funcionario(){ 
    char p_nome[30] = "\0";
    char s_nome[30] = "\0";
    int senha_func;
    int cont_type;
    printf("==================================\n");   
    printf("      Cadastro de Funcionario\n");
    printf("==================================\n");

    printf("Informe o primeiro nome: ");
    fflush(stdin);
    scanf("%s", p_nome);

    printf("Informe o segundo nome: ");
    fflush(stdin);
    scanf("%s", s_nome);
    
    printf("\nInforme a senha de 8 digitos numericos: ");
    fflush(stdin);
    scanf("%d", &senha_func);

    printf("\nInforme o tipo do Funcionario!");
    printf("\n1 para ADM | 2 para Comum: ");

    fflush(stdin);
    scanf("%d", &cont_type);

    cadastrar_Conta(p_nome,s_nome,senha_func,id_cont,cont_type);
    }

void remover_Funcionario(){
    int id;
    printf("==================================\n");   
    printf("      Remocao de Funcionario\n");
    printf("==================================\n");

    listar_Contas();

    printf("Informe o codigo da conta que deseja remover: ");
    fflush(stdin);
    scanf("%d", &id);

    Conta* aux = buscar_Conta(id, raizContas);
    while (aux->id == NULL){ 
        printf("Informe um codigo válido: ");
        fflush(stdin);
        scanf("%d", &id);
        Conta* aux = buscar_Conta(id, raizContas);
    }
    remover_Conta(raizContas,id);
}

