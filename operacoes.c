/**
 * @file operacoes.c Contém as instruções destinadas às operações .
 */
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "assert.h"
#include "parser.h"
#include "stack.h"
#include "operacoes.h"
#include "stdlib.h"

/**
 *\brief Compara um inteiro com um elemento do tipo DADOS
 *
 *@param d1 Inteiro usado na comparação
 *
 *@param d2 Elemento usado na operação
 *
 *@returns -1 se o primeiro argumento é menor, 0 se são iguais e
 *  1 se o primeiro argumento é maior
 */
int compareDadosL (long d1, DADOS d2){
  switch (d2.tipo) {
    case (LONG):
        if (d1<d2.dados.LONG) return -1;
        else if (d1==d2.dados.LONG) return 0;
        else return 1;
    case (DOUBLE):
        if (((double)d1)<d2.dados.DOUBLE) return -1;
        else if (((double)d1)==d2.dados.DOUBLE) return 0;
        else return 1;
    case (CHAR):
        if (d1<(long)d2.dados.CHAR) return -1;
        else if (d1==(long)d2.dados.CHAR) return 0;
        else return 1;
    default: assert(1==0);
  }
}

/**
 *\brief Compara um double com um elemento do tipo DADOS
 *
 *@param d1 Double usado na comparação
 *
 *@param d2 Elemento usado na operação
 *
 *@returns -1 se o primeiro argumento é menor, 0 se são iguais e
 *  1 se o primeiro argumento é maior
 */
int compareDadosD (double d1, DADOS d2){
  switch (d2.tipo) {
    case (LONG):
        if (d1<(double)d2.dados.LONG) return -1;
        else if (d1==(double)d2.dados.LONG) return 0;
        else return 1;
    case (DOUBLE):
        if (d1<d2.dados.DOUBLE) return -1;
        else if (d1==d2.dados.DOUBLE) return 0;
        else return 1;
    case (CHAR):
        if (d1<(double)d2.dados.CHAR) return -1;
        else if (d1==(double)d2.dados.CHAR) return 0;
        else return 1;
    default: assert(1==0);
  }
}

/**
 *\brief Compara um char com um elemento do tipo DADOS
 *
 *@param d1 Char usado na comparação
 *
 *@param d2 Elemento usado na operação
 *
 *@returns -1 se o primeiro argumento é menor, 0 se são iguais e
 *  1 se o primeiro argumento é maior
 */
int compareDadosC (char d1, DADOS d2){
  switch (d2.tipo) {
    case (LONG):
        if ((long)d1<d2.dados.LONG) return -1;
        else if ((long)d1==d2.dados.LONG) return 0;
        else return 1;
    case (DOUBLE):
        if (((double)d1)<d2.dados.DOUBLE) return -1;
        else if (((double)d1)==d2.dados.DOUBLE) return 0;
        else return 1;
    case (CHAR):
        if (d1<d2.dados.CHAR) return -1;
        else if (d1==d2.dados.CHAR) return 0;
        else return 1;
    default: assert(1==0);
  }
}

/**
 *\brief Compara uma string com um elemento do tipo DADOS
 *
 *@param d1 String usada na comparação
 *
 *@param d2 Elemento usado na operação
 *
 *@returns -1 se o primeiro argumento é menor, 0 se são iguais e
 *  1 se o primeiro argumento é maior
 */
 int compareDadosS (char *d1, DADOS d2){
  assert(d2.tipo==STRING);
  int x=strcmp(d1,d2.dados.STRING);
  if (x>0) x=1;
  else if (x<0) x=-1;
  return x;
}

/**
 *\brief Compara dois elementos do tipo DADOS
 *
 *@param d1 Primeiro elemento usado na comparação
 *
 *@param d2 Segundo elemento usado na operação
 *
 *@returns -1 se o primeiro argumento é menor, 0 se são iguais e
 *  1 se o primeiro argumento é maior
 */
int compareDados (DADOS d1, DADOS d2){
  switch (d1.tipo) {
    case (LONG):
        return compareDadosL(d1.dados.LONG, d2);
    case (DOUBLE):
        return compareDadosD(d1.dados.DOUBLE, d2);
    case (CHAR):
        return compareDadosC(d1.dados.CHAR, d2);
    case (STRING):
        return compareDadosS(d1.dados.STRING, d2);
    default: assert(1==0);
  }
}

/**
 *\brief Concatena dois arrays
 *
 * Junta os elementos do segundo array ao fim do primeiro array.
 * Se o primeiro array não tiver espaço para colocar todos os elementos
 * duplica o espaço deste até ter.
 * No final liberta o espaço ocupado pelo seunndo array.
 *
 *@param a Primeiro array dado
 *
 *@param b Segundo array dado
 *
 *@param s Endereço da stack a alterar
 */
 void somaARRS (array a, array b, Stack s){
  int i;
  while ((a->tam + b->tam) < a->size) {
    a->size*=2;
    a->ARRAY=realloc (a->ARRAY, a->size* sizeof(DADOS));
  }
  for (i=0; i<b->tam;i++){
      a->ARRAY[(a->front+a->tam)]=b->ARRAY[(b->front+i)];
      (a->tam) ++;
  }
  free(b->ARRAY);
  free(b);
  makeDados(d,ARRAY, a)
  push(d,s);
}

/**
 *\brief Concatena duas strings
 *
 * Junta os elementos da segunda string ao fim d primeira string.
 * No final liberta o espaço ocupado pela segunda string.
 *
 *@param s1 Primeira string dado
 *
 *@param s2 Segunda string dado
 *
 *@param s Endereço da stack a alterar
 */
void somaSTRS (char *s1, char *s2, Stack s){
   strcat(s1, s2);
   free(s2);
   makeDados(d,STRING, s1);
   push(d,s);
}

/**
 *\brief Concatena um array com um elemento
 *
 * Acrescenta o elemento dado no início se o char dado for 'i', se for 'f' põe no final.
 *
 *@param c Carater que serve para saber se é para acrescentaro elemento no fim ou no início
 *
 *@param d Elemento a acrescentar
 *
 *@param a Array onde se adiciona o elemento
 *
 *@param s Endereço da stack a alterar
 */
void somaEARR (char c, DADOS d, array a, Stack s){
  if (a->tam==a->size){
    a->size*=2;
    a->ARRAY=realloc (a->ARRAY, a->size * (sizeof(DADOS)));
  }
  if (c=='i') {
    a->front = (a->front-1+a->size)%a->size;
    a->ARRAY[a->front]=d;
    a->tam++;}
  else a->ARRAY[(a->front + (a->tam++))%a->size]=d;
  makeDados(elem,ARRAY, a)
  push(elem,s);
}

