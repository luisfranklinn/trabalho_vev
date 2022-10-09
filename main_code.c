#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Grupo SEV
//Curso: Engenharia de Software
//Luis Antonio Viana Franklin - 5141467
//Ruan Pablo de Sousa Estacio - 509806 




//Estrutura de Dados - RUAN
typedef struct prod{
    char nome[30];
    float preco;
    int codigo;
    struct prod *dir;
    struct prod *esq;
}Produto;


typedef struct carrinho{
    Produto produto;
    int quantidade;
    struct carrinho *prox;
}Carrinho;

Produto *raizProduto = NULL;
int contador_produto = 0;

Carrinho * topoCarrinho = NULL; 
int contador_carrinho = 0;

//Função de Busca na Arvore Binária - RUAN
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
//o contador_produto gera os códigos dos produtos - RUAN
void adicionarProduto(char *nome, float preco, int codigo){
    Produto* aux = buscar(codigo, raizProduto);
    if(aux != NULL && aux->codigo == codigo){
        //codigo já existe na árvore!
        printf("insercao invalida!\n");
    }else{
        Produto* novo = malloc(sizeof(Produto));
        strcpy(novo->nome, nome);
        novo->preco = preco;
        novo->codigo = codigo;
        novo->esq = NULL;
        novo->dir = NULL;
        if(aux == NULL){ //vazia
            raizProduto = novo;
        }else if(codigo < aux->codigo){//esq
            aux->esq = novo;
        }else{ //dir
            aux->dir = novo;
        }
        contador_produto++;
    }
}


// Função Cadastrar produto - Essa função pede os dados do produto ao usúario(Preço e Nome) e no final
// passa os dados como parametros para a função adcionar - RUAN
void cadastrarProduto(){ 
    char produto[30] = "\0";
    float preco = 0.0;
    printf("===============================\n");   
    printf("      Cadastro de Produto\n");
    printf("===============================\n");

    printf("Informe o nome do produto: ");
    fflush(stdin);
    scanf("%s", produto);

    printf("Informe o preco do produto: ");
    scanf("%f", &preco);
    printf("-------------------------------\n");


    printf("\nAdcionado ao sistema! -> Produto: %s | Preco: R$%.2f \n", produto, preco);
    printf("----------------------------------------------------------\n");
    adicionarProduto(produto, preco, contador_produto);}


// Função Imprimir - Associada a função de listar Produtos, ela faz a impressão da arvore em in_order - RUAN
void imprimir_em_ordem(Produto *aux){
    if(aux->esq != NULL){
        imprimir_em_ordem(aux->esq);
    }
    printf("\n%-5.3d  %-30s  %.2f", aux->codigo, aux->nome, aux->preco);
    if(aux->dir != NULL){
        imprimir_em_ordem(aux->dir);
    }
}


// Função listar produtos - Função chamada no menu, faz a verificação se existem produtos cadastrados na arvore, se existir
//chama a função imprimir_em_ordem(), caso o contrario avisa ao cliente que não tem produtos cadastrados  - RUAN
void listarProdutos(){ 
	if(contador_produto > 0){
		Produto * aux;
        printf("\n%-5s  %-30s  %s", "Cod","Produto","Preco");
        printf("\n-----------------------------------------------");
        imprimir_em_ordem(raizProduto);
	}else{
		printf("Nao temos produtos disponiveis no momento :(\n");
	}
    printf("\n-----------------------------------------------\n");
}


// Função adicionar ao carrinho, assim que o usuario realiza a escolha do seu produto, essa função insere o produto a partir de
//uma verificaçao do código, assim, a função adciona o produto dentro de uma pilha. - LUIS
void adicionarCarrinho(Produto prod, int qtd){
    Carrinho *carrin = (Carrinho*) malloc (sizeof (Carrinho));
    Carrinho * aux;
    if(topoCarrinho == NULL){
        carrin->produto = prod;
        carrin->quantidade = qtd;
        carrin->prox = topoCarrinho;
        topoCarrinho = carrin;
        contador_carrinho++;
    }else{
        for(aux = topoCarrinho; aux != NULL; aux = aux->prox){
            if(prod.codigo == aux->produto.codigo){
                aux->quantidade += qtd;
                break;
            }else if(aux->prox == NULL){
                carrin->produto = prod;
                carrin->quantidade = qtd;
                carrin->prox = topoCarrinho;
                topoCarrinho = carrin;
                contador_carrinho++;
                break;
            }
        }
    }
}


