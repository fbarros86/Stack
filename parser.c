/**
 * @file parser.c Módulo que contem o PARSER, que verifica se as expressões do input são válidas e "manda" executá-las.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>
#include "parser.h"
#include "stack.h"
#include "operacoes.h"



/**
 * \brief Função que valida uma string, indicando se é ou não uma string numérica inteira.
 *
 * @param token String (token) a ser validada.
 *
 * @returns 0, se não for um número inteiro; o tamanho do token, caso contrário.
 */
int isintnum(char token[]) {
    int size = 0;
    char *sobra;

    strtol(token, &sobra,10);
    if ((strlen(token) != strlen(sobra)) && (strlen(sobra) == 0))
        size = strlen(token);

    return size;
}

/**
 * \brief Função que valida uma string, indicando se é ou não uma string numérica (inteira ou decimal).
 *
 * @param token String (token) a ser validada.
 *
 * @returns 0, se não for um número; o tamanho do token, caso contrário.
 */
int isnumeric(char token[]) {
    int size = 0;
    char *sobra;

    strtod(token, &sobra);

    if ((strlen(token) != strlen(sobra)) && (strlen(sobra) == 0))
        size = strlen(token);

    return size;
}


/**
 * \brief Função que valida um símbolo (do tipo char), indicando se pertence, ou não, a um conjunto de símbolos.
 *
 * @param simbol Símbolo a ser verificado.
 *
 * @param set Conjunto onde vai ser procurado o símbolo recebido.
 *
 * @returns 0, se não pertencer ao conjunto; 1, caso contrário.
 */
int issimbolin(char simbol, char set[])
{
    int i=0, found = 0;

    while ((i < (int)strlen(set)) && (found == 0)) {
            if (simbol == set[i]) found = 1;
            i++;
        }
    return found;
}

/**
 * \brief Função que valida a coerência dos símbolos de abertura e fecho de agrupamento do tipo bloco e array.
 *
 * @param token Token a ser validado.
 *
 * @param simbolopen Símbolo de abertura do agrupamento ( '[' ou '{')
 *
 * @param simboloclose Símbolo de fecho do agrupamento ( ']' ou '}')
 *
 * @returns 1, caso o número de '[' e ']' existam e sejam iguais; 0, caso contrário.
 */
int isValidGroup(char *token, char simbolopen, char simbolclose)
{
    int abriu = 0, fechou = 0, i=0 ;

    if (strlen(token) > 1 )   {
       while ((abriu >= fechou ) && (i < (int)strlen(token)))
       {
           if (token[i]==simbolopen) abriu ++;
           else if (token[i]==simbolclose) fechou ++;
           i++;
       }
    }
    return (((abriu > 0) && (fechou == abriu)) ? 1 : 0);
}

/**
 * \brief Função que valida a coerência do número de vezes que aparece o símbolo ' " ', em tokens do tipo strings.
 *
 * @param token Token a ser validado.
 *
 * @returns 1, caso o número de aspas seja coerente; 0, caso contrário.
 */
int isValidString(char *token)
{
    int contadoraspas = 0, i=0 ;

    if (strlen(token) > 1 ) {
       while  (i < (int)strlen(token))
       {
           if (token[i]=='\"') contadoraspas ++;
           i++;
       }
    }
    return (((contadoraspas > 0) && (contadoraspas % 2 == 0)) ? 1 : 0);
}

/**
 * \brief Função que valida se um dado token é do tipo string.
 *
 * @param token Token a ser validado.
 *
 * @returns O tamanho do token, caso seja uma string; 0, caso contrário.
 */
int isString(char *token)
{
    int size = 0;

    if ((strlen(token) > 0) && (token[0] == '\"'))
       {
        size = strlen(token);
        assert ((size > 1) &&  isValidString(token));
       }
    return size;
}

/**
 * \brief Função que valida se um dado token é do tipo array. 
 *
 * @param token Token a ser validado.
 *
 * @returns O tamanho do token, caso seja um token do tipo array; 0, caso contrário.
 */
