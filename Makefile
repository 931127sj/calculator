main : main.o func.o stack.o
	gcc -lm -o main main.o func.o stack.o
main.o : main.c func.h stack.h
	gcc -c main.c
func.o : func.c func.h stack.h
	gcc -c func.c
stack.o : stack.c stack.h
	gcc -c stack.c
