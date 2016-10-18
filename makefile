./project : postfix.o calc.o oprtrstack.o oprndstack.o add.o sub.o token.o infix.o multiply.o 1list.o
	gcc oprtrstack.o calc.o postfix.o oprndstack.o add.o sub.o token.o infix.o multiply.o 1list.o -o ./project
infix.o : infix.c calc.o oprtrstack.o token.o postfix.o oprndstack.o add.o sub.o multiply.o 1list.o
	gcc -c infix.c
add.o : add.c
	gcc -c add.c
sub.o : sub.c
	gcc -c sub.c
token.o : token.c token.h 
	gcc -c token.c
oprtrstack.o : oprtrstack.c oprtrstack.h
	gcc -c oprtrstack.c
oprndstack.o : oprndstack.c oprndstack.h
	gcc -c oprndstack.c
1list.o : 1list.c integer.h
	gcc -c 1list.c
multiply.o : 1list.o multiply.c
	gcc -c multiply.c
calc.o : calc.c token.h multiply.o add.o sub.o
	gcc -c calc.c
postfix.o : postfix.c calc.o token.o oprndstack.o
	gcc -c postfix.c