int isArray(char *token)
{
    int size = 0;

    if ((strlen(token) > 0) && (token[0] == '['))
       {
        size = strlen(token);
        assert ((size > 1) &&  isValidGroup(token,'[',']'));
       }
    return size;
}

/**
 * \brief Função que valida se um dado token é do tipo bloco.
 *
 * @param token Token a ser validado.
 *
 * @returns O tamanho do token, caso seja um token do tipo bloco; 0, caso contrário.
 */
int isBloco(char *token)
{
    int size = 0;

    if ((strlen(token) > 0) && (token[0] == '{'))
       {
        size = strlen(token);
        assert ((size > 1) &&  isValidGroup(token,'{','}'));
       }
    return size;
}

/**
 * \brief Função que procura o primeiro símbolo de grupo (abertura).
 *
 * @param token Token a ser validado.
 *
 * @returns A posicao do primeiro simbolo de grupo (bloco, array, string); -1, caso contrário.
 */
int fstGroupSimbol(char *token)
{
    int i = 0, posGroupSimbol = -1;
    int size = strlen(token);

    while ((size > 0) && (i < size) && (posGroupSimbol == -1))
    {
        if (issimbolin(token[i], PARSER_SIMBOLS_GROUP_SAB) != 0) posGroupSimbol = i;
        i++;
    }
    return (posGroupSimbol);
}

/**
 * \brief Função que procura o último símbolo de grupo (fecho).
 *
 * @param token Token a ser validado.
 *
 * @returns A posicao do par que fecha o grupo (bloco, array, string); -1, caso contrário.
 */
int getPosParGroupSimbol(char *token, int inicio)
{
    int  posParGroupSimbol = -1;
    int  i = inicio + 1;
    char simbolo = ' ';
    char opensimbol = token[inicio];
    int  nivelsimbol = 0;

    if (i >= 0)
    {
        switch (opensimbol)
        {
        case '\"':
           simbolo = '\"';
           break;
        case '[':
           simbolo = ']';
           break;
        case '{':
           simbolo = '}';
           break;
        }
        if (opensimbol != '\"') nivelsimbol = 1;
        while ((i<(int)strlen(token)) && (posParGroupSimbol ==-1))
        {
            if ((opensimbol != '\"') && issimbolin(token[i], PARSER_SIMBOLS_GROUP_SAB))
            {
                if (token[i] == opensimbol)
                   nivelsimbol ++;
                else if (token[i] == simbolo)
                   nivelsimbol --;
            }

            if ((token[i] == simbolo) && (nivelsimbol == 0)) posParGroupSimbol = i;
            i++;
        }
    }
    return posParGroupSimbol;
}

/**
 * \brief Função que indica se existe pelo menos um símbolo de grupo (bloco, array, string).
 *
 * @param token Token a ser validado.
 *
 * @returns O tamanho do token, caso exista; 0, caso contrário.
 */
int hasGroupSimbol(char *token)
{
     return((fstGroupSimbol(token) != -1) ? strlen(token) : 0);
}

/**
 * \brief Função que valida se um token é um símbolo de agrupamento.
 *
 * @param token Token a ser validado.
 *
 * @returns O tamanho do token, caso seja; 0, caso contrário.
 */
int isGroupSimbol(char *token)
{
    int size = 0;
    if (issimbolin(token[0], PARSER_SIMBOLS_GROUP_SAB))
    {
        if (isBloco(token) || isArray(token) || isString(token))
           size = strlen(token);
    }
    return (size);
}


/**
 * \brief Função que valida um símbolo, indicando se se trata de uma variável.
 *
 * @param simbol Símbolo a ser validado.
 *
 * @returns 1, se pertencer ao conjunto; 0, caso contrário.
 */
int isvarsimbol(char simbol)
  {
     return ((simbol >= 'A' && simbol <= 'Z') ? 1 : 0);
  }

/**
 * \brief Função que valida um token, indicando se se trata de um token com prefixo 'e' ou':', ou de um token com sufixo '/'.
 *
 * @param token Token a ser validado.
 *
 * @returns 0, se não for um símbolo composto; 2, caso contrário.
 */
