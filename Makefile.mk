make: copy_ssh 

comp-lab1: @echo Compilando lab1 
		   mpicc ex1.c -o lab1

comp-lab2: @echo Compilando lab1 
			mpicc ex2.c -o lab2

comp-lab3: @echo Compilando lab1 
 			mpicc ex3.c -o lab3

run-lab1: @echo Rodando lab1   	
		  mpirun --hostifle nome_hosts -np 4 -mca plm_rsh_no_tree_spawn 1 lab1

run-lab2:  @echo Rodando lab2
			mpirun --hostifle nome_hosts -np $(n) -mca plm_rsh_no_tree_spawn 1 lab2

run-lab3: @echo Rodando lab3 
		  mpirun --hostifle nome_hosts -np $(n) -mca plm_rsh_no_tree_spawn 1 lab3

copy-ssh: @echo Fazendo copia ssh 
		  scp -r ~ /Downloads/BOladao/labparelela lab@L307-4B:~/Downloads

ls-ssh: ssh l307-4B ls -la ~/Downloads/BOladao/labparelela

.PHONY: comp-lab1 comp-lab2 comp-lab3 run-lab1 run-lab2 run-lab3 copy-ssh ls-ssh 