/**
 *\brief Concatena uma string com um elemento
 *
 * Acrescenta o elemento dado no início se o char dado for 'i', se for 'f' põe no final.
 *
 *@param c Carater que serve para saber se é para acrescentaro elemento no fim ou no início
 *
 *@param d Elemento a acrescentar
 *
 *@param a Array onde se adiciona o elemento
 *
 *@param s Endereço da stack a alterar
 */
void somaEFSTR (char d, char *c, Stack s){
  int size =strlen(c);
  char *str = malloc ((size+1) *sizeof (char));
  int i;
  for (i=0;i<size;i++) str[i]=c[i];
  str[i++]=d;
  str[i]='\0';
  free (c);
  makeDados(elem,STRING, str)
  push(elem,s);
}

/**
 *\brief Concatena uma string com um elemento (fica no ínicio da string)
 *
 * Acrescenta o elemento dado no início da string.
 *
 *@param d Elemento a acrescentar
 *
 *@param a String onde se adiciona o elemento
 *
 *@param s Endereço da stack a alterar
 */
void somaEISTR (char d, char *c, Stack s){
  int size =strlen(c);
  char *str = malloc ((size+1) *sizeof (char));
  int i;
  str[0]=d;
  for (i=1;i<size+1;i++) str[i]=c[i-1];
  free (c);
  makeDados(elem,STRING, str)
  push(elem,s);
}

/**
 *\brief Auxiliar que preenche um determinado array a partir de outro array
 *
 *@param a Array recebido
 *
 *@param r Array preenchido
 */
void preencheARR (array a, array r){
  int i=0;
  while (i < a->tam) {
    r->ARRAY[(r->tam ++)]=a->ARRAY[(a->front+i)%a->size];
    i++;
  }
}

/**
 *\brief Concatena um array x vezes
 *
 *@param a Array a concatenar
 *
 *@param x Número de vezes a concatenar
 *
 *@param s Endereço da stack a alterar
 */
void concatARR (array a, long x, Stack s){
  array r = malloc (sizeof(struct sarray));
  r->ARRAY= malloc ((x*a->tam)*sizeof(DADOS));
  r->front=0;
  r->tam=0;
  r->size=x*(a->tam);
  while (x-->0) preencheARR(a,r);

  makeDados(elem, ARRAY, r);
  push(elem,s);
  free(a->ARRAY);
  free(a);
}

/**
 *\brief Auxiliar que preenche uma determinado string a partir de outra string
 *
 *@param a String recebida
 *
 *@param r String preenchida
 */
void preencheSTR (char *r, char *str, int x){
  int i;
  for (i=0; str[i]; i++)
    r[x++]=str[i];
}

/**
 *\brief Concatena uma string x vezes
 *
 *@param str String a concatenar
 *
 *@param x Número de vezes a concatenar
 *
 *@param s Endereço da stack a alterar
 */
void concatSTR (char *str, long x, Stack s){
  int len = strlen(str);
  int i=0;
  char *r = malloc((x*len+1)*sizeof(char));
  while (x>0){
    preencheSTR(r,str,i);
    i+=len;
    x--;
  }
  r[i]='\0';
  makeDados(elem, STRING, r);
  push(elem,s);
  free(str);
}

/**
 *\brief Verifica se a segunda string é prefixo da primeira
 *
 *@param s1 String principal
 *
 *@param s2 String que se verifica se é prefixo
 *
 *@param i Indíce a inciar a procura
 */
int prefixo (char *s1, char *s2, int i) {
  int r;
  for (r=0;s2[r]!='\0'&& s1[i]==s2[r]; r++) i++;
  if (s2[r]=='\0') r=0;
  else r=1;
  return r;
}

/**
 *\brief Verifica se a segunda string é sub-string da primeira
 *
 *@param ss String principal
 *
 *@param s2 String que se verifica se é sub-string
 */
int subSTR (char *ss, char *str){
    int i,r=-1;
    for (i=0; str[i]!='\0'&& r==-1; i++) if (!prefixo (str,ss,i)) r=i;
    if (ss[0]=='\0') r=i;
    return r;
}

/**
 *\brief Coloca na stack o resultado de verificar se a segunda string é sub-string da primeira
 *
 *@param ss String principal
 *
 *@param s2 String que se verifica se é sub-string
 *
 *@param s Endereço da stack a alterar
 */
void searchSubStr (char *ss, char *str, Stack s){
  int r = subSTR (ss,str);
  makeDados(e, LONG, r)
  push(e,s);
}

/**
 *\brief Obtem uma string modificada através de um inteiro
 *
 *@param str String principal
 *
 *@param w Inteiro que molda a string
 */
char *getString (char *str, int w){
  char *r = malloc ((w+1)* sizeof(char));
  int i;
  for (i=0;i<w; i++) r[i]=str[i];
  r[i]='\0';
  return r;
}

/**
 *\brief Separa uma string completa em diversas sub-strings
 *
 *@param ss String principal
 *
 *@param str Sub-String
 *
 *@param s Endereço da stack a ser preenchida
 */
void unwords (char *ss, char *str, Stack s){
  char *r;
  int w=subSTR(ss,str);
  int l = strlen(ss);
  array a = malloc (sizeof (struct sarray));
  a->ARRAY = malloc (5*sizeof(DADOS));
  a->size=5;
  a->tam=0;
  a->front=0;
  while (w>=0 && (*str)){
    r=getString (str, w);
    makeDados(elem, STRING,r);
    if (a->size==a->tam){
      a->size*=2;
      a->ARRAY=realloc (a->ARRAY, a->size * (sizeof(DADOS)));
    }
    a->ARRAY[a->tam++]=elem;
    str=str+w+l;
    w=subSTR(ss,str);
  }
  if (*str) {
    r=getString (str, (strlen(str)));
    makeDados(elem, STRING,r);
    if (a->size==a->tam){
      a->size*=2;
      a->ARRAY=realloc (a->ARRAY, a->size * (sizeof(DADOS)));
    }
    a->ARRAY[a->tam++]=elem;
  }
  makeDados(arr, ARRAY, a)
  push(arr,s);
}

/**
 *\brief Retorna o número resultante da operação dada
 *
 *@param x Primeiro número utilizado na operação efetuada
 *
 *@param y Segundo número utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@returns resultado de uma determinada operação
 */
double operaD(double x, double y, char c) {
  //  printf("Foi efetuada a operação: %g %c %g\n", y,c,x );
    switch (c) {
        case '+':
            return y + x;
        case '-':
            return y - x;
        case '*':
            return y * x;
        case '/':
            return y / x;
        case '#':
            return pow(y, x);
        default:
            assert (1 == 0);
    }
}

