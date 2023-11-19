#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int type;  // 0 это числа, буквы и символы соответствующая операция
  int priority;
  double data;  // если type 0, эта переменная будет заполнена
  struct Node *next;
} Node;

typedef enum {
  s21_num = 0,
  s21_X = 1,

  s21_plus = 2,   //
  s21_minus = 3,  //
  s21_mul = 4,    //
  s21_div = 5,    //
  s21_mod = 6,
  s21_pow = 7,      //
  s21_bracket = 8,  //

  s21_unary_minus = 9,  ///
  s21_sin = 10,
  s21_cos = 11,
  s21_tan = 12,
  s21_asin = 13,
  s21_acos = 14,
  s21_atan = 15,
  s21_sqrt = 16,
  s21_ln = 17,
  s21_log = 18,

} type_t;

void push(Node **head, double data, int type, int priority);
void listprint(Node *elem);
void pop(Node **head);
char *push_digit(char *string, Node **num);
char *push_oper(char *string, Node **oper, Node **push_digit);
int is_operator(int c);
int is_letter(int c);
char *pars_func(Node *temp_oper, char *string);
int calculate(Node **digit, Node **oper);