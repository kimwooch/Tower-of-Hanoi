hanoi: hanoi.c list.o stack.o
	gcc -Wall -std=c11 hanoi.c list.o stack.o -o hanoi

list.o: list.c list.h
	gcc -std=c11 -Wall list.c -c

stack.o: stack.c stack.h list.h
	gcc -std=c11 -Wall stack.c -c

clean:
	rm -f *.o hanoi
