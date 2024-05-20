#include "stack.h"
char *solv(char *Str_postfix, int *err, double *result) {
  double resul = 0;
  char Str_redused[256] = {0};  // сжимаем функции и ставим пробелы
  char Str_BPN[256] = {0};  // обратная польская нотация с пробелами
  *err = 0;  // для валидации
  Stack s = {0};
  *err = validation_srt(Str_postfix);  // валидация
  if (*err == 0) {
    string_reduction(Str_postfix, Str_redused);
    Back_polish_notation(Str_redused, s, Str_BPN);

    resul = calculation(Str_BPN, err);
    *result = resul;
  }
  strcpy(Str_postfix, Str_BPN);
  return Str_postfix;
}

int is_empty(Stack stack) { return stack.n == 0 ? 1 : 0; }
void push(Stack *stac, int number) {
  stac->a[stac->n] = number;
  stac->n++;
}
void push_double(Stack *stac, double num) {
  stac->number[stac->n] = num;
  stac->n++;
}
int pop(Stack *stack) {
  int result = stack->a[stack->n - 1];
  stack->a[stack->n - 1] = 0;
  stack->n--;
  return result;
}
double pop_double(Stack *stack) {
  double result = stack->number[stack->n - 1];
  stack->number[stack->n - 1] = 0;
  stack->n--;
  return result;
}
void print_stack(Stack stac) {
  for (int i = 0; i < stac.n; i++) printf("%c ", stac.a[i]);
  printf("\n");
}
char view(Stack stack) { return stack.a[stack.n - 1]; }
int priority(char operato_r) {
  int result = -1;
  if (operato_r == '(') result = 0;
  if (operato_r == ')') result = 1;
  if (operato_r == '+' || operato_r == '-') result = 2;
  if (operato_r == '*' || operato_r == '/' || operato_r == '%') result = 3;
  if (operato_r >= 97 && operato_r <= 122) result = 4;
  if (operato_r == '^') result = 5;
  return result;
}
/*перевод строки из инфиксной в обратную польскую нотацию
Pointer_Str_postfix -> Str_BPN
возврящает количество симолов записанное в строку Str_BPN
*/
int Back_polish_notation(char *Pointer_Str_postfix, Stack s, char *Str_BPN) {
  int num_place = 0;
  while (*Pointer_Str_postfix != end_srt) {
    if (!((*Pointer_Str_postfix > 47 && *Pointer_Str_postfix < 58) ||
          *Pointer_Str_postfix == '.' || *Pointer_Str_postfix == 'x') &&
        Str_BPN[num_place - 1] != ' ' && num_place) {
      Str_BPN[num_place++] = ' ';
    }
    if ((*Pointer_Str_postfix > 47 && *Pointer_Str_postfix < 58) ||
        *Pointer_Str_postfix == '.' || *Pointer_Str_postfix == 'x') {
      Str_BPN[num_place++] = *Pointer_Str_postfix;
    } else if (*Pointer_Str_postfix == '(') {
      push(&s, *Pointer_Str_postfix);
    } else if (*Pointer_Str_postfix == ')') {
      while (view(s) != '(') {
        if (Str_BPN[num_place - 1] != ' ') Str_BPN[num_place++] = ' ';
        Str_BPN[num_place++] = pop(&s);
      }
      if (Str_BPN[num_place - 1] != ' ') Str_BPN[num_place++] = ' ';
      pop(&s);
    } else if (is_empty(s) ||
               priority(view(s)) < priority(*Pointer_Str_postfix)) {
      push(&s, *Pointer_Str_postfix);
    } else if (priority(view(s)) >= priority(*Pointer_Str_postfix)) {
      while (priority(view(s)) >= priority(*Pointer_Str_postfix)) {
        if (Str_BPN[num_place - 1] != ' ') Str_BPN[num_place++] = ' ';
        Str_BPN[num_place++] = pop(&s);
      }
      if (Str_BPN[num_place - 1] != ' ') Str_BPN[num_place++] = ' ';
      push(&s, *Pointer_Str_postfix);
    }
    Pointer_Str_postfix++;
  }
  while (s.n != 0) {
    if (Str_BPN[num_place - 1] != ' ') Str_BPN[num_place++] = ' ';
    Str_BPN[num_place++] = pop(&s);
  }
  return num_place;
}
// удаление лишних символов из строчки  sin->s
void string_reduction(char *str_in, char *str_out) {
  int num = 0;
  if (*str_in == '-' || *str_in == '+') {
    *str_out = '0';
    str_out += 1;
    num = 1;
  }
  while (*str_in != end_srt) {
    num++;
    if ((*(str_in - 1) > 47 && *(str_in - 1) < 58) && *str_in == '(') {
      *str_out = '*';
      str_out += 1;
      num = 1;
    }
    if ((*str_in == '-' || *str_in == '+') && *(str_in - 1) == '(') {
      *str_out = '0';
      str_out += 1;
      num = 1;
    }
    if (*str_in == 'c' || *str_in == 't') {  // cos(x)->c tan(x)->t
      *str_out = *str_in;
      str_in += 2;
    } else if (*str_in == 'l' && *(str_in + 1) == 'n') {  // ln(x)->l
      *str_out = *str_in, str_in += 1;
    } else if (*str_in == 'a' && *(str_in + 1) == 's') {  // asin(x)->n
      *str_out = 'n', str_in += 3;
    } else if (*str_in == 'a' && *(str_in + 1) == 't') {  // atan(x)->n
      *str_out = 'y', str_in += 3;
    } else if (*str_in == 'a' && *(str_in + 1) == 'c') {  // acos(x)->A
      *str_out = 'A', str_in += 3;
    } else if (*str_in == 's' && *(str_in + 1) == 'q') {  // sqrt(x)->n
      *str_out = 'q';
      str_in += 3;
    } else if (*str_in == 'l' && *(str_in + 1) == 'o') {  // log(x)->g
      *str_out = 'g';
      str_in += 2;
    } else if (*str_in == 's' && *(str_in + 1) == 'i') {  // sin(x)->g
      *str_out = 's';
      str_in += 2;
    } else {
      *str_out = *str_in;
    }
    str_in += 1;
    str_out += 1;
  }
  str_out += 1;
  *str_out = 0;
  str_out -= num + 1;
}
// математические операции на стеке
double calculation(char *Str_BPN, int *err) {
  int error = 0;
  double result = 0;
  Stack calc = {0};

  while (*Str_BPN != 0 && !error) {
    if (*Str_BPN == 'x') {
      error = 1;
      break;
    }
    if (*Str_BPN != ' ') {
      if (*Str_BPN >= 48 && *Str_BPN < 58) {
        double result_num = 0.0;
        Str_BPN = srt_to_double(Str_BPN, &result_num);
        push_double(&calc, result_num);
      } else if (*Str_BPN < 65 || *Str_BPN == '^') {
        double num_2 = pop_double(&calc), num_1 = pop_double(&calc);
        push_double(&calc, func_calc(*Str_BPN, num_1, num_2, &error));
      } else {
        double num_11 = pop_double(&calc);
        push_double(&calc, func_calc_ext(*Str_BPN, num_11));
      }
    }
    Str_BPN++;
  }
  *err = error;
  result = pop_double(&calc);
  return result;
}
// переводит из строчки в дабл
char *srt_to_double(char *Str_BPN, double *result) {
  int lenth = (int)strcspn(Str_BPN, " \0");
  int point = (int)strcspn(Str_BPN, ". \0");
  if (lenth == point) lenth += 1;
  int power_10 = 0, flag = 0;
  // printf("lenth = %d",)
  while (lenth-- > 1) {
    if (*Str_BPN == '.') {
      Str_BPN += 1;
      flag = 1;
    }
    if (flag) power_10++;

    *result *= 10;
    *result += (*Str_BPN - 48);
    Str_BPN += 1;
  }
  // printf(" result=%lf ",*result);
  *result = *result * 1 / pow(10, power_10);
  return Str_BPN;
}
// +- % * /
double func_calc(char func, double num_1, double num_2, int *error) {
  double result = 0;
  if (func == '/' && num_2 == 0.0) *error = 1;
  if (func == '+') result = num_1 + num_2;
  if (func == '^') result = pow(num_1, num_2);
  if (func == '-') result = num_1 - num_2;
  if (func == '*') result = num_1 * num_2;
  if (func == '/' && num_2 != 0.0) result = num_1 / num_2;
  if (func == '%') {
    int mul = (int)num_1 / (int)num_2;
    result = num_1 - num_2 * mul;
  }

  return result;
}
// всякие функции
double func_calc_ext(char func, double num_1) {
  double result = 0;
  if (func == 'c') result = cos(num_1);
  if (func == 't') result = tan(num_1);
  if (func == 'n') result = asin(num_1);
  if (func == 'q') result = sqrt(num_1);
  if (func == 'g') result = log10(num_1);
  if (func == 's') result = sin(num_1);
  if (func == 'A') result = acos(num_1);
  if (func == 'y') result = atan(num_1);
  if (func == 'l') result = log(num_1);
  return result;
}
// функция валидации
int validation_srt(char *str) {
  int err = 0;
  char *str_rem = str;
  err = bracket(str_rem);
  if (err == 0) err = funk_brackets(str_rem);
  return err;
}
// валидация скобок()()()()
int bracket(char *str) {
  Stack bracket = {0};
  int err = 0;
  while (err != 1 && *str != 0) {
    if ((*str == ')' && is_empty(bracket)) == 1) err = 1;
    if (*str == '(') push(&bracket, '(');
    if (*str == ')' && !is_empty(bracket)) {
      int back_bracket = 0;
      back_bracket = pop(&bracket);
      if (back_bracket != '(') err = 1;
    }
    str += 1;
  }
  if (!is_empty(bracket)) err = 1;
  return err;
}
// валидация ()-что не пусто между
int funk_brackets(char *str) {
  int err = 0;
  int num = 0;
  while (err != 1 && *str != 0) {
    if (*str == '(' && *(str + 1) == ')') err = 1;
    if (*str == '(' && *(str + 1) != ')') {
      char *str_rem = str;
      num = 0;
      while (*str_rem != ')') {
        if (*str_rem > 47 && *str_rem < 58) num++;
        str_rem += 1;
      }
      if (err == 0) err = (num == 0);
    }
    str += 1;
  }
  return err;
}