/**
 *\brief Retorna o número resultante da operação dada
 *
 *@param x Primeiro número utilizado na operação efetuada
 *
 *@param y Segundo número utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@returns resultado de uma determinada operação
 */
double operaL(long x, long y, char c) {
  //  printf("Foi efetuada a operação: %ld %c %ld\n", y,c,x );
    switch (c) {
        case '+':
            return y + x;
        case '-':
            return y - x;
        case '*':
            return y * x;
        case '/':
            return y / x;
        case '%':
            return y % x;
        case '#':
            return pow(y, x);
        default:
            assert (1 == 0);
    }
}

/**
 *\brief Retorna o carater resultante da operação dada
 *
 *@param x Primeiro carater utilizado na operação efetuada
 *
 *@param y Segundo carater utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@returns resultado de uma determinada operação
 */
char operaC(char x, char y, char c) {
  //  printf("Foi efetuada a operação: %c %c %c\n", y,c,x );
    switch (c) {
        case '+':
            return y + x;
        case '-':
            return y - x;
        case '*':
            return y * x;
        case '/':
            return y / x;
        case '%':
            return y % x;
        case '#':
            return pow(y, x);
        default:
            assert (1 == 0);
    }
}
/**
 *\brief Efetua operações entre strings e longs
 *
 *@param str String usada na operação
 *
 *@param x Inteiro usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaSL (char w,char *str, long x, char c, Stack s){
  switch (c){
    case '+':
      if (w=='i') somaEISTR((char)x, str, s);
      else somaEFSTR((char)x, str, s);
      break;    case '*': concatSTR(str,x,s); break;
    case '#': break;
    case '/': break;
  }
}

/**
 *\brief Efetua operações entre strings e doubles
 *
 *@param str String usada na operação
 *
 *@param x Double usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaSD (char w, char *str, double x, char c, Stack s){
  switch (c){
    case '+':
      if (w=='i') somaEISTR((char)x, str, s);
      else somaEFSTR((char)x, str, s);
      break;
    case '*': concatSTR(str,(long)x,s); break;
    default: break;
  }
}

/**
 *\brief Efetua operações entre strings e chars
 *
 *@param str String usada na operação
 *
 *@param x Char usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaSC (char w,char *str, char x, char c, Stack s){
  switch (c){
    case '+':
      if (w=='i') somaEISTR((char)x, str, s);
      else somaEFSTR((char)x, str, s);
      break;
    case '*': concatSTR(str,(long)x,s); break;
    default: break;
  }
}

/**
 *\brief Efetua operações entre strings
 *
 *@param str Primeira string usada na operação
 *
 *@param x Segunda string usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaSS (char *str, char *x, char c, Stack s){
  switch (c){
    case '+': somaSTRS(x, str, s);break;
    case '#': searchSubStr(str,x,s);break;
    case '/': unwords(str,x,s); break;
    case '*': break;
  }
}


/**
 *\brief Efetua operações entre strings e arrays
 *
 *@param str String usada na operação
 *
 *@param x Array usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaSA (char *str, array x, char c, Stack s){
  assert (c=='+');
  makeDados(elem, STRING, str)
  somaEARR('f',elem, x, s);
}

/**
 *\brief Efetua operações entre arrays e longs
 *
 *@param a Array usado na operação
 *
 *@param x Long usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaAL(char b,array a,long x,char c,Stack s){
  switch (c){
    case '+':{
      makeDados(elem, LONG,x)
      somaEARR(b,elem,a,s);break;
    }
    case '*': concatARR(a,x,s); break;
    default: break;
  }
}

/**
 *\brief Efetua operações entre arrays e doubles
 *
 *@param a Array usado na operação
 *
 *@param x Double usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaAD(char b,array a,double x,char c,Stack s){
  switch (c){
    case '+':{
      makeDados(elem, DOUBLE,x)
      somaEARR(b,elem,a,s);break;
    }
    case '*': concatARR(a,(long)x,s); break;
    default: break;
  }
}

/**
 *\brief Efetua operações entre arrays e chars
 *
 *@param a Array usado na operação
 *
 *@param x Long usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaAC(char b,array a,long x,char c,Stack s){
  switch (c){
    case '+':{
      makeDados(elem, CHAR,x)
      somaEARR(b,elem,a,s);break;
    }
    case '*': concatARR(a,(long)x,s); break;
    default: break;
  }
}

/**
 *\brief Efetua operações entre arrays e strings
 *
 *@param a Array usado na operação
 *
 *@param x String usada na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaAS(char b,array a,char *x,char c,Stack s){
  switch (c){
    case '+':{
      makeDados(elem, STRING,x)
      somaEARR(b,elem,a,s);break;
    }
    default: break;
  }
}

/**
 *\brief Efetua operações entre arrays
 *
 *@param a Array usado na operação
 *
 *@param x Array usado na operação
 *
 *@param c Carater correspondente à operação
 *
 *@param s Endereço da stack a alterar
 */
void operaAA(array a,array x,char c,Stack s){
  assert(c=='+');
  int i;
  while ((x->tam + a->tam) < x->size) {
    x->size*=2;
  //  x->ARRAY=realloc (x->ARRAY, x->size* sizeof(DADOS));
  }
  for (i=0; i<a->tam;i++){
      x->ARRAY[(x->front+x->tam)]=a->ARRAY[(a->front+i)];
      (x->tam) ++;
  }
  free(a->ARRAY);
  free(a);
  makeDados(d,ARRAY, x)
  push(d,s);
}

/**
 *\brief Coloca na stack um elemento após operar sobre os dois elementos dados(sendo o primeiro um long)
 *
 *@param x Primeiro elemento da stack utilizado na operação efetuada
 *
 *@param op2 Segundo elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opBINLONG(long x,DADOS op2, char c, Stack s){
   switch (op2.tipo) {
       case (LONG): {
           makeDados (x1, LONG, operaL(x,op2.dados.LONG, c))
           push(x1,s); break;
       }
       case (DOUBLE): {
           makeDados (x2, DOUBLE, operaD((double) x, op2.dados.DOUBLE, c))
           push(x2,s); break;
       }
       case (CHAR): {
           makeDados (x3, LONG, operaL(x, (long) op2.dados.CHAR, c))
           push(x3,s); break;
       }
       case (STRING): operaSL('f',op2.dados.STRING, x,c,s);break;
       case (ARRAY): operaAL('f',op2.dados.ARRAY, x,c,s);break;
       default: break;
   }
}

 /**
  *\brief Coloca na stack um elemento após operar sobre os dois elementos dados(sendo o primeiro um double)
  *
  *@param x Primeiro elemento da stack utilizado na operação efetuada
  *
  *@param op2 Segundo elemento da stack utilizado na operação efetuada
  *
  *@param c Operação a ser efetuada
  *
  *@param s Endereço da stack a alterar
  */
