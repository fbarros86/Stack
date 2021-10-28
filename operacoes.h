/**
 *@file operacoes.h Header file do ficheiro operacoes.c
 */

/**
 * \brief Constantes globais utilizadas no módulo de parser.
 */
/*@{*/
#define BINBIT_SIMBOLS  "&|^" /**< Símbolos de operações bitwise */
#define UNARY_SIMBOLS  "()~ifcs," /**< Símbolos de operações unárias */
#define STACK_SIMBOLS  "_;\\$@" /**< Símbolos de operações bitwise */
#define ARRAY_CSIMBOLS  "<>/=" /**< Símbolos de operações sobre arrays */
#define ARRAY_SSIMBOLS  ["S/","N/"] /**< Símbolos de operações sobre arrays */
#define LOGIC_SIMBOLS  "=<>?!" /**< Símbolos de operações sobre arrays */
/*@}*/


double operaD (double x, double y, char c);
double operaL (long x, long y, char c);
char operaC (char x, char y, char c);
void opBIN (DADOS op1, DADOS op2, char c, Stack s);
void opBIT (DADOS op1, DADOS op2, char c, Stack s);
void opUN (DADOS op, char c, Stack s);
void calculate ( char *operator, Stack s);
