#include <stdio.h>
#include <malloc.h>
#include "stack.h"

STACK* createStack(){
	STACK* newStack = (STACK*) malloc(sizeof(STACK));
	newStack->count = 0;
	newStack->top = NULL;

	return newStack;
}

int pop(STACK* st){
	int res;
	struct node* temp = st->top;

	if(st->count == 0){
		printf("Stack is empty!");
		return;
	}else{
		res = temp->data;
		st->top = temp->prev;
		free(temp);
		st->count--;

		return res;
	}
}

void push(STACK* st, int d){
	if(st->count == 0){
		struct node* newNode = (struct node*) malloc(sizeof(struct node));
		newNode->prev = NULL;
		newNode->data = d;

		st->top = newNode;
	}else{
		struct node* temp = (struct node*) malloc(sizeof(struct node));
		temp->prev = st->top;
		temp->data = d;
		st->top = temp;
	}

	st->count++;
	return;
}

int stackTop(STACK* st){
	if(st->count == 0){
		printf("Stack is empty!");
		return;
	}else{
		return st->top->data;
	}
}