void opBINDOUBLE (double x, DADOS op2, char c, Stack s){
   switch (op2.tipo) {
       case (LONG): {
           makeDados (x1, DOUBLE, operaD(x, (double) op2.dados.LONG, c))
           push(x1,s); break;
       }
       case (DOUBLE): {
           makeDados (x2, DOUBLE, operaD(x, op2.dados.DOUBLE, c))
           push(x2,s); break;
       }
       case (CHAR): {
           makeDados (x3, DOUBLE, operaD(x, (char) op2.dados.CHAR, c))
           push(x3,s); break;
       }
       case (STRING): operaSD('f',op2.dados.STRING, x,c,s);break;
       case (ARRAY): operaAD('f',op2.dados.ARRAY, x,c,s);break;
       default: break;
   }
}

/**
 *\brief Coloca na stack um elemento após operar sobre os dois elementos dados(sendo o primeiro um long)
 *
 *@param x Primeiro elemento da stack utilizado na operação efetuada
 *
 *@param op2 Segundo elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opBINCHAR (char x, DADOS op2, char c, Stack s){
   switch (op2.tipo) {
       case (LONG): {
           makeDados (x1, LONG, operaL((long) x,op2.dados.LONG, c))
           push(x1,s); break;
       }
       case (DOUBLE): {
           makeDados (x2, DOUBLE, operaD((double)x, op2.dados.DOUBLE, c))
           push(x2,s); break;
       }
       case (CHAR): {
           makeDados (x3, CHAR, operaC(x, op2.dados.CHAR, c))
           push(x3,s); break;
       }
       case (STRING): operaSC('f',op2.dados.STRING, x,c,s);break;
       case (ARRAY): operaAC('f',op2.dados.ARRAY, x,c,s);break;
       default:break;
   }
}

/**
 *\brief Altera a stack após operar sobre os dois elementos dados(sendo o primeiro uma string)
 *
 *@param x Primeiro elemento da stack utilizado na operação efetuada
 *
 *@param op2 Segundo elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opBINSTRING (char *x, DADOS op2, char c, Stack s){
  switch (op2.tipo) {
      case (LONG):  operaSL('i',x,op2.dados.LONG,c,s); break;
      case (DOUBLE):operaSD('i',x,op2.dados.LONG,c,s); break;
      case (CHAR): operaSC('i',x,op2.dados.CHAR,c,s); break;
      case (STRING): operaSS(x,op2.dados.STRING,c,s); break;
      case (ARRAY): operaSA(x,op2.dados.ARRAY,c,s);break;
      default: break;
  }
}

/**
 *\brief Altera a stack após operar sobre os dois elementos dados(sendo o primeiro uma string)
 *
 *@param x Primeiro elemento da stack utilizado na operação efetuada
 *
 *@param op2 Segundo elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opBINARRAY (array a, DADOS op2, char c, Stack s){
  switch (op2.tipo) {
      case (LONG):  operaAL('i',a,op2.dados.LONG,c,s); break;
      case (DOUBLE): operaAD('i',a,op2.dados.LONG,c,s); break;
      case (CHAR): operaAC('i',a,op2.dados.CHAR,c,s); break;
      case (STRING): operaAS('i',a,op2.dados.STRING,c,s); break;
      case (ARRAY): operaAA(a,op2.dados.ARRAY,c,s); break;
      default: break;
  }
}

/**
 *\brief Copia um determinado bloco de instruções
 *
 *@param b Bloco a ser copiado
 *
 *@returns célula de memória com uma cópia do bloco
 */
char * copiaBlock (char * b){
  char * s= malloc((strlen(b)+1)*sizeof(char));
  int i;
  for (i =0; b[i]; i++) s[i]=b[i];
  s[i]='\0';
  return s;
}

/**
 *\brief Aplica o conteúdo imposto pelo bloco b ao array a
 *
 *@param a Elemento a ser alterado
 *
 *@param b Bloco fornecido
 *
 *@param s Endereço da stack a alterar
 *
 *@returns array a alterado consoante bloco b
 */
void applyARRAY(array a, char *b, Stack s){
  int i,aux=0;
  char * cena=NULL;
  array arr = malloc(sizeof(struct sarray));
  arr->ARRAY = malloc(20 * sizeof(DADOS));
  arr->tam = 0;
  arr->size = 20;
  arr->front = 0;
  DADOS elem;
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  STACK x;
  init_stack(&x);
  putVars (x.var,s->var);
  for (i = 0; i < a->tam; i++)
  {
      cena = copiaBlock(b);
      x.top=-1;
      elem = a->ARRAY[(a->front+i)%a->size];
      push(elem,&x);
      parsing_init(tokens);
      parsing(cena,&x,tokens);
      aux=x.top;
      while (x.top>=0){
        if (arr->tam==arr->size){
        arr->size*=2;
        arr->ARRAY= realloc(arr->ARRAY, arr->size * sizeof(DADOS));
        }
        elem=pop(&x);
        arr->ARRAY[(arr->tam)+1+x.top] = elem;
      }
      arr->tam+=aux+1;
  }
  makeDados(elem2, ARRAY, arr);
  push(elem2, s);
  putVars (s->var,x.var);
}

/**
 *\brief
 *
 *@param s String fornecida
 *
 *@param c Char que vai ser acrescentado à string
 *
 *@returns array a alterado consoante bloco b
 */
void acrescentaChar(char * s, char c){
  int x=strlen(s);
  s[x++]=c;
  s[x]='\0';
}

/**
 *\brief Aplica o conteúdo imposto pelo bloco b ao string a
 *
 *@param a Elemento a ser alterado
 *
 *@param b Bloco fornecida
 *
 *@param s Endereço da stack a alterar
 *
 *@returns string a alterado consoante bloco b
 */
void applySTRING(char *a, char *b, Stack s){
  int i;
  char*cena = NULL;
  char * str= malloc ((strlen(a)+1)*sizeof(char));
  str[0]='\0';
  char word;
  DADOS elem;
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  STACK x;
  init_stack(&x);
  putVars (x.var,s->var);
  for (i = 0; i < (int)strlen(a); i++)
  {
    cena = copiaBlock(b);
    word = a[i];
    makeDados(letter,CHAR,word)
      push(letter,&x);
      parsing(cena,&x,tokens);
      elem=pop(&x);
      assert(elem.tipo==CHAR);
      acrescentaChar(str, elem.dados.CHAR);
  }
  makeDados(elem2, STRING, str);
  push(elem2, s);
  putVars (s->var,x.var);

}