int iscompsimbol(char token[]){
    int size = 0;

    if (strlen(token) == 2)
         {

            if (token[0] == PARSER_CHAR_PREFIX_LOGIC_SIMBOLS) {
                if (issimbolin(token[1], PARSER_SIMBOLS_WITH_E))  size = 2;
                assert (size > 0);
            }
            else if (token[0] == PARSER_CHAR_PREFIX_VAR_SIMBOLS) {
                if (isvarsimbol(token[1])) size = 2;
                assert (size > 0);
            }
            else if ((token[1] = '/') && issimbolin (token[0], PARSER_PREFIX_STRING_SPLIT_SIMBOLS) )
                        size = 2; 
         }

    return size;
}


/**
 * \brief Função que valida o termo de uma expressão, indicando se é ou não um símbolo válido.
 *
 * @param token String (token) a ser validada.
 *
 * @returns 0, se não for um símbolo; o tamanho do token, caso contrário.
 */
int issimbol(char token[]) {
    int size = 0;

    size = isnumeric(token);                                    //porque podem existir . ou e no numero ('E' = base 10)
    if ((size == 0) && isvarsimbol(token[0]))
    {
        size = strlen(token);
        assert (size == 1);
    }

    if ((size == 0) && (issimbolin(token[0], PARSER_SIMBOLS))) {size = strlen(token);}

    return size;

}


/**
 * \brief Função que recebe um token e valida se é uma operação de leitura - comando l.
 *
 * @param token String (token) a ser validada.
 *
 * @returns 0, se não for uma operação de leitura; o tamanho do token, caso contrário.
 */
int isOpReader(char *token) {

    int size = 0;
    if ((strlen(token) == 1) && issimbolin(token[0], PARSER_INPUTLINE_SIMBOLS))
        size = strlen(token);
    return size;

}

/**
 * \brief Função que recebe um token e valida se é uma operação de leitura de um input com várias linhas - comando t.
 *
 * @param token String (token) a ser validada.
 *
 * @returns 0, se não for; o tamanho do token, caso contrário.
 */
int isopmultiline(char *token) {
    int size = 0;
    if ((strlen(token) == 1) && (token[0] == PARSER_CHAR_SIMBOL_MULTILINE))
        size = strlen(token);
    return size;
}


/**
 * \brief Função que valida uma string, indicando se é ou não um token válido.
 *
 * @param token String (token) a ser validada.
 *
 * @returns 0, se não for um token válido; o tamanho do token, caso contrário.
 */
int isvalidtoken(char token[]) {
    int size = 0;

    size = isnumeric(token);
    if (size==0) size = hasGroupSimbol(token);  //símbolo agrupamento (bloco, array ou string)
                        //isGroupSimbol(token); 
    if (size == 0) {
        size = iscompsimbol(token);             //símbolo composto com prefixo
        if (size == 0) {
            size = issimbol(token);
            assert (size == 1);
        }
    }
    return size;
}

/**
 * \brief Função que valida um input, indicando se é ou não o comando EOF.
 *
 * É necessário introduzir pelo menos uma linha não vazia.
 *
 * @param inputline Linha a ser validada.
 *
 * @returns 1, se for EOF; 0, caso contrário.
 */
int isEndOfInput(char *inputline) {

    return ((inputline[0] == '\0' ? 1 : 0));
}

/**
 * \brief Função que valida um input, indicando se é ou não um caracter válido.
 *
 * @param inputC Input a ser validado.
 *
 * @returns 1, se for um caracter válido; 0, caso contrário.
 */
int isValidChar(char inputC)
{
    int isValid = 1;
    if ((inputC < 32) && (inputC != '\t')) isValid = 0;

    return isValid;
}

/**
 * \brief Função que lê uma sequência de caracteres, terminada por '\n'.
 *
 * @param inputline Linha de input a ser validada.
 *
 * @param maxlenght Tamanho máximo da célula.
 *
 * @param permitevazio Parâmetro que decide se é permitido um input vazio, ou não.
 *
 */
