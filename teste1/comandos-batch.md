# Conexão à rede Lab Grad

1. Conectar ao Sparta

		ssh portoalegre\\16180107@sparta.pucrs.br
		//senha de login do lab e moodle

2. Conectar ao Lab Grad
		
		ssh pp12722@grad.lad.pucrs.br
		//mesma senha
		
3. Ir até a pasta do repositório e dar pull

		cd git/Programacao-Paralela/
		git pull

# Criação e compilação do programa

1. Criar programa HelloWorld.c

	```
	#include <stdio.h>

	int main () {
		#pragma omp parallel
		printf("Hello World from OpenMP\n");
		return 0;
	}

	```

2. Compilar o programa

		gcc HelloWorld.c -o HelloWorld -fopenmp

# Criação do batchjob

1. Criar o batchjob

	```
	#!/bin/bash
	#PBS -m abe
	#PBS -V
	#PBS -l nodes=1:ppn=16:cluster-Grad,walltime=00:05:00
	#PBS -r n
	#PBS -j oe
	#PBS -d /home/pp12722/git/Programacao-Paralela/teste1
	################
	echo Running on host `hostname`
	echo
	echo Initial Time is `date`
	echo 
	echo Directori is `pwd`
	echo
	echo This jobs runs on the following nodes:
	echo `cat $PBS_NODEFILE | uniq`
	echo
	echo JOB_ID:
	echo `echo $PBS_JOBID`
	echo ###########
	./HelloWorld
	echo Final Time is `date`

	```

2. Rodar o batchjob com o comando
	
		qsub Helloworld.batchjob
		
3. Ver o estado do serviço

		qstat
		
4. Se o serviço é muito rapido a execução termina antes do qstat, então podemos rodar os 2 comandos junto

		qsub HelloWorld.batchjob ; qstat
		
5. Verificar o arquivo

		more HelloWorld.batchjob.o126443