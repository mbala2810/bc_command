./project : postfix.o compare.o base_change.o math.o calc.o oprtrstack.o oprndstack.o add.o sub.o token.o infix.o multiply.o 1list.o div.o
	gcc oprtrstack.o base_change.o math.o calc.o compare.o postfix.o oprndstack.o power.o add.o sub.o token.o infix.o multiply.o 1list.o div.o -lm -o ./project
infix.o : infix.c calc.o oprtrstack.o token.o base_change.o postfix.o oprndstack.o add.o sub.o multiply.o 1list.o
	gcc -c infix.c
add.o : add.c
	gcc -c add.c
sub.o : sub.c add.o multiply.o
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
calc.o : calc.c token.h multiply.o add.o power.o sub.o compare.o div.o
	gcc -c calc.c
postfix.o : postfix.c calc.o token.o oprndstack.o
	gcc -c postfix.c
compare.o : compare.c integer.h
	gcc -c compare.c
power.o : power.c multiply.o
	gcc -c power.c
div.o : div.c multiply.o add.o sub.o compare.o
	gcc -c div.c
base_change.o : base_change.c div.o multiply.o add.o sub.o compare.o
	gcc -c base_change.c
math.o : math.c div.o multiply.o add.o sub.o
	gcc -c math.c
clean :
	rm *.o project
