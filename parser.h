/**
 *@file parser.h Header file do ficheiro parser.c
 */

#ifndef CODE_PARSER_H
#define CODE_PARSER_H
/**
 * \brief Constantes globais utilizadas no módulo de parser.
 */
/*@{*/
#define PARSER_SIMBOLS  "+-*/()%\\#&|^~_;@$lcifs.tp?=e<>!:,[]{}w"   /**< Símbolos válidos. */
#define PARSER_SIMBOLS_WITH_E              "&|<>"                   /**< Símbolos com prefixo e */
#define PARSER_SIMBOLS_GROUP_SAB           "{}[]\""                 /**< Símblos de agrupamento : Bloco, Array e String */
#define PARSER_INPUTLINE_SIMBOLS           "tl"                     /**< Símbolos de leitura de linha(s) de input  */
#define PARSER_PREFIX_STRING_SPLIT_SIMBOLS "SN"                     /**< Prefixo de simbolos dos separadores de strings */
#define PARSER_CHAR_PREFIX_LOGIC_SIMBOLS   'e'                      /**< Prefixo de simbolos lógicos */
#define PARSER_CHAR_PREFIX_VAR_SIMBOLS     ':'                      /**< Prefixo de variáveis */
#define PARSER_CHAR_SIMBOL_MULTILINE       't'                      /**< Símbolo de operação imput multi-linha  */

#define EXPRESSION_DELIMS                  " \t\n"    		        /**< Delimitascadores de uma expressões.  */
#define EXPRESSION_SIZE_MAX_TERMS          2048   			        /**< Tamanho máximo da estrutura onde são armazenados os termos das expressões. */
#define EXPRESSION_SIZE_MAX_TERM           500  			        /**< Tamanho máximo do termo de uma expressão. */
#define INPUTLINE_SIZE_MAX                 500	                    /**< Tamanho máximo da linha de input associada ao comando l. */
/*@}*/
#include "stack.h"

int issimbolin(char simbol, char set[]);
void parsing(char *linha, Stack s,char tokens[][EXPRESSION_SIZE_MAX_TERM]);
void parsing_init(char tokens[][EXPRESSION_SIZE_MAX_TERM]);
void parsing_finalize(char tokens[][EXPRESSION_SIZE_MAX_TERM]);


#endif //CODE_PARSER_H