/**
 *\brief Reira o conteúdo imposto pelo bloco b ao array a
 *
 *@param a Elemento a ser alterado
 *
 *@param b Bloco fornecida
 *
 *@param s Endereço da stack a alterar
 *
 *@returns array alterado consoante bloco b
 */
void foldARRAY (array a, char *b, Stack s){
  STACK x; char * cena=NULL;
  init_stack(&x);
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  putVars (x.var,s->var);
  push(a->ARRAY[a->front],&x);
  a->front=(a->front+1)%a->size;
  while (--a->tam>0){
    push(a->ARRAY[a->front],&x);
    a->front=(a->front+1)%a->size;
    cena= copiaBlock(b);
    parsing(cena,&x,tokens);
  }
  push(pop(&x), s);
  free(x.stck);
  putVars (s->var,x.var);
}

/**
 *\brief Altera a stack após operar sobre os dois elementos dados(sendo o primeiro um bloco)
 *
 *@param b Primeiro elemento da stack utilizado na operação efetuada
 *
 *@param op2 Segundo elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opBINBLOCK (char * b, DADOS op2, char c, Stack s){
  switch (c) {
    case '*':
      assert(op2.tipo==ARRAY);
      foldARRAY(op2.dados.ARRAY, b,s);
      break;
    case('%'):
      {
        if (op2.tipo == ARRAY)
           applyARRAY(op2.dados.ARRAY,b,s);
        else if (op2.tipo == STRING)
           applySTRING(op2.dados.STRING,b,s);
        break;
      }
    default: break;

  }
}

/**
  *\brief Coloca na stack um elemento após operar sobre os dois elementos dados
  *
  *@param op1 Primeiro elemento da stack utilizado na operação efetuada
  *
  *@param op2 Segundo elemento da stack utilizado na operação efetuada
  *
  *@param c Operação a ser efetuada
  *
  *@param s Endereço da stack a alterar
  */
void opBIN(DADOS op1, DADOS op2, char c, Stack s) {
     switch (op1.tipo) {
         case (LONG):
             opBINLONG(op1.dados.LONG, op2,c,s);break;
         case (DOUBLE):
             opBINDOUBLE (op1.dados.DOUBLE, op2, c,s);break;
         case (CHAR):
             opBINCHAR (op1.dados.CHAR, op2, c,s);break;
         case (STRING):
             opBINSTRING (op1.dados.STRING, op2, c,s);break;
         case (ARRAY):
             opBINARRAY (op1.dados.ARRAY, op2, c,s);
             break;
         case (BLOCK):
             opBINBLOCK (op1.dados.BLOCK, op2, c, s); break;
     }
 }

/**
 *\brief Coloca na stack um elemento após operar sobre aquele que lhe é dado
 *
 *@param op1 Primeiro elemento da stack utilizado na operação efetuada
 *
 *@param op2 Segundo elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 */
void opBIT(DADOS op1, DADOS op2, char c, Stack s) {
    TIPO t1 = op1.tipo, t2 = op2.tipo;
    assert (t1 == LONG && t2 == LONG);
    long v1 = op1.dados.LONG, v2 = op2.dados.LONG;
//    printf("Foi efetuada a operação: %ld %c %ld\n", v2,c,v1);
    switch (c) {
        case '&': {
            makeDados (d1, LONG, v1 & v2)
            push(d1,s); break;
        }
        case '|': {
            makeDados (d2, LONG, v1 | v2)
            push(d2,s); break;
        }
        case '^': {
            makeDados (d3, LONG, v1 ^ v2)
            push(d3,s); break;
        }
        default: break;
    }
}

void makeRange (int x, Stack s){
  int i;
  array a=malloc(sizeof (struct sarray));
  a->ARRAY=malloc (x* sizeof(DADOS));
  a->tam=x;
  a->size=x;
  a->front=0;
  for (i=0;i<x;i++){
    makeDados (ind, LONG, i)
    a->ARRAY[i]=ind;
  }
  makeDados(arr, ARRAY, a)
  push(arr,s);
}

/**
 *\brief Coloca na stack um elemento após operar sobre o inteiro que lhe é dado
 *
 *@param x Inteiro (long) utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUNLONG(long x, char c, Stack s){
//  printf("Foi efetuada a operação: %ld %c\n", x,c);
  switch (c) {
      case ')': {
          makeDados (x1, LONG, x + 1);
          push(x1,s); break;
      }
      case '(': {
          makeDados (x2, LONG, x - 1);
          push(x2,s); break;
      }
      case '~': {
          makeDados (x3, LONG, ~x);
          push(x3,s); break;
      }
      case 'f': {
          makeDados (x4, DOUBLE, (double) x);
          push(x4,s); break;
      }
      case 'c': {
          makeDados (x5, CHAR, (char) x);
          push(x5,s); break;
      }
      case 's': {
          char str[256];
          sprintf(str, "%ld", x);
          makeDados (x6, STRING, strdup(str));
          push(x6,s); break;
      }
      case ',': makeRange(x,s); break;
      default: break;
  }
}

/**
 *\brief Coloca na stack um elemento após operar sobre o double que lhe é dado
 *
 *@param x Double utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUNDOUBLE(double x, char c, Stack s){
//  printf("Foi efetuada a operação: %g %c\n", x,c);
  switch (c) {
      case ')': {
          makeDados (x1, DOUBLE, x + 1);
          push(x1,s); break;
      }
      case '(': {
          makeDados (x2, DOUBLE, x - 1);
          push(x2,s); break;
      }
      case 'i': {
          makeDados (x3, LONG, (long) x);
          push(x3,s); break;
      }
      case 'c': {
          makeDados (x4, CHAR, (char) x);
          push(x4,s); break;
      }
      case 's': {
          char str[256];
          sprintf(str, "%lf", x);
          makeDados (x5, STRING, strdup(str));
          push(x5,s); break;
      }
      default: break;
  }
}

/**
 *\brief Coloca na stack um elemento após operar sobre o carater que lhe é dado
 *
 *@param x Carater utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUNCHAR (char x, char c, Stack s){
//  printf("Foi efetuada a operação: %c %c\n", x,c);
  switch (c) {
      case ')': {
          makeDados (x1, CHAR, x+1);
          push(x1,s); break;
      }
      case '(': {
          makeDados (x2, CHAR, x-1);
          push(x2,s); break;
      }
      case 'i': {
          makeDados (x3, LONG, (long) x);
          push(x3,s); break;
      }
      case 'f': {
          makeDados (x4, DOUBLE, (double) x);
          push(x4,s); break;
      }
      case 's': {
          char str[2];
          str[0] = x;
          str[1] = '\0';
          makeDados (x5, STRING, strdup(str));
          push(x5,s); break;
      }
      default: break;
  }
}

/**
  *\brief Retira um char do inicio da string
  *
  *@param x String inicialmente atribuida
  *
  *@param s Endereço da stack a alterar
  */
