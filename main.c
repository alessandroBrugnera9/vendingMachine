#include <stdio.h>
#include <stdbool.h>
#include "definicoes.h"
#include "estoque.h"
#include "caixaDeDinheiro.h"
#include "comunicador.h"

int acaoMatrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximoEstadoMatrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];

void iniciaMaquinaEstados(void) {
    int i;
    int j;

    for (i = 0; i < NUM_ESTADOS; i++) {
        for (j = 0; j < NUM_EVENTOS; j++) {
            acaoMatrizTransicaoEstados[i][j] = NENHUMA_ACAO;
            proximoEstadoMatrizTransicaoEstados[i][j] = i;
        }
    }

    acaoMatrizTransicaoEstados[IDLE][PEDIR] = PEDINDO;
    proximoEstadoMatrizTransicaoEstados[IDLE][PEDIR] = A01;

    acaoMatrizTransicaoEstados[PEDINDO][PEDIDOSUCESSO] = IDLE;
    proximoEstadoMatrizTransicaoEstados[PEDINDO][PEDIDOSUCESSO] = A02;


    acaoMatrizTransicaoEstados[IDLE][INSERIRDINHEIRO] = INSERINDO;
    proximoEstadoMatrizTransicaoEstados[IDLE][INSERIRDINHEIRO] = A03;

    acaoMatrizTransicaoEstados[INSERINDO][DINHEIROINSERIDO] = IDLE;
    proximoEstadoMatrizTransicaoEstados[INSERINDO][DINHEIROINSERIDO] = A04;


    acaoMatrizTransicaoEstados[IDLE][CANCELAR] = CANCELANDO;
    proximoEstadoMatrizTransicaoEstados[IDLE][CANCELAR] = A09;


    acaoMatrizTransicaoEstados[IDLE][ALTERARESTOQUE] = ALTERANDOESTOQUE;
    proximoEstadoMatrizTransicaoEstados[IDLE][ALTERARESTOQUE] = A05;

    acaoMatrizTransicaoEstados[ALTERANDOESTOQUE][ESTOQUEALTERADO] = IDLE;
    proximoEstadoMatrizTransicaoEstados[ALTERANDOESTOQUE][ESTOQUEALTERADO] = A06;


    acaoMatrizTransicaoEstados[IDLE][REMOVERPRODUTO] = REMOVENDOPRODUTO;
    proximoEstadoMatrizTransicaoEstados[IDLE][REMOVERPRODUTO] = A07;

    acaoMatrizTransicaoEstados[REMOVENDOPRODUTO][PRODUTOREMOVIDO] = IDLE;
    proximoEstadoMatrizTransicaoEstados[REMOVENDOPRODUTO][PRODUTOREMOVIDO] = A08;


}

void iniciaSistema(void) {
    iniciaMaquinaEstados();
    est_inicializaEstoque();
    cxd_zeraCaixa();
    printf("Vending Machine ligada!\n");
}


int executaAcao(int codigoAcao) {
    int eventoInterno = NENHUM_EVENTO;

    if (codigoAcao == NENHUMA_ACAO) {
        return NENHUM_EVENTO;
    }

    switch (codigoAcao) {
        break;
        case A01:
            com_inserindoDinheiro();
            eventoInterno = DINHEIROINSERIDO;
            break;

        case A02:
            com_dinheiroInserido();
            break;

        case A03:
            com_pedindo();
            eventoInterno = PEDIDOSUCESSO;
            break;

        case A04:
            com_pedidoRecebido();
            break;

        case A05:
            com_alterandoEstoque();
            eventoInterno = ESTOQUEALTERADO;
            break;

        case A06:
            com_estoqueAlterado();
            break;

        case A07:
            com_removendoProduto();
            eventoInterno = PRODUTOREMOVIDO;
            break;

        case A08:
            com_produtoRemovido();
            break;

        case A09:
            com_cancelamento();
            break;

        default:
            printf("Ação não identificada.");
            break;
    }

    return eventoInterno;
}

int obterEvento() {
    //TODO: recebe input
    int teclaRecebida = com_inputSeletor();

    switch (teclaRecebida) {
        case PEDINDO:
            return PEDINDO;
            break;
        case INSERINDO:
            return INSERINDO;
            break;
        case CANCELANDO:
            return CANCELANDO;
            break;
        case ALTERANDOESTOQUE:
            return ALTERANDOESTOQUE;
            break;
        case REMOVENDOPRODUTO:
            return REMOVENDOPRODUTO;
            break;
        default:
            printf("Comando desconhecido."); //TODO:avaliar se eh gambiarra
            break;
    }



    return NENHUM_EVENTO;
}

int obterProximoEstado(int estado, int evento) {
    return proximoEstadoMatrizTransicaoEstados[estado][evento];
}

int obterAcao(int estado, int evento) {
    return acaoMatrizTransicaoEstados[estado][evento];
}

int main(void) {

    int codigoEvento;
    int codigoAcao;
    int estado;
    int eventoInterno;

    estado = IDLE;
    eventoInterno = NENHUM_EVENTO;

    iniciaSistema();

//    loop de maquina de estados:
    while (true) {
        if (eventoInterno == NENHUM_EVENTO) {
            codigoEvento = obterEvento();
        } else {
            codigoEvento = eventoInterno;
        }
        if (codigoEvento != NENHUM_EVENTO) {
            codigoAcao = obterAcao(estado, codigoEvento);
            estado = obterProximoEstado(estado, codigoEvento);
            eventoInterno = executaAcao(codigoAcao);
            printf("Estado: %d Evento: %d Acao: %d\n", estado, codigoEvento, codigoAcao);


        }
    }

}