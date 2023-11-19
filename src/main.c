
#include "s21_calc.h"

int main() {
  char *string;
  string = malloc(256);
  Node *digit = NULL;
  Node *oper = NULL;
  strcpy(string, "2+2^2*2\0");
  for (; *string != '\0'; string++) {
    if (*string >= '0' && *string <= '9') {
      string = push_digit(string, &digit);
    }
    if (*string == ')') {
    } else if (is_letter(*string) || is_operator(*string)) {
      // printf("%c", *string);
      string = push_oper(string, &oper, &digit);
    }
  }
  while (oper != NULL) {
    calculate(&digit, &oper);
  }
  listprint(digit);
  // listprint(oper);
}

char *push_digit(char *string, Node **digit) {
  int i = 0;
  char digit_str[256] = "\0";
  while ((*string >= '0' && *string <= '9') || (*string == '.')) {
    digit_str[i] = *string;
    i++;
    string++;
    digit_str[i] = '\0';
  }
  push(digit, atof(digit_str), 0, 0);
  string--;
  return string;
}

char *push_oper(char *string, Node **oper, Node **digit) {
  Node temp_oper = {0, 0, 0, NULL};
  if (*string == '+') {
    temp_oper.type = s21_plus;
    temp_oper.priority = 0;
  }
  if (*string == '-') {
    temp_oper.type = s21_minus;
    temp_oper.priority = 0;
  }
  if (*string == '-' && (digit == NULL || *(string - 1) == '(')) {
    temp_oper.type = s21_unary_minus;
    temp_oper.priority = 2;
  }
  if (*string == '*') {
    temp_oper.type = s21_mul;
    temp_oper.priority = 1;
  }
  if (*string == '/') {
    temp_oper.type = s21_div;
    temp_oper.priority = 1;
  }
  if (*string == '^') {
    temp_oper.type = s21_pow;
    temp_oper.priority = 3;
  }
  if (*string == '(') {
    temp_oper.type = s21_bracket;
    temp_oper.priority = 5;
  }
  string = pars_func(&temp_oper, string);
  while (*oper && (*oper)->priority >= temp_oper.priority &&
         (*oper)->type != s21_bracket) {
    calculate(digit, oper);
    printf("calc\n");
  }
  push(oper, 0, temp_oper.type, temp_oper.priority);
  return string;
}

int calculate(Node **digit, Node **oper) {
  double result = 0;
  if ((*oper)->type < 8) {
    double num2 = (*digit)->data;
    pop(digit);
    double num1 = (*digit)->data;
    pop(digit);
    if ((*oper)->type == s21_plus) result = num1 + num2;
    if ((*oper)->type == s21_minus) result = num1 - num2;
    if ((*oper)->type == s21_mul) result = num1 * num2;
    if ((*oper)->type == s21_div) result = num1 / num2;
    if ((*oper)->type == s21_pow) result = pow(num1, num2);
  }
  pop(oper);
  push(digit, result, 0, 0);
  return 0;
}

char *pars_func(Node *temp_oper, char *string) {
  int i = 0;
  if (string == strstr(string, "sin")) {
    temp_oper->type = s21_sin;
    temp_oper->priority = 4;
    i = 2;
  }
  if (string == strstr(string, "cos")) {
    temp_oper->type = s21_cos;
    temp_oper->priority = 4;
    i = 2;
  }
  if (string == strstr(string, "tan")) {
    temp_oper->type = s21_tan;
    temp_oper->priority = 4;
    i = 2;
  }
  if (string == strstr(string, "asin")) {
    temp_oper->type = s21_asin;
    temp_oper->priority = 4;
    i = 3;
  }
  if (string == strstr(string, "acos")) {
    temp_oper->type = s21_acos;
    temp_oper->priority = 4;
    i = 3;
  }
  if (string == strstr(string, "atan")) {
    temp_oper->type = s21_atan;
    temp_oper->priority = 4;
    i = 3;
  }
  if (string == strstr(string, "ln")) {
    temp_oper->type = s21_sin;
    temp_oper->priority = 4;
    i = 1;
  }
  if (string == strstr(string, "log")) {
    temp_oper->type = s21_sin;
    temp_oper->priority = 4;
    i = 2;
  }
  if (string == strstr(string, "sqrt")) {
    temp_oper->type = s21_sin;
    temp_oper->priority = 4;
    i = 3;
  }
  if (string == strstr(string, "log")) {
    temp_oper->type = s21_mod;
    temp_oper->priority = 1;
    i = 2;
  }
  return string + i;
}