void tiraCharI (char *x, Stack s){
  char r = x[0];
  int i;
  for (i=0; x[i+1];i++) x[i]=x[i+1];
  x[i]='\0';
  makeDados(elem1,STRING, x);
  push(elem1,s);
  makeDados(elem2, CHAR, r);
  push(elem2,s);
}

/**
  *\brief Retira um char do fim da string
  *
  *@param x String inicialmente atribuida
  *
  *@param s Endereço da stack a alterar
  */
void tiraCharF (char *x, Stack s){
  int i;
  for (i=0; x[i];i++);
  i--;
  char r=x[i];
  x[i]='\0';
  makeDados(elem1,STRING, x);
  push(elem1,s);
  makeDados(elem2, CHAR, r);
  push(elem2,s);
}

/**
 *\brief Altera a stack após operar sobre a string que lhe é dada
 *
 *@param x String utilizada na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUNSTRING (char *x, char c, Stack s){
//  printf("Foi efetuada a operação: %s %c\n", x,c);
  switch (c) {
      case 'i': {
          makeDados (x1, LONG, atol(x));
          push(x1,s); break;
      }
      case 'f': {
          makeDados (x2, DOUBLE, atof(x));
          push(x2,s); break;
      }
      case 'c': {
          makeDados (x3, CHAR, x[0]);
          push(x3,s); break;
      }
      case ',':{
        makeDados(x4,LONG, strlen(x))
        push(x4,s);break;
      }
      case '(':{
        tiraCharI (x,s);break;
      }
      case ')':{
        tiraCharF(x,s);break;
      }
      default: break;
  }
}


/**
 *\brief Altera a stack após operar sobre o array que lhe é dado
 *
 *@param a Array utilizada na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUNARRAY (array a, char c, Stack s){
  DADOS d;
  switch (c){
    case('('):
      assert((a->tam)-- > 0);
      d=a->ARRAY[a->front];
      a->front=(a->front +1)%a->size;
      makeDados(e1, ARRAY, a)
      push(e1,s);
      push(d,s);break;
    case (')'):
      assert((a->tam)-- > 0);
      d=a->ARRAY[(a->front+a->tam)%a->size];
      makeDados(e2, ARRAY, a)
      push(e2,s);
      push(d,s);break;
    case (','):{
      makeDados(e, LONG, a->tam)
      push(e,s); break;
    case ('~'):{
      int i;
      for (i=0;i<a->tam; i++)
        push(a->ARRAY[(i+a->front)%a->size],s);
      break;
    default: break;
    }
    }
  }
}

/**
 *\brief Verifica se um elemento do tipo DADOS é igual zero
 *
 *@param d Elemento a analisar
 *
 *@returns 0 se for igual a 0 e diferente de 0 se for diferente de zero
 */
long isZero (DADOS d){
  switch (d.tipo){
    case (LONG): return d.dados.LONG;
    case (DOUBLE): return (long) d.dados.DOUBLE;
    case (CHAR): return ((long) (d.dados.CHAR));
    default: assert(1==0);
  }
}

/**
 *\brief Filtra a stack após operar sobre o array que lhe é dado
 *
 *@param a Array utilizada na operação efetuada
 *
 *@param b Bloco dado
 *
 *@param s Endereço da stack a alterar
 */
void filterARRAY(array a, char *b, Stack s){
  int i;
  array v = malloc(sizeof(struct sarray));
  char *cena=NULL;
  v->ARRAY = malloc(20 * sizeof(DADOS));
  v->tam = 0;
  v->size = 20;
  v->front = 0;
  DADOS elem;
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  STACK x;
  init_stack(&x);
  putVars (x.var,s->var);
  for (i = 0; i < a->tam; i++){
    elem = a->ARRAY[(a->front+i)%a->size];
    cena = copiaBlock(b);
      push(elem,&x);
      parsing(cena,&x,tokens);
      if (isZero(pop(&x)) != 0)
         v->ARRAY[v->tam++] = elem;
  }
  makeDados(elem2, ARRAY, v);
  push(elem2, s);
  putVars (s->var,x.var);
  free(a);
  free(cena);
}

/**
 *\brief Altera a stack após operar sobre o array que lhe é dado
 *
 *@param a Array utilizada na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void filterSTRING(char *a, char *b, Stack s){
  int i;
  array v = malloc(sizeof(struct sarray));
  char * cena=NULL;
  v->ARRAY = malloc(20 * sizeof(DADOS));
  v->tam = 0;
  v->size = 20;
  v->front = 0;
  char word;
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  STACK x;
  init_stack(&x);
  putVars (x.var,s->var);

  for (i = 0; i < (int)strlen(a); i++)
  {
    word = a[i];
    cena = copiaBlock(b);
    makeDados(letter,CHAR,word)
      push(letter,&x);
      parsing(cena,&x,tokens);
      if (isZero(pop(&x)) != 0)
         v->ARRAY[v->tam++] = letter;
  }
  makeDados(elem2, ARRAY, v);
  push(elem2, s);
  putVars (s->var,x.var);
  free(a);
  free(cena);
}

/**
 *\brief Ordena um array de acordo com o bloco dado
 *
 *@param a Array utilizada na operação efetuada
 *
 *@param b Bloco atribuido
 *
 *@param s Endereço da stack a alterar
 */
void orderARRAY (array arr, char *b, Stack s){
  int i, j, min; char * cena= NULL;
  DADOS elem, minC;
  STACK x;
  DADOS aux;
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  init_stack(&x);
  putVars (x.var,s->var);
  for (i = 0; i < (arr->tam) - 1; i++) {
        cena = copiaBlock(b);
        min=i;
        push(arr->ARRAY[(arr->front+i)%arr->size],&x);
        parsing(cena,&x,tokens);
        minC=pop(&x);
        for (j = i + 1; j < arr->tam; j++){
           cena = copiaBlock(b);
            push(arr->ARRAY[(arr->front+j)%arr->size],&x);
            parsing(cena,&x,tokens);
            elem = pop(&x);
            if (compareDados(elem,minC) == -1){
                min = j;
                minC=elem;
            }
        }
      aux=arr->ARRAY[(arr->front+min)%arr->size];
      arr->ARRAY[(arr->front+min)%arr->size]=arr->ARRAY[(arr->front+i)%arr->size];
      arr->ARRAY[(arr->front+i)%arr->size]=aux;
    }
    makeDados(a,ARRAY,arr)
    push(a,s);
    putVars (s->var, x.var);
    free(cena);
    free(x.stck);
}

