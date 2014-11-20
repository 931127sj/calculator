#include <stdio.h>
#include <string.h>
#include "func.h"
#include "stack.h"

bool isOperators(char op){
	switch (op){
		case '*' : 
		case '/' : 
		case '+' : 
		case '-' : 
		case '(' : 
		case ')' :
			return true;
		break;
		default : 
			return false;
		break;
	}
}

char* toPostfix(char* pInfix){
	int i = 0, j = 0, x;
	char* pPostfix;
	char infix[100];
	char postfix[100];
	char token;

	STACK* op = createStack();
	strcpy(infix, pInfix);

	printf("%s", infix);

	while(infix[i] != '\0'){
		token = infix[i];
		printf("infix[%d] = %c\n", i, infix[i]);

		if(infix[i] == ' '){
			i++;
			continue;
		}
		else if(!isOperators(token)){ // number
			postfix[j] = infix[i];
			j++;
			postfix[j] = ' ';
			j++;
		}else{ // Operator
			printf("I'm Operator %c\n", infix[i]);
			if((op->count) == 0){ // empty stack
				printf("Stack is mine\n");
				push(op, i);
				printf("My value is %d\n", stackTop(op));
			}else{ // not empty
				printf("I want meet my freinds\n");
				int op1, op2;
				op1 = prioritize(infix, i);
				op2 = prioritize(infix, stackTop(op));

				if(op1 == 4){ // )
					while(1){
						op2 = prioritize(infix, stackTop(op));
						if(op2 == 3){ // (
							pop(op);
							break;
						}else{
							x = pop(op);
							postfix[j] = infix[x];
							j++;
						}
					}
				}else{ // not )
					if((op1 > op2) || (op2 == 3)){
						push(op, i);
					}else{
						x = pop(op);
						postfix[j] = infix[x];
						j++;

						while((op->count) != 0){
							op2 = prioritize(infix, stackTop(op));
							if(op1 > op2 || (op2 == 3)) break;
							else{
								x = pop(op);
								postfix[j] = infix[x];
								j++;
							}
						}
						push(op, i);
					}
				}
			}
		}
		i++;
	}

	while(!((op->count) == 0)){
		x = pop(op);
		postfix[j] = infix[x];
		j++;
	}

	strcpy(pPostfix, postfix);
	return pPostfix;
}

int prioritize(char* b, int idx){
	char oper = b[idx];
	switch(oper){
		case '+' :
		case '-' : 
			return 1;
		break;
		case '*' : 
		case '/' : 
			return 2;
		break;
		case '(' :
			return 3;
		break;
		case ')' : 
			return 4;
		break;
		default : 
			return -1;
		break;
	}
}

int calculate(int num1, char op, int num2){
	switch(op){
		case '*' : return (num1 * num2); break;
		case '/' : return (num1 / num2); break;
		case '+' : return (num1 + num2); break;
		case '-' : return (num1 - num2); break;
		default : break;
	}
}

int calc(char* postfix){
	int i = 0, j = 0, n;
	char num[5] = "";
	int operand1, operand2;
	int value;

	STACK* val = createStack();

	while(postfix[i]!= '\0'){
		if(postfix[i] == ' '){
			if(num[0] != '\0'){
				value = atoi(num);
				push(val, value);
				for(n = 0; n < 5; n++) num[n] = 0;
				j = 0;
			}
		}else{
			if(!isOperators(postfix[i])){
				num[j] = postfix[i];
				j++;
			}else{
				operand2 = pop(val);
				operand1 = pop(val);

				value = calculate(operand1, postfix[i], operand2);
				push(val, value);
			}
		}
		i++;
	}

	while(!((val->count) == 0)){
		value = pop(val);
	}

	return value;
}
