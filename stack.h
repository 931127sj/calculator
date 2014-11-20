#define MAX_NUMBER 10

struct node{
	int data;
	struct node* prev;
};

typedef struct stack{
	int count;
	struct node* top;
}STACK;

STACK* createStack();
int pop(STACK* st);
void push(STACK* st, int d);
int stackTop(STACK* st);
