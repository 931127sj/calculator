#include <stdbool.h>

bool isOperators(char op);
char* toPostfix(char* infix);
int prioritize(char* b, int idx);
int calculate(int num1, char op, int num2);
int calc(char* postfix);