/**
 *\brief Ordena uma string de acordo com o bloco dado
 *
 *@param arr String utilizada na operação efetuada
 *
 *@param b Bloco atribuido
 *
 *@param s Endereço da stack a alterar
 */
void orderSTRING (char *arr, char *b, Stack s){
  int i, j, min; char * cena= NULL;
  DADOS elem, minC;
  STACK x;
  char aux;
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  init_stack(&x);
  putVars (x.var,s->var);
    for (i = 0; i < (int)(strlen(arr)) - 1; i++) {
        cena = copiaBlock(b);
        min=i;
        makeDados(x1,CHAR,arr[i])
        push(x1,&x);
        parsing(cena,&x,tokens);
        minC=pop(&x);
        for (j = i + 1; j < (int)strlen(arr); j++){
            cena = copiaBlock(b);
            makeDados(x2,CHAR,arr[j])
            push(x2,&x);
            parsing(cena,&x,tokens);
            elem = pop(&x);
            if (compareDados(elem,minC) == -1){
                min = j;
                minC=elem;
            }
        }
    aux=arr[min];
    arr[min]=arr[i];
    arr[i]=aux;
    }
    makeDados(a,STRING,arr)
    push(a,s);
    putVars (s->var, x.var);
    free(cena);
    free(x.stck);
}

/**
 *\brief Altera a stack após operar sobre o bloco que lhe é dado
 *
 *@param b Bloco utilizada na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUNBLOCK(char *b, char c, Stack s)
{
  switch (c)
  {
  case (','):
  {
    DADOS d = pop(s);
    if (d.tipo == ARRAY)
       filterARRAY(d.dados.ARRAY,b,s);
    else if (d.tipo == STRING)
       filterSTRING(d.dados.STRING,b,s);
    break;
  case ('~'):
  {
    char* cena=copiaBlock(b);
    char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
    parsing(cena,s,tokens);
    break;
  }
  case('$'):
  {
    DADOS d = pop(s);
    if (d.tipo == ARRAY) orderARRAY (d.dados.ARRAY,b,s);
    else if (d.tipo == STRING) orderSTRING(d.dados.STRING,b,s);
    break;
  }
  default:
    break;
  }
  }
}
/**
 *\brief Coloca na stack um elemento após operar sobre aquele que lhe é dado
 *
 *@param op Elemento da stack utilizado na operação efetuada
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opUN(DADOS op, char c, Stack s) {
    TIPO t = op.tipo;
    switch (t) {
        case LONG:
            if (c=='i') push (op,s);
            else opUNLONG(op.dados.LONG,c ,s);
            break;
        case DOUBLE:
            if (c=='f') push (op,s);
            else opUNDOUBLE(op.dados.DOUBLE,c,s);
            break;
        case CHAR:
            if (c=='c') push (op,s);
            else opUNCHAR(op.dados.CHAR,c,s);
            break;
        case STRING:
            if (c=='s') push (op,s);
            else opUNSTRING(op.dados.STRING, c,s);
            break;
        case ARRAY:
            opUNARRAY(op.dados.ARRAY, c,s); break;
        case BLOCK:
            opUNBLOCK(op.dados.BLOCK, c, s);break;
    }
}

/**
 *\brief Altera a stack após operar sobre esta
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opSTACK (char c, Stack s){
  DADOS op1,op2;
  switch (c) {
    case '_':
        op1 = pop(s);
        push(op1,s);
        push(op1,s);
      //  printf("Foi duplicado o último elemento da stack\n");
        break;
    case ';':
        op1 = pop(s);
    //    printf("Foi retirado o último elemento da stack\n");
        break;
    case '\\':
        op1 = pop(s);
        op2 = pop(s);
        push(op1,s);
        push(op2,s);
      //  printf("A ordem dos dois elementos no topo da stack trocou\n");
        break;
    case '$':
        op1 = pop(s);
        if (op1.tipo==BLOCK) (opUNBLOCK(op1.dados.BLOCK,c,s));
        else {
        DADOS d= getElem(op1,s);
        push(d,s);
      //  printf("Foi duplicado o elemento na posição ");
      }
        break;
    case '@':
        op1 = pop(s);
        op2 = pop(s);
        DADOS op3 = pop(s);
        push(op2,s);
        push(op1,s);
        push(op3,s);
      //  printf("A ordem dos três elementos no topo da stack trocou\n");
        break;
    default: break;
  }
}


/**
 *\brief Coloca na stack elemento do array na posição x
 *
 *@param x posição no destino
 *
 *@param a array de elementos
 *
 *@param s Endereço da stack a alterar
 */
void getElemA (long x, array a, Stack s){
  assert (a->tam > x);
  push(a->ARRAY[(a->front+x)%a->size], s);
  //free(a);
}

/**
 *\brief Coloca na stack elemento da string na posição x
 *
 *@param x posição no destino
 *
 *@param a string de elementos
 *
 *@param s Endereço da stack a alterar
 */
void getElemS (long x, char *str, Stack s){
//  assert ((long)strlen(str) > x);
  makeDados(elem, CHAR, str[x]);
  push(elem, s);
  //free(str);
}

/**
 *\brief Coloca na stack x elementos do array
 *
 *@param x elementos a copiar
 *
 *@param a array de elementos
 *
 *@param s Endereço da stack a alterar
 */
void getElemsA(char c,long x, array a, Stack s){
  if (c=='f') a->front=(a->front+(a->tam-x))%a->size;
  a->tam=x;
  makeDados(arr, ARRAY, a)
  push(arr,s);
}

/**
 *\brief Coloca na stack x elementos do string
 *
 *@param x elementos a copiar
 *
 *@param a string de elementos
 *
 *@param s Endereço da stack a alterar
 */
void getElemsS(char c,long x, char *str, Stack s){
  long i,b=0;
  char *r=malloc (x*sizeof(char));
  if (c=='f') b=(long) strlen(str) - x;
  for (i=0;i<x;i++) r[i]=str[b+i];
  free(str);
  makeDados (elem, STRING, r)
  push(elem,s);
}

/**
 *\brief Altera a stack após operar sobre esta
 *
 *@param c Operação a ser efetuada
 *
 *@param s Endereço da stack a alterar
 */
