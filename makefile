all:
	gcc -o exec core.c main.c

run: all
	./exec

gdb: all
	gdb exec


clean:
	rm *~
	clear

cleanall:
	rm exec
	rm *~
	clear
