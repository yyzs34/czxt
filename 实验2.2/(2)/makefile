greeting:greeting.o myapp.o
	gcc greeting.o myapp.o -o greeting
myapp.o:myapp.c
	gcc -c myapp.c
greeting.o:greeting.c
	gcc -c greeting.c
clean:
	rm *.o greeting

