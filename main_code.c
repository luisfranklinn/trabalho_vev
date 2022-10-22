#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura de Dados
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