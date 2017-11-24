all:
	gcc -o exec main.c

run: all
	./exec

gdb: all
	gdb exec


clean:
	rm *~
	clear

cleanall:
	rm exec
	rm a.out
	rm *~
	clear
