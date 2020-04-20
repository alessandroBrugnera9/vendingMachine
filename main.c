#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void main(void) {
    float credito = 0.0;
    int inventorySize = 10;
    bool ligado = true;
    int i;
    struct produto {
        char nome[30];
        float preco;
        int quantidade;
    };
    struct produto produtos[inventorySize];
    for (i=0;i<inventorySize;i++) { //ver se existe no estoque
        produtos[i].quantidade = -1;
        produtos[i].preco = 0.0;
    }

    //Já liga com isso
    strncpy(produtos[0].nome, "suco de laranja", 29);
    produtos[0].nome[29] = 0;
    produtos[0].preco = 1.00;
    produtos[0].quantidade = 3;

    strncpy(produtos[1].nome, "suco de maca", 29);
    produtos[1].preco = 2.00;
    produtos[1].quantidade = 3;
    int acao;
    int produtoDesejado;
    int slotAlterado;

    while (ligado) { //Listener
        printf("\n");
        printf("O  Que você deseja fazer (colocar o número respectivo):");
        printf("\n");
        printf("1  Para adicionar crédito.");
        printf("\n");
        printf("2  Para selecionar produto.");
        printf("\n");
        printf("3  Cancela a compra e devolve o troco.");
        printf("\n");
        printf("7  Modo de alteração de estoque.");
        printf("\n");
        printf("8  Remove produto.");
        printf("\n");
        printf("9  Desliga a máquina.");
        fflush(stdin);
        printf("\n");
        scanf("%d", &acao);

        switch (acao) //Recebe ação desejada
        {
            float add;
            case 1: //adicao
                fflush(stdin);
                printf("Quantos reais você vai adicionar? ");
                scanf("%f",&add);
                credito = credito + add;
                fflush(stdin);
                printf("Crédito: R$%.2f", credito);
                break;

            case 2: //selecionar produtos
                for (i=0;i<inventorySize;i++) {
                    if (produtos[i].quantidade>-1) {
                        fflush(stdin);
                        printf("Produto %i : ", i);
                        printf("%i ", produtos[i].quantidade);
                        printf("%s", produtos[i].nome);
                        printf(": R$%.2f.\n", produtos[i].preco);
                    }
                }
                fflush(stdin);
                printf("Qual produto você deseja (coloque o número respectivo)? ");
                scanf("%d", &produtoDesejado);

                if (credito>=produtos[produtoDesejado].preco) {
                    printf("\n");
                    printf("Produto %s entregue.", produtos[produtoDesejado].nome);
                    printf("\n");
                    printf("Troco: %.2f.", credito - produtos[produtoDesejado].preco);
                }
                else {
                    printf("\n");
                    printf("Crédito insuficiente.");
                }
                break;

            case 3: //cancela compra
                printf("Compra canceladda.\n");
                printf("Troco: R$%.2f.\n", credito);
                credito = 0;
                break;


            case 7: //Altera slot
                for (i=0;i<inventorySize;i++) {
                    if (produtos[i].quantidade>-1) {
                        printf("Produto %i : ", i);
                        printf("%i ", produtos[i].quantidade);
                        printf("%s", produtos[i].nome);
                        printf(": R$%.2f.\n", produtos[i].preco);
                    }
                }
                printf("Em qual slot de produto você quer mexer (Número de 0 a 9)?\n");
                fflush(stdin);
                scanf("%d", &slotAlterado);

                printf("Nome do Produto no slot %i: ", slotAlterado);
                fflush(stdin);
                scanf("%s", produtos[slotAlterado].nome);
                printf("Quantidade do Produto %s: ", produtos[slotAlterado].nome);
                fflush(stdin);
                scanf("%d", &produtos[slotAlterado].quantidade);
                printf("Preço do Produto %s: ", produtos[slotAlterado].nome);
                fflush(stdin);
                scanf("%f", &produtos[slotAlterado].preco);
                printf("\n");

                printf("Produto no slot %i : ", slotAlterado);
                printf("%i ", produtos[slotAlterado].quantidade);
                printf("%s", produtos[slotAlterado].nome);
                printf(": R$%.2f.\n", produtos[slotAlterado].preco);
                printf("\n");
                break;

            case 8: //Altera slot
                for (i=0;i<inventorySize;i++) {
                    if (produtos[i].quantidade>-1) {
                        printf("Produto %i : ", i);
                        printf("%i ", produtos[i].quantidade);
                        printf("%s", &produtos[i].nome);
                        printf(": R$%.2f.\n", produtos[i].preco);
                    }
                }
                printf("Qual slot de produto será removido (Número de 0 a 9)?\n");
                fflush(stdin);
                scanf("%d", &slotAlterado);

                strncpy(produtos[slotAlterado].nome, "", 29);
                produtos[slotAlterado].nome[29] = 0;
                produtos[slotAlterado].quantidade = -1;
                produtos[slotAlterado].preco = 0.0;

                printf("Slot %i vazio. ", slotAlterado);
                break;

            case 9:
                ligado = false;
                break;


            default:
                printf("Comando não identificado.");
        }
    }
}