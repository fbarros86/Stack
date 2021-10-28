/**
 *@file stack.c Ficheiro que contém as funções relacionadas com a stack.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"

/**
 *\brief Inicializa a STACK s.
 *
 *Define como o tamanho inicial 10
 *(alocando 10 células de memória), coloca o top em -1 e inicializa
 * o array das variáveis com os valores pré-definidos.
 *
 *@param s Stack que é inicializada
 */
void init_stack(Stack s) {
    s->tam = 10;
    s->top = -1;
    s->stck = (DADOS *) malloc(10 * (sizeof(DADOS)));
    makeDados(x1,LONG,10)
    makeDados(x2,LONG,11)
    makeDados(x3,LONG,12)
    makeDados(x4,LONG,13)
    makeDados(x5,LONG,14)
    makeDados(x6,LONG,15)
    makeDados(x7,CHAR,'\n')
    makeDados(x8,CHAR,' ')
    makeDados(x9,LONG,0)
    makeDados(x10,LONG,1)
    makeDados(x11,LONG,2)
    s->var[0] = x1; //A
    s->var[1] = x2; //B
    s->var[2] = x3; //C
    s->var[3] = x4; //D
    s->var[4] = x5; //E
    s->var[5] = x6; //F
    s->var[13] = x7; //N
    s->var[18] = x8; //S
    s->var[23] = x9; //X
    s->var[24] = x10; //Y
    s->var[25] = x11; //Z

}

/**
 *\brief Acrescenta um elemento ao topo da STACK s.
 *
 *Começa por incrementar o stack pointer (top). De seguida,
 *verifica se a stack tem espaço para ser acresentado um elemento.
 *Caso isto não se verifique, duplica o tamanho da stack (o objetivo de
 *duplicar o tamanho, e não simplesmente aumentar um, é aumentar a eficiência).
 *
 *Finalmente, coloca o elemento no topo da stack.
 *
 * @param Stack que é alterada
 *
 *@param d Representa o elemento que se quer colocar na stack
 */
void push(DADOS d, Stack s) {
    (s->top)++;
    if ((s->top) >= s->tam) {
        s->tam *= 2;
        s->stck = (DADOS *) realloc(s->stck, (s->tam) * (sizeof(DADOS)));
    }
    s->stck[s->top] = d;
   // printf("Foi acrescentado o elemento:");
   // print_elem(d);
   // putchar('\n');
   // print_stack(s);
}

void putVars(DADOS *x, DADOS *y){
  int i;
  for (i=0;i<25;i++) x[i]=y[i];
}


/**
 *\brief Retira o elemento que se encontra no topo da STACK s.
 *
 *Começa por verificar se o espaço alocado para a stack corresponde ao
 *quádruplo do stack pointer (top). Se isto se verficar, diminui o tamanho da
 *stack para metade (o objetivo de só diminuir o tamanho quando este é o quádruplo
 *,e não simplesmente diminuir um sempre, é aumentar a eficiência).
 *
 *Finalmente decrementa o stack pointer.
 *
 *Nota: Esta função só funciona se a stack não estiver vazia.
 *
 *@param s Stack que é alterada
 *
 *@returns O elemento que foi retirado da stack
 */
DADOS pop(Stack s) {
    DADOS d;
    assert (s->top >= 0);
    if (s->tam / 4 > s->top) {
        s->tam /= 2;
        s->stck = (DADOS *) realloc(s->stck, (s->tam) * (sizeof(DADOS)));
    }
    // printf("Foi retirado o elemento:");
    // print_elem(s->stck[s->top]);
    // putchar('\n');
    d=s->stck[(s->top)--];
   // print_stack(s);
    return d;
}

/**
 *\brief Vê qual o elemento que está na stack numa dada posição.
 *
 * @param x Posição a verificar na STACK s
 *
 * @param s Stack onde se procura o elemento
 *
 * @returns Elemento na posição dada
 */
DADOS getElem(DADOS x,Stack s) {
    assert (x.tipo == LONG);
    return s->stck[s->top - x.dados.LONG];
}

/**
  *\brief Imprime o conteúdo de um array
  *
  *@param a Array a imprimir
  */
void printArray (array a) {
  int i;
  for (i=0;i<a->tam; i++)
    print_elem(a->ARRAY[(i+a->front)%a->size]);
}

/**
 *\brief Imprime um elemento do tipo DADOS
 *
 *@param d Elemento a imprimir
 */
void print_elem (DADOS d){
  switch (d.tipo) {
      case LONG:
          printf("%ld", d.dados.LONG);
          break;
      case DOUBLE:
          printf("%g", d.dados.DOUBLE);
          break;
      case CHAR:
          printf("%c", d.dados.CHAR);
          break;
      case STRING:
          printf("%s", d.dados.STRING);
          break;
      case ARRAY:
          printArray (d.dados.ARRAY);
          break;
      case BLOCK:
          printf("{%s}", d.dados.BLOCK);

  }
}

/**
 *\brief Imprime o conteúdo da stack s.
 *
 *@param s Stack a imprimir
 */
void print_stack(Stack s) {
    for (int i = 0; i <= s->top; i++)
       print_elem(s->stck[i]);
    putchar('\n');
}
