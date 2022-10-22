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

// Funcionario
funcionario(){
    int opcao;

        printf("O que deseja fazer?\n");
        printf("[1]Adcionar produto ao sistema\n[2]Remover produto do sistema\n[3]Voltar ao menu de Login:\n");
        scanf("%d", &opcao);

        while (opcao < 1 || opcao > 3) {
        printf("!!OPCAO INVALIDA!!\n\n");
        printf("O que deseja fazer?\n");
        printf("[1]Adcionar produto ao sistema\n[2]Remover produto do sistema\n[3]Voltar ao menu de Login:\n");
        scanf("%d",&opcao);}

        switch(opcao){
        case 1: 
            adicionar_Produto();
            funcionario();
            break;

        case 2: 
            remover_Produto();
            funcionario();
            break;          

        case 3:
            printf("\nVoltando ao menu de login...\n\n");
            login();
            break;}
        }


// Funcionario ADM
funcionario_adm(){
    int opcao;
        printf("O que deseja fazer?\n");
        printf("[1]Adcionar produto ao sistema\n[2]Remover produto do sistema\n[3]Adicionar Conta ao Sistema:\n[4]Remover Conta do Sistema:\n[5]Listar Contas Cadastradas:\n[6]Voltar ao menu de Login:\n");
        scanf("%d",&opcao);

        while (opcao < 1 || opcao > 6) {
        printf("!!OPCAO INVALIDA!!\n\n");
        printf("O que deseja fazer?\n");
        printf("[1]Adcionar produto ao sistema\n[2]Remover produto do sistema\n[3]Adicionar Conta ao Sistema:\n[4]Remover Conta do Sistema:\n[5]Listar Contas Cadastradas:\n[6]Voltar ao menu de Login:\n");
        scanf("%d",&opcao);}

        switch(opcao){
        case 1: 
            adicionar_Produto();
            funcionario_adm();
            break;

        case 2: 
            remover_Produto();
            funcionario_adm();
            break;

        case 3:           
            adicionar_Funcionario();
            funcionario_adm();
            break;

        case 4:           
            remover_Funcionario();
            funcionario_adm();
            break;

        case 5:
            listar_Contas();
            funcionario_adm();
            break;

        case 6:
            printf("\nVoltando ao menu de login...\n\n");
            login();
            break;}
        }


//Cliente
cliente(int id){
    comprar(id);
    }

//Login
void login(){ 
    int id;
    char p_nome[30];
    char s_nome[30];
    int senha_cad;
    int senha;
    int opcao = 1;

        printf("-----------------------------------------------------\n");
        printf("--------------------MERCADO BIG BOM------------------\n");
        printf("-----------------------------------------------------\n");
        printf("                    OPCOES DE LOGIN\n\n");
        printf("     [1]Criar uma Conta     |     [2]Fazer Login\n");
        printf("                        [3]SAIR\n\n");
        printf("O que deseja fazer?: ");
        scanf("%d", &opcao);
        printf("------------------------------------------------\n\n");

        while (opcao < 1 || opcao > 3) {
            printf("               !!OPCAO INVALIDA!!\n\n");
            printf(" [1]Criar uma Conta     |    [2]Fazer Login\n");
            printf("                    [3]SAIR\n\n");
            printf("O que deseja fazer?: ");
            scanf("%d",&opcao);}


        switch(opcao){

            case 1:
                printf("-----------------------------------------\n");
                printf("================ CADASTRO ===============\n");
                printf("-----------------------------------------\n");
                printf("Informe seu primeiro nome: ");
                fflush(stdin);
                scanf("%s", p_nome);

                printf("Informe seu segundo nome: ");
                fflush(stdin);
                scanf("%s", s_nome);
                
                printf("\nInforme sua senha de 8 digitos numericos: ");
                fflush(stdin);
                scanf("%d", &senha_cad);

                cadastrar_Conta(p_nome, s_nome, senha_cad, id_cont, 3);
                login();
                break;

            case 2:
                printf("-----------------------------------------\n");
                printf("================= LOGIN =================\n");
                printf("-----------------------------------------\n");
                printf("Informe o seu ID: ");
                fflush(stdin);
                scanf("%d", &id);

                Conta* aux = buscar_Conta(id, raizContas);
                while(aux->id == NULL){
                    printf("Informe um ID valido: ");
                    fflush(stdin);
                    scanf("%d", &id);
                    Conta* aux = buscar_Conta(id, raizContas);
                }
                
                printf("\nInforme sua senha: ");
                fflush(stdin);
                scanf("%d", &senha);

                while(senha != aux->senha){
                    printf("Informe sua senha: ");
                    fflush(stdin);
                    scanf("%d", &senha);
                }

                if (aux->cont_type == 1){
                    funcionario_adm();
                }
                else if (aux->cont_type == 2){
                    funcionario();
                }
                else if (aux->cont_type == 3){
                    cliente(aux->id);
                }
                break;

            case 3:
                printf("Ate logo!\n");
                break;
            default:
                printf("Opcao invalida");
                break;
            }
        }

