target:	hw2

hw2_lib:	hw2_lib.h hw2_lib.c
			gcc -ansi -pedantic-errors -c hw2_lib.c -lm

hw2_main:	hw2_lib.h hw2_main.c
			gcc -ansi -pedantic-errors -c hw2_main.c -lm 


hw2:	hw2_main hw2_lib
		gcc hw2_lib.o hw2_main.c -o hw2 -lm

clean:
		rm hw2