void readline(char inputline[], int maxlenght, int permitevazio) {
    int c;
    int i = 0;

    inputline[0] = '\0';
    c = getchar();

    while ((i < maxlenght) && isValidChar(c)) {
        inputline[i++] = c;
        c = getchar();
    }
    if (i < maxlenght) inputline[i] = '\0';  //tem de ser antes do assert por causa do ctrl D
    assert ((c == '\n' || c == EOF || c == '\t') && (i > 0 || permitevazio != 0) && maxlenght >= i);
}

/**
 * \brief Função que separa o token do resto da linha.
 *
 * @param line Linha de input a ser trabalhada.
 *
 * @param *rest Resto onde vai ser guardado o resto da string
 *
 * @returns O token separado.
 *
 */
char *get_token(char *line, char *rest)         
{
    int i=0, size = 0, sizetoken = 0;
  //  char restgroup[EXPRESSION_SIZE_MAX_TERM];
    int posGS = -1;

    rest[0] = '\0';
    posGS = fstGroupSimbol(line);

    size = strlen(line);
    if (posGS == 0 )
      {
        posGS = getPosParGroupSimbol(line, posGS)+ 1;
        sizetoken = posGS;
        i = posGS;
      }
      else
      {
        while ((i < size && (posGS == -1 || i < posGS)) && ((issimbolin(line[i], EXPRESSION_DELIMS) == 0))) i++;
        sizetoken = i;
      }


      while ((i < size) && (line[i] == 32)) i++;
      strcpy (rest, strndup((char *)(line + i), size - i));
        //(*rest) = strndup((* line) + i, size - i),

    return strndup(line, sizetoken);
}



/**
 * \brief Função que recebe a expressão que se pretende calcular e separa-a em termos.
 *
 * @param tokens Estrutura onde vão ser armazenados os termos (tokens) resultantes da "decomposição" da expressão.
 *
 * @param expressao Expressão sobre a qual vai ser feito o split.
 *
 * @returns O número de termos (tokens) colocados na estrutura.
 */
int split_expression(char tokens[][EXPRESSION_SIZE_MAX_TERM], char expressao[]) {
    /*@{*/
    int numtokens = 0;
    char *token = NULL;
    int size = 0;
    char rest[EXPRESSION_SIZE_MAX_TERM];

    token = get_token(expressao, rest);
    while (token[0] != '\0') {
        size = isvalidtoken(token);
        if (size > 0) {
            strcpy(tokens[numtokens++], token);
            //printf("--> (%s)\n", token);
            strcpy(expressao, rest);
            token = get_token(expressao, rest);/**< Vai buscar o próximo token da expressão. */
        } else { token[0] = '\0'; }
    }

    return numtokens;
}


/**
 * \brief Função que inicializa a estrutura de dados de apoio às funções de Parsing.
 *
 * É obrigatório chamar esta função antes de chamar a de parsing.
 *
 */
void parsing_init(char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM]) {
    int i;
    for (i = 0; i < EXPRESSION_SIZE_MAX_TERM; i++)
        tokens[i][0] = '\0';
}



/**
 * \brief Função que finaliza a estrutura de dados de apoio às funções de Parsing.
 */
void parsing_finalize(char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM]) {
    parsing_init(tokens);
}


/**
 * \brief Função que executa a leitura de um input, através das operações 't' e 'l'.
 *
 * @param token a ser lido
 *
 * @param Stack s Stack para onde vão ser feitos PUSH dos elementos.
 *
 */
void opInput(char *token, Stack s)
{
    /*@{*/
    int readmultiline = 0, numberinputs = 0;
    char inputline[INPUTLINE_SIZE_MAX];
    char inputstring[INPUTLINE_SIZE_MAX];
    int tamanho=0;

    readmultiline = isopmultiline(token);
    inputline[0]='\0';
    inputstring[0] = '\0';

    do {
        readline(inputline, INPUTLINE_SIZE_MAX, readmultiline);
        if ((readmultiline == 0) || isEndOfInput(inputline) == 0)   
        {
            if (readmultiline != 0) {
                if (numberinputs > 0) {                
                    tamanho = strlen(inputstring);                   
                    inputstring[tamanho] = ' ';
                    inputstring[tamanho+1] ='\0';            
                }
                strcat(inputstring, inputline);                  
            } 
            else
            { 
                makeDados(elem, STRING, strdup(inputline));
                push(elem,s);
            }
            numberinputs ++;

        }
    } while (readmultiline != 0 && (isEndOfInput(inputline) == 0));
    if (readmultiline != 0)
    {
        makeDados(elem, STRING, strdup(inputstring));
        push(elem,s);
    }
    assert (numberinputs > 0);/**< Obrigatório introduzir pelo menos uma linha não vazia. */
}

