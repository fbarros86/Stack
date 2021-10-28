/**
 * @file main.c Ficheiro que contém as funções principais do programa.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "parser.h"

/**
    * \brief Função principal do programa.
    *
    * @returns 0
    *
*/
int main() {
  /*@{*/

    STACK s;
    char expressao[10240];/**< String para guardar uma linha. */
    char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];

    init_stack(&s);/**< Inicialização da função stack disponível em stack.c. */

    assert (fgets(expressao, 10240, stdin) != NULL);/**< Assert funcionou corretamente se não devolveu NULL. \
                                                         Função fgets que lê uma linha e guarda a linha na "expressao". */

    assert (expressao[strlen(expressao) - 1] == '\n');/**< Uma vez que é uma string, verifica se o último caracter lido é um '\n'. */

    parsing_init(tokens);/**< Função responsável por iniciar o parsing, disponível em parser.c. */

    parsing(expressao,&s,tokens);/**< Função que é a principal responsável pelo parsing, disponivel em parser.c. */

    parsing_finalize(tokens);/**< Função responsável por finalizar o parsing, disponível em parser.c. */

    print_stack(&s); /**<  Função que imprime o conteúdo da stack, disponível em stack.c. */
    return 0;

}
