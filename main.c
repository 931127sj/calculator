#include <stdio.h>
#include "stack.h"
#include "func.h"

void main(int argc, char* argv[]){
	char input_val[5] = "";
	char infix[100];
	char postfix[100];
	char num[5];
	char token;
	STACK* op = createStack();

	int i = 0, j = 0, x, n;
	int res = 0;
	int operand1, operand2;

	printf("Write your equation. (term-by-term)(If you want exit, write 'end')\n");

	while(1){
		scanf("%s", input_val);
		if(input_val[0] == 'e' && input_val[1] == 'n' && input_val[2] == 'd'){
			infix[j-1] = '\0';
			break;	
		}

		for(i = 0; input_val[i] != '\0'; i++){
			infix[j] = input_val[i];
			j++;
		}
		infix[j] = ' ';
		j++;
	}

	printf("%s = ", infix);

	i = 0; j = 0;	
	while(infix[i] != '\0'){
        token = infix[i];
        if(infix[i] == ' '){
            i++;
            continue;
        }
        else if(!isOperators(token)){ // number
            postfix[j] = infix[i];
			j++;
			if(isOperators(infix[i+2]) || (infix[i+2] == '\0')){
				postfix[j] = ' ';
            	j++;
			}
        }else{ // Operator
            if((op->count) == 0){ // empty stack
                push(op, i);
            }else{ // not empty
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
							postfix[j] = ' ';
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
						postfix[j] = ' ';
						j++;

                        while((op->count) != 0){
                            op2 = prioritize(infix, stackTop(op));
                            if(op1 > op2 || (op2 == 3)) break;
                            else{
                                x = pop(op);
                                postfix[j] = infix[x];
                                j++;
								postfix[j] = ' ';
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
	    postfix[j] = ' ';
		j++;
    }
	postfix[j] = '\0';

	printf("%s = ", postfix);

	i = 0, j = 0;
	while(postfix[i]!= '\0'){
        if(postfix[i] == ' '){
            if(num[0] != '\0'){
                res = atoi(num);
                push(op, res);
                for(n = 0; n < 5; n++) num[n] = 0;
                j = 0;
            }
        }else{
            if(!isOperators(postfix[i])){
                num[j] = postfix[i];
                j++;
            }else{
                operand2 = pop(op);
                operand1 = pop(op);

                res = calculate(operand1, postfix[i], operand2);
                push(op, res);
            }
        }
        i++;
    }

    while(!((op->count) == 0)){
        res = pop(op);
    }

	printf("%d\nResult is %d\n", res, res);

	return;
}