/**
 * \brief Função que trata operações de agrupamentos (STRINGS, BLOCOS E ARRAYS).
 *
 * @param arr a ser tratado.
 *
 * @param Stack s Stack onde vai ser guardado o resultado final (elem).
 */
void OpGroup(char *arr, Stack s){
    int i;
    STACK aux;
    char tokens[EXPRESSION_SIZE_MAX_TERM][EXPRESSION_SIZE_MAX_TERM];
    init_stack(&aux);
    putVars (aux.var,s->var);
    parsing_init(tokens);
    parsing(arr, &aux, tokens);
    free(arr);
    array r = malloc (sizeof(struct sarray));
    r->ARRAY= malloc ((2*(aux.top+1)+2)*sizeof(DADOS));
    r->front=0;
    r->tam=aux.top+1;
    r->size=(aux.top+1)*2 +2;
    i = aux.top;
    while(i>=0){
    r->ARRAY[i--] = pop(&aux);
    }
    parsing_finalize(tokens);
    makeDados(elem, ARRAY, r);
    push(elem, s);
    putVars (s->var,aux.var);
    free(aux.stck);
}



/**
 * \brief Função que executa operações de agrupamentos (STRINGS, BLOCOS E ARRAYS).
 *
 * @param token Token a ser interpretado como sendo uma STRING, BLOCO OU ARRAY.
 *
 * @param Stack s Stack onde vai ser guardado o resultado final (elem).
 */
void opAgrupamento(char *token, Stack s)
{

   if (isString(token)) {
   makeDados(elem, STRING, strndup((char *)(token) + 1, strlen(token)-2));
   push(elem,s);
   }
   else if (isBloco(token))
   {
   makeDados(elem2, BLOCK,strndup((char *)(token) + 1, strlen(token)-2))
   push(elem2,s);
   }
   else if (isArray(token))
   {
   OpGroup(strndup((char *)(token) + 1, strlen(token)-2), s);
   }
}


/**
 * \brief Função que trata operações numéricas.
 *
 * @param token Token a ser interpretado como sendo DECIMAL ou INTEIRO, para ser executado.
 *
 * @param Stack s Stack onde vai ser guardado o resultado final (elem).
 */
void opNumericas(char *token, Stack s)
{
    if (isintnum(token) == 0) {
    makeDados(elem, DOUBLE, atof(token));
    push(elem,s);
    }
    else {
    makeDados(elem, LONG, atol(token));
    push(elem,s);
    }
}


/**
 * \brief Esta é a função principal deste módulo.
 *
 * Faz a análise sintática das expressões, valida-as e manda executar as respetivas operações (calculate).
 *
 * @param expressionline Expressão a ser interpretada, validada e executada.
 */
void parsing(char *expressionline, Stack s, char tokens[][EXPRESSION_SIZE_MAX_TERM]) {
    unsigned int i;
    size_t numtokens = 0;
    for (i=0; expressionline[i]==' '; i++);
    expressionline=expressionline+i;
    numtokens = split_expression(tokens, expressionline);

    if (numtokens > 0) {
        for (i = 0; i < numtokens; i++) {
            if (isnumeric(tokens[i]))
            {
                opNumericas (tokens[i], s);
            }
            else if (isGroupSimbol(tokens[i]))
            {
                opAgrupamento(tokens[i], s);
            }
            else if (isvalidtoken(tokens[i]) )
            {
                if (isOpReader(tokens[i]) ) {
                    opInput(tokens[i], s);
                } else {
                    calculate(tokens[i], s);
                }
            }
        }
    }

}