void opLOGIC (char c, Stack s){
  DADOS op1, op2;
  makeDados (u,LONG, 1)
  makeDados (z,LONG, 0)
  switch (c) {
    case '=':
      op1 = pop(s);
      op2 = pop(s);
      if (op2.tipo==ARRAY) getElemA (op1.dados.LONG, op2.dados.ARRAY,s);
      else if ((op2.tipo==STRING) && (op1.tipo!=STRING)) getElemS (op1.dados.LONG, op2.dados.STRING,s);
      else if (compareDados(op1,op2)==0) push(u,s);
      else push(z,s);
      break;
    case '<':
      op1 = pop(s);
      op2 = pop(s);
      if (op2.tipo==ARRAY) getElemsA ('i',op1.dados.LONG, op2.dados.ARRAY,s);
      else if ((op2.tipo==STRING) && (op1.tipo!=STRING)) getElemsS ('i',op1.dados.LONG, op2.dados.STRING,s);
      else if (compareDados(op2,op1)==-1) push(u,s);
      else push(z,s);
      break;
    case '>':
      op1 = pop(s);
      op2 = pop(s);
      if (op2.tipo==ARRAY) getElemsA ('f',op1.dados.LONG, op2.dados.ARRAY,s);
      else if ((op2.tipo==STRING) && (op1.tipo!=STRING)) getElemsS ('f',op1.dados.LONG, op2.dados.STRING,s);
      else if (compareDados(op2,op1)==1) push(u,s);
      else push(z,s);
      break;
    case '?':
      op1 = pop(s);
      op2 = pop(s);
      DADOS op3 = pop(s);
      if (isZero(op3)) push(op2,s);
      else push(op1,s);
      break;
    case '!':
      op1= pop(s);
      if (isZero (op1)==0) push(u,s);
      else push(z,s);
      break;
    }
}

/**
 *\brief Altera a stack após operar sobre esta
 *@param c Operação a ser efetuada
 *
 *@param z Tipo de dados que pode assumir
 *
 *@param s Endereço da stack a alterar
 */
void opELOGIC (char c, DADOS z, Stack s){
  DADOS op1,op2;
  switch (c) {
    case '&':
      op1 = pop(s);
      op2 = pop(s);
      if (isZero(op1) && isZero(op2)) push(op1,s);
      else push(z,s);
      break;
    case '|':
      op1= pop(s);
      op2= pop(s);
      if (isZero(op1) && isZero(op2)) push(op2,s);
      else if (!isZero(op1) && !isZero(op2)) push(z,s);
      else if (!isZero(op1) && isZero(op2)) push(op2,s);
      else push(op1,s);
      break;
    case '<':
      op1= pop(s);
      op2= pop(s);
      if (compareDados(op2,op1)==-1) push(op2,s);
      else push(op1,s);
      break;
    case '>':
      op1= pop(s);
      op2= pop(s);
      if (compareDados(op2,op1)==1) push(op2,s);
      else push(op1,s);
      break;
  }
}

/**
 *\brief Coloca na stack o valor definido para a variável dada
 *
 *@param c Variável correspondente ao valor a pôr na stack
 *
 *@param s Endereço da stack a alterar
 */
void pushVar (char c, Stack s){
    push(s->var[c-'A'],s);
}

/**
 *\brief Separa string em várias secções
 *
 *@param b Recebe uma char específica
 *
 *@param s Endereço da stack a alterar
 */
void separateString (char b, char *str, Stack s){
  char c[]=" \r\t\n\v\f";
  if (b=='N') {c[0]='\n'; c[1]= '\0';}
  char *r;
  array a;
  a=malloc(sizeof(struct sarray));
  a->front=0;
  a->ARRAY= malloc (5* (sizeof (DADOS)));
  a->size=5;
  a->tam=0;
  r= strtok(str,c);
  while (r != NULL) {
    makeDados(elem,STRING,r)
    if (a->size==a->tam){
      a->size*=2;
      a->ARRAY=realloc (a->ARRAY, a->size * (sizeof(DADOS)));
    }
    a->ARRAY[(a->tam)++]= elem;
    r = strtok(NULL, c);
  }
  makeDados(arr, ARRAY, a)
  push (arr,s);
  //free(str);
}

void whileBlock(char * b, Stack s){
  DADOS elem=pop(s);
  char tokens[EXPRESSION_SIZE_MAX_TERMS][EXPRESSION_SIZE_MAX_TERM];
  char *cena=NULL;
  while (isZero(elem)){
    cena = copiaBlock(b);
    push(elem,s);
    parsing(cena,s,tokens);
    elem=pop(s);
  }
}

void calculateC (char c, Stack s){
  if (c=='w') {
    DADOS op=pop(s);
    assert(op.tipo==BLOCK);
    whileBlock(op.dados.BLOCK,s);
  }
  else if (issimbolin(c, STACK_SIMBOLS)) opSTACK (c,s); // se for uma operação da stack
  else if (issimbolin(c,LOGIC_SIMBOLS)) opLOGIC(c,s);
  else if (c >= 'A' && c <= 'Z') pushVar(c,s);
  else{
          DADOS op1 = pop(s);
          if (issimbolin(c, UNARY_SIMBOLS)) opUN(op1, c,s); // se for uma operação unária
          else {
              DADOS op2 = pop(s);
              if (issimbolin(c, BINBIT_SIMBOLS)) opBIT(op1, op2, c,s); // se for uma operação de bits
              else opBIN(op1, op2, c,s);// se for uma operação binária
          }
  }
}



/**
* \brief Copia um determinado array
*
*@param a Array dado para ser copiado
*
*
*@returns uma segunda cópia do array
**/
array copyARRAY (array a){
  array r=malloc(sizeof(struct sarray));
  r->ARRAY=malloc(a->size* sizeof(DADOS));
  r->size=a->size;
  r->tam=0;
  r->front=0;
  int i;
  for (i=0; i<a->tam; i++){
    r->ARRAY[r->tam]=a->ARRAY[(a->front+i)%a->size];
    (r->tam) ++;
  }
  return r;
}

/**
* \brief Designa o papel de função central.
*
* Esta função, altera o conteúdo da stack consoante o operador dado
*
*@param operator String que contêm a operação a executar
*
*@param s Endereço da stack a alterar
**/
void calculate(char *operator,Stack s) {

    if (strlen(operator) == 1) calculateC (operator[0],s);
    else {
      DADOS op1;
      makeDados (z,LONG, 0)
      if (operator[0]==':'){
        op1 = pop(s);
        push(op1,s);
        if (op1.tipo==ARRAY){
          array a= copyARRAY(op1.dados.ARRAY);
          makeDados(a1,ARRAY,a)
          s->var[operator[1]-'A']=a1;
        }
        else s->var[operator[1]-'A']=op1;
      }
      else if (operator[1]=='/') {
        op1=pop(s);
        separateString (operator[0], op1.dados.STRING, s);
      }
      else opELOGIC(operator[1],z,s);
    }
}
