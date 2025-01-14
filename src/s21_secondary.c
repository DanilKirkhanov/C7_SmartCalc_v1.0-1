#include "s21_calc.h"

void push(Node **head, double data, int type, int priority) {
  Node *temp;
  temp = (Node *)malloc(sizeof(Node));
  if (temp == NULL) {
    printf("Stack is full");
    exit(1);
  }
  temp->next = *head;
  temp->data = data;
  temp->type = type;
  temp->priority = priority;
  *head = temp;
}


void pop(Node **head) {
  if (!head) {
    printf("Stack is empty");
    exit(1);
  } else {
    Node *tmp = *head;
    *head = (*head)->next;
    free(tmp);
  }
}

int is_operator(int c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(');
}

int is_letter(int c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
