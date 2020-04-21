//
// Created by alessandro on 20/04/2020.
//

#ifndef VENDINGMACHINE_ESTOQUE_H
#define VENDINGMACHINE_ESTOQUE_H

#define NUMS_SLOTSPRODUTOS 10


extern void est_inicializaEstoque();

extern void est_exportarEstoque();

extern int est_pagamento(float);
extern char* est_getNomeProduto(int);
extern float est_getPrecoProduto(int);
#endif //VENDINGMACHINE_ESTOQUE_H
