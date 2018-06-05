comp: 
	@echo Compilando o programa
	gcc -o pi2 -fopenmp pi2.c

run:
	./pi2

.PHONY: comp run