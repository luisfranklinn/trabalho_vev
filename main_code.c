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


// Manter Carrinho
void adicionar_Carrinho(Produto prod, int qtd){
    Carrinho *carrinho = (Carrinho*) malloc (sizeof (Carrinho));
    Carrinho * aux;
    if(topoCarrinho == NULL){
        carrinho->produto = prod;
        carrinho->quantidade = qtd;
        carrinho->prox = topoCarrinho;
        topoCarrinho = carrinho;
        contador_carrinho++;
    }else{
        for(aux = topoCarrinho; aux != NULL; aux = aux->prox){
            if(prod.codigo == aux->produto.codigo){
                aux->quantidade += qtd;
                break;
            }else if(aux->prox == NULL){
                carrinho->produto = prod;
                carrinho->quantidade = qtd;
                carrinho->prox = topoCarrinho;
                topoCarrinho = carrinho;
                contador_carrinho++;
                break;
            }
        }
    }
}

void comprar(int id){ 
    int cod_prod_carrinho;
    int opcao;
    int qtd = 1;
    listar_Produtos();
    
    
    printf("Selecione pelo codigo qual produto deseja adicionar no carrinho: ");
    scanf("%d", &cod_prod_carrinho);
    Produto * found = buscar_Prod(cod_prod_carrinho, raizProduto);
    
    while(found->codigo == NULL){
        printf("Selecione pelo codigo qual produto deseja adicionar no carrinho: ");
        scanf("%d", &cod_prod_carrinho);
        Produto * found = buscar_Prod(cod_prod_carrinho, raizProduto);
    };



    printf("Qual a quantidade: ");
    scanf("%d", &qtd);


    while (found->quantidade_prod < qtd){
        printf("Só temos %d unidades de %s no estoque!\n", found->quantidade_prod, found->nome);   
        printf("Qual a quantidade você deseja: ");
        scanf("%d", &qtd);
    }
    
    if (qtd == found->quantidade_prod){
        remover_produto_estoque(raizProduto, cod_prod_carrinho);
    }
    else{
        remover_produto_quantidade(found->codigo,qtd);
    }

    adicionar_Carrinho(*found, qtd);

    printf("\nAdcionado ao carrinho! -> Produto: %s | Quantidade: %d \n",found->nome, qtd);
    printf("----------------------------------------------------------\n");
    printf("Deseja continuar comprando?\n[1] Sim\n[2] Nao (Volta ao Menu do Cliente)\n");
    scanf("%d", &opcao);

    while(opcao < 1 || opcao > 2){
        printf("!!OPCAO INVALIDA!!\n");
        printf("Deseja continuar comprando?\n[1] Sim\n[2] Nao\n");
        scanf("%d", &opcao);}

    switch(opcao){
        case 1:
            comprar(id);
            break;
        case 2:
            fechar_Pedido(id);
            break;
    }

}

int esvaziar_Carrinho(){
    Carrinho * aux = topoCarrinho;
    for(aux = topoCarrinho; aux != NULL; aux = aux->prox){
        topoCarrinho = topoCarrinho->prox;
        Carrinho * lixo = aux;
        free(lixo);
        contador_carrinho--;
    }
}

void remover_Carrinho(int id){
    if ( contador_carrinho > 0 ){
        int cod_prod_carrinho = 0;
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
        scanf("%d", &cod_prod_carrinho);
        do{
            resul = 0;
            for(prod = topoCarrinho; prod != NULL; prod = prod->prox){
                if(cod_prod_carrinho == prod->produto.codigo){
                    resul = 1; //encontrou
                    break;
                }
            }
            if (resul == 0){
                printf("\nErro! Codigo inexistente!\n");
                printf("Selecione o codigo do produto que deseja remover: ");
                scanf("%d", &cod_prod_carrinho);
            }
        }while(resul == 0);

        Produto * found = buscar_Prod(cod_prod_carrinho, raizProduto);

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
            found->quantidade_prod += qtd;
            fechar_Pedido(id);
        }else{
            printf("Remocao cancelada!\n");
            fechar_Pedido(id);
        }
    }
}

void fechar_Pedido(int id){ 
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
                gerar_Nota(id, troco, pagamento);
                esvaziar_Carrinho();
                contador_carrinho = 0;
                printf("\nCompra finalizada!\nSua nota fiscal foi gerada :P\nObrigado pela preferencia!\n");
                break;

            case 2:
                printf("Voltando ao menu de compras...\n");
                comprar(id);
                break;

            case 3:
                remover_Carrinho(id);
                break;
            default:
                printf("\n !!OPCAO INVALIDA!!\n");
                break;
            }
        }while(opcao < 1 || opcao > 3);
	}else{
		printf("Nao temos ainda produtos cadastrados.\n");
        
	}
}


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


int main(){

    cadastrar_Conta("Luis", "Franklin", 1234, id_cont, 1);
    cadastrar_Conta("Kauan", "Deyvid", 1234, id_cont, 2);
    cadastrar_Conta("Marcos", "Gabriel", 1234, id_cont, 3);
    cadastrar_Produto("Leite",1,5, 10);
    cadastrar_Produto("Queijo",2,2,5);
    cadastrar_Produto("Pao",3,2,0.25);
    cadastrar_Produto("Presunto",4,3,5);
    login();
    
}