//Função Comprar - Associada a função adicionar carrinho, ela é resposavel por pegar o código e a quantidade do produto que o cliente
//deseja comprar, verifica se o produto existe, se existir manda para função adicionarCarrinho(), se não informa que o produto não existe  - LUIS
void comprar(){ 
    int opcao;
    if (contador_produto > 0){
        int codigin = 0;
        int qtd = 1;
		printf("===============================================\n");
		printf("            Produtos disponiveis\n");
		printf("===============================================\n");
        listarProdutos();
        do{
            printf("Selecione pelo codigo qual produto deseja adicionar no carrinho: ");
            scanf("%d", &codigin);
        }while(codigin < 0 || codigin > contador_produto-1);
        Produto * aux = buscar(codigin, raizProduto);
        printf("Qual a quantidade: ");
        scanf("%d", &qtd);

        adicionarCarrinho(*aux, qtd);

        printf("\nAdcionado ao carrinho! -> Produto: %s | Quantidade: %d \n", aux->nome, qtd);
        printf("----------------------------------------------------------\n");
        printf("Deseja continuar comprando?\n[1] Sim\n[2] Nao (Volta ao Menu do Cliente)\n");
        scanf("%d", &opcao);

        while(opcao < 1 || opcao > 2){
            printf("!!OPCAO INVALIDA!!\n");
            printf("Deseja continuar comprando?\n[1] Sim\n[2] Nao\n");
            scanf("%d", &opcao);}

        switch(opcao){
            case 1:
                comprar();
                break;
            case 2:
                fecharPedido();
                break;
        }
    }else{
        printf("Ainda nao temos produto cadastrado.\n");
        menu();
    }
}


//Função limpar Carrinho - Zera o carrinho assim que o cliente finaliza a compra - LUIS
int limparCarrinho(){
    Carrinho * aux = topoCarrinho;
    for(aux = topoCarrinho; aux != NULL; aux = aux->prox){
        topoCarrinho = topoCarrinho->prox;
        Carrinho * lixo = aux;
        free(lixo);
        contador_carrinho--;
    }
}


//Função Remover do Carrinho - Remove itens que o cliente não deseja mais comprar - LUIS
void removerCarrinho(){
    if ( contador_carrinho > 0 ){
        int codigin = 0;
        int qtd = 1;
        float valorProd = 0.0;
        float valorTotal = 0.0;
        int resul;
        int opcao_rem;

        Carrinho *aux;
        printf("===============================================================\n");
		printf("                      Remover do carrinho\n");
		printf("===============================================================\n");

        printf("%-5s  %-20s  %-13s  %-10s %-10s\n","Cod","Produto","Preco", "Qtd","Valor");//Listar
        printf("---------------------------------------------------------------\n");
        for (aux = topoCarrinho; aux != NULL; aux = aux->prox){
            valorProd = aux->produto.preco * aux->quantidade;
            valorTotal += valorProd;
            printf("%-5d  %-20s  %-13.2f  %-10d %-10.2f\n", aux->produto.codigo, aux->produto.nome, aux->produto.preco, aux->quantidade, valorProd);
        }
        Carrinho * prod; // verificar se o produto esta no carrinho
        printf("Selecione o codigo do produto que deseja remover: ");
        scanf("%d", &codigin);
        do{
            resul = 0;
            for(prod = topoCarrinho; prod != NULL; prod = prod->prox){
                if(codigin == prod->produto.codigo){
                    resul = 1; //encontrou
                    break;
                }
            }
            if (resul == 0){
                printf("\nErro! Codigo inexistente!\n");
                printf("Selecione o codigo do produto que deseja remover: ");
                scanf("%d", &codigin);
            }
        }while(resul == 0);

        printf("Qual a quantidade do produto -> '%s' deseja remover: ", prod->produto.nome);
        scanf("%d", &qtd);
        while (qtd > prod->quantidade){//Verifição
            printf("Nao e possivel remover alem da quantidade\n");
            printf("Qual a quantidade do produto -> '%s' deseja remover: ", prod->produto.nome);
            scanf("%d", &qtd);
        }//Confirmação
        printf("O produto -> '%s' ficara com apenas %d unidade(s).\n", prod->produto.nome, prod->quantidade-qtd);
        printf("Deseja confirmar a remocao de %d unidade(s) do produto -> '%s'?\n[1] Sim\n[2] Nao\n", qtd, prod->produto.nome);
        scanf("%d", &opcao_rem);

        while (opcao_rem < 1 || opcao_rem > 2){
            printf("!!OPCAO INVALIDA!!");
            printf("\nDeseja remover?\n[1] Sim\n[2] Nao\n");
            scanf("%d", &opcao_rem);
        }
        if(opcao_rem == 1){
            printf("%d unidade(s) do produto -> '%s' removida(s) com sucesso!\n", qtd, prod->produto.nome);
            prod->quantidade -= qtd;
            fecharPedido();
        }else{
            printf("Remocao cancelada!\n");
            fecharPedido();
        }
    }
}


//Função Gerar Nota - Essa função imprime a nota fiscal em forma de arquivo - LUIS
void gerarNota(float troco, float pago){ 
    FILE *arquivo;
    Carrinho * aux;
    float valorProd = 0.0;
    float valorTotal = 0.0;
    arquivo = fopen("Nota Fiscal.txt","w");
    fprintf(arquivo,"========================================================\n");
    fprintf(arquivo,"                       NOTA FISCAL\n");
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

//Função Listar Carrinho - Mostra todos os produtos que estão no carrinho para o cliente e pede a ele que escolha se quer
//finalizar o pedido ou continuar comprando - GUILHERME
void fecharPedido(){ 
    if(contador_carrinho > 0){
        int opcao;
        float valorProd = 0.0;
        float valorTotal = 0.0;
        float pagamento;
		Carrinho * aux;
		printf("=========================================================\n");
		printf("                       Seu carrinho\n");
		printf("=========================================================\n");
        printf("%-20s  %-13s  %-10s %-10s\n","Produto","Preco", "Qtd","Valor");
        printf("---------------------------------------------------------\n");
        for (aux = topoCarrinho; aux != NULL; aux = aux->prox){
            valorProd = aux->produto.preco * aux->quantidade;
            valorTotal += valorProd;
            printf("%-20s  %-13.2f  %-10d %-10.2f\n", aux->produto.nome, aux->produto.preco, aux->quantidade, valorProd);
        }
        printf("---------------------------------------------------------\n");
        printf("Valor total da compra: R$%.2f\n", valorTotal);
        printf("---------------------------------------------------------\n");
        do{
            printf("O que voce quer fazer?\n[1] Fechar pedido\n[2] Continuar comprando\n[3] Remover do carrinho\n");
            scanf("%d", &opcao);
            fflush(stdin);

            switch (opcao){
            case 1:
                printf("---------------------------------------------------------\n");
                printf("Valor a ser pago: %.2f\n", valorTotal);
                printf("Insira o valor de pagamento: ");
                scanf("%f", &pagamento);

                while (pagamento < valorTotal){
                    printf("\n!!O valor inserido e menor que o valor Total!!");
                    printf("\nInsira um valor maior ou igual a R$%.2f: ",valorTotal);
                    scanf("%f", &pagamento);
                }

                float troco = pagamento - valorTotal;
                printf("---------------------------------------------------------\n");

                if (troco > 0){
                    printf("\nSeu troco e de R$%.2f", troco);
                }
                gerarNota(troco, pagamento);
                limparCarrinho();
                contador_carrinho = 0;
                printf("\nCompra finalizada!\nSua nota fiscal foi gerada :P\nObrigado pela preferencia!\n");
                break;

            case 2:
                printf("Voltando ao menu de compras...\n");
                comprar();
                break;

            case 3:
                removerCarrinho();
                break;
            default:
                printf("\n !!OPCAO INVALIDA!!\n");
                break;
            }
        }while(opcao < 1 || opcao > 3);
	}else{
		printf("Nao temos ainda produtos cadastrados.\n");
        menu();
	}
}



// Funções de Usuarios do sistema
void cliente(){
    comprar();}

void funcionario(){ // - LEANDRO
    int opcao;

    printf("O que deseja fazer?\n");
    printf("[1]Adcionar produto ao sistema\n[2]Listar todo o estoque\n[3]Voltar ao menu de Login:\n");
    scanf("%d", &opcao);

    while (opcao < 1 || opcao > 3) {
    printf("!!OPCAO INVALIDA!!\n\n");
    printf("O que deseja fazer?\n");
    printf("[1]Adcionar produto ao sistema\n[2]Listar todo o estoque\n[3]Voltar ao menu de Login:\n");
    scanf("%d",&opcao);}

    switch(opcao){
    case 1: 
        cadastrarProduto();
        funcionario();
        break;

    case 2: 
        printf("===============================================\n");
		printf("            Produtos Cadastrados\n");
		printf("===============================================\n");
        listarProdutos();
        funcionario();
        break;          

    case 3:
        printf("\nVoltando ao menu de login...\n\n");
        menu();
        break;}}


//Função Menu -  Chama o menu de login   - VITORIA    
void menu(){ 
    int opcao = 1;
        printf("\n=======================================\n");
        printf("==============   SEV   ================\n");
        printf("=======================================\n\n");

        printf("---------------------------------------\n");
        printf("           OPCOES DE LOGIN\n\n");
        printf("    [1]CLIENTE    |   [2]FUNCIONARIO\n");
        printf("              [3]SAIR\n\n");
        printf("Como deseja acessar: ");
        scanf("%d", &opcao);
        printf("---------------------------------------\n\n");

        while (opcao < 1 || opcao > 3) {
            printf("         !!OPCAO INVALIDA!!\n\n");
            printf("    [1]CLIENTE    |   [2]FUNCIONARIO\n");
            printf("              [3]SAIR\n\n");
            printf("Como deseja acessar: ");
            scanf("%d",&opcao);}

        switch(opcao){

            case 1:
                printf("=======================================\n");
                printf("========== Bem vindo Cliente ==========\n");
                printf("=======================================\n\n\n");
                cliente();
                break;
            case 2:
                printf("=======================================\n");
                printf("======== Bem vindo Colaborador ========\n");
                printf("=======================================\n");
                funcionario();
                break;
            case 3:
                printf("Ate logo!\n");
                break;
            default:
                printf("Opcao invalida");
                break;
            }
        }


int main(){

    adicionarProduto("Leite",5,contador_produto);
    adicionarProduto("Queijo",2,contador_produto);
    adicionarProduto("Pao",0.25,contador_produto);
    adicionarProduto("Presunto",3,contador_produto);
    menu();
}