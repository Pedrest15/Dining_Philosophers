all:
	gcc -pthread -o DiningPhi *.c

run:
	./main

zip:
	zip dining_phi.zip Makefile *.c *.h *.pdf