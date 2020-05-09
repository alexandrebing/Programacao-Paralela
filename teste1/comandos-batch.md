1. Criar o batchjob

2. Rodar o batchjob com o comando
	
		qsub Helloworld.batchjob
		
3. Ver o estado do serviço

		qstat
		
4. Se o serviço é muito rapido a execução termina antes do qstat, então podemos rodar os 2 comandos junto

		qsub HelloWorld.batchjob ; qstat
		
5. Verificar o arquivo

		