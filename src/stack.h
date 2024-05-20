#include <stdio.h>
#define Sos 256
#define end_srt 0
#include <math.h>
#include <string.h>

typedef struct {
  double number[Sos];
  char a[Sos];  // массив с данными
  int n;  // сколько элементов находится в стеке
} Stack;

char view(Stack stack);
void print_stack(Stack stac);
void push(Stack *stac, int number);
int pop(Stack *stack);
int is_empty(Stack stack);
int Back_polish_notation(char *Pointer_Str_postfix, Stack s, char *Str_BPN);
int priority(char operato_r);
void string_reduction(char *str_in, char *str_out);
char *srt_to_double(char *Str_BPN, double *result);
double calculation(char *Str_BPN, int *err);
void push_double(Stack *stac, double num);
double pop_double(Stack *stack);
double func_calc(char func, double num_1, double num_2, int *error);
double func_calc_ext(char func, double num_1);
int validation_srt(char *str);
int bracket(char *str);
int funk_brackets(char *str);
char *solv(char *Str_postfix, int *err, double *result);
