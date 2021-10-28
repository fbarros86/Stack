/**
 *@file stack.h Header file do ficheiro stack.c
 */

#ifndef CODE_STACK_H
#define CODE_STACK_H
/**
 *\brief Cria um elemento do tipo DADOS com a informação dada.
 *
 * @param var Variável onde e vai colocar o elemento criado
 *
 * @param TIPO Define o tipo de dados que queremos criar
 *
 * @param valor Define o valor que o elemento terá
 */
#define makeDados(var, TIPO, valor) \
  DADOS var;  \
  var.dados.TIPO=valor; \
  var.tipo=TIPO;

/// Esta estrutura representa os diferentes tipos de dados usados.
typedef enum {
    LONG,///< Tipo long
    DOUBLE, ///< Tipo double
    CHAR,///< Tipo char
    STRING,///< Tipo string
    ARRAY,///< Tipo array
    BLOCK//<Tipo block
} TIPO;
/**
 *\brief Definição do tipo array para ser  usada à frente
 */
typedef struct sarray *array;

/**
 * \brief Esta estrutura é usada para representar
 * um elemento da stack.
 *
 * Guarda o tipo do elemento e o prório elemento (este
 * pode ser um long, um double, um char ou uma string).
 */
typedef struct {
    /*@{*/
    TIPO tipo;/**< Tipo de elemento armazenado  */
    union {
        long LONG;/**< É preenchido se o elemento for um long (int) */
        double DOUBLE;/**< É preenchido se o elemento for um double */
        char CHAR;/**< É preenchido se o elemento for um caráter */
        char *STRING;/**< É preenchido se o elemento for uma string */
        array ARRAY;/**< É preenchido se o elemento for um array*/
        char *BLOCK; /**< É preenchido se o elemento for um block*/
    } dados;/**< Elemento armazenado */
    /*@}*/
} DADOS;


/**
 * \brief Esta estrutura é usada para representar
 * um array
 */
struct sarray{
    /*@{*/
    DADOS *ARRAY;/**< Array com elementos do tipo DADOS*/
    long size;/**< Espaço disponível do array*/
    long tam;/**< Tamanho do array*/
    long front;/**< Localidade do primeiro elemento do array*/
    /*@}*/
};

/**
 * \brief Esta estrutura é usada para representar
 * uma stack e tem três componentes.
 */
typedef struct {
    /*@{*/
    int tam; /**< Tamanho atual da stack, ou seja, número de células alocadas */
    int top; /**< Stack pointer */
    DADOS *stck; /**< Endereço do array que representa a stack */
    DADOS var[26]; /**< Array de variáveis */
    /*@}*/
} STACK;

/**
 * \brief Apontador para uma STACK
 */
typedef STACK *Stack;

void push(DADOS d,Stack s);

DADOS pop(Stack s);

void print_stack(Stack s);

void printArray(array);

void init_stack(Stack s);

DADOS getElem(DADOS x,Stack s);

void print_elem (DADOS d);

void putVars (DADOS *, DADOS *);

#endif //CODE_STACK_H
