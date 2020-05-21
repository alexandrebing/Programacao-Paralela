#Área de um Conjunto de Mandelbrot usando OpenMP

Alexandre Bing e Fabrício Pujol

## Resumo

## Introdução

## O problema apresentado

### Definição

O Conjunto de Mandelbrot consiste em um fractal (figura geométrica não clássica onde as partes separadas repetem os padrões do todo completo) cuja razão é definida por uma condição inicial `z = c` e a iteração `z=z2+c` não diverege.

O desafio proposto consiste em paralelizar uma implementação sequencial de um programa que calcula a área de uma figura que pertence ao Conjunto de Mandelbrot, e realizar a comparação dos resultados encontrados de modo a se verificar o ganho de desempenho na comparação entre a versão sequencial e a paralelizada utilizando diferentes configurações do número de threads.

### Versão sequencial

A versão sequencial do programa foi fornecida inicialmente no enunciado do trabalho. A única alteração feita neste programa foi a inclusão de um novo laço externo que realiza uma iteração sobre o tamanho da área (em pontos) onde estaria inserido o fractal, que foi nossa compreensão sobre o que seria o número de NPOINTS que estamos incrementando gradualmente em 500 unidades.

Isso foi feito com base nos experimentos de aula que demonstraram essa como uma das alternativas para gerarmos todos os outputs com a execução do mesmo programa, e considerada a mais adequada tendo em vista o conhecimento e familiaridade dos autores deste relatório com _shellscript_.

Deste modo, a única alteração existente no código originalmente disponibilizado no enunciado foi:

```
int main(){

	...
	for (NPOINTS=500; NPOINTS <= 5000; NPOINTS += 500)
  	{

   		int numoutside = 0;
    	start = omp_get_wtime();
    	...

    	printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
    	fprintf(stderr, "%d %12.8f\n", NPOINTS, finish - start);
    }
}
```

### Versão paralelizada

Para a versão paralelizada, consideramos algumas alternativas de implementação.

A primeira, e mais óbivia, foi a paralelização de um dos laços com a diretiva `#pragma omp parallel`. Analizando cada um dos 3 laços originais, verificamos que a pior opção seria pela paralelização do laço mais interno, por não existir uniformidade na sua execução. Isso é explicado pela presença de uma linha de código que interrompe a execução deste laço (linha 51 do código `areasParalelo.c`, que não torna essa opção possível.

Da mesma forma, a paralelização do laço intermediário também não parecia uma boa alternativa por existir dependência dos valores de `i`, que é atualizado pelo laço mais externo. Isso implicaria a criação de threads para cada iteração do laço mais externo e trancar sua execução.

Portanto, a opção de paralelizar o laço mais externo pareceu a mais adequada e segura, desde que pudessemos garantir que a execução de _threads_ para cada laço não interferisse na execução de outra.

Por esta razão, foram inclusas na declaração da paralelização as variáveis pertencentes a cada instância do laço, de forma a impedir que a execução de uma thread atualizasse dados que interferissem na execução da outra.

```
int main()
{
  int NPOINTS;
  double area, error, ztemp;
  double start, finish;
  struct complex z, c;

  for (NPOINTS=500; NPOINTS <= 5000; NPOINTS += 500)
  {
  	...
```

Analizando o trecho do código sequencial acima, as variáveis mais óbvias, em primeira análise, eram as definidas para a própria iteração dos laços, `i`, `j` e `iter`. A variável `NPOINTS` é na verdade uma constante dentro de cada iteração do programa estamos testando, e não é alterada nunca. Da mesma forma, as variáveis `start` e `finish` são executadas apenas após a finalização da execução dos 3 laços aninhados. Além de `i`, `j`, e `iter`, os structs `z` e `c` de `complex` devem possuir instâncias dentro de cada thread, para que a execução de uma _thread_ com essas variáveis não sobrescreva os resultados em outras. Deste modo, nossa diretiva de paralelização ficou da seguinte forma:

```
#pragma omp parallel private(i, j, iter, c, z, ztemp)
{
	//PARALLELIZING EXTERNAL LOOP
	#pragma omp for
    for (i = 0; i < NPOINTS; i++)
            {
            ...
	
```

Faltava apenas a questão de como lidar com a variável `numOutside`, que é utilizada fora do laço paralelizado, mas increnentada no laço mais externo caso os número complexos testados não façam parte do Conjunto de Mandelbrot. Por se tratar apenas se uma operação de incrementar essa variável, testamos o comportamento do programa mantendo esta variável fora do mais externo laço e permitindo que as _threads_ a incrementássem a seu bel prazer.

Entretanto, ao testarmos verificamos que os resultados não batiam com os da versão sequencial, e a explicação estava justamente na atualização concorrente que as _threads_ estavam fazendo na mesma variável, o que possibilitou que ela não fosse incrementada corretamente.

Tal fenômeno se consistia em uma sessão crítica identificada no trecho de código abaixo:

```

``` 

## Resultados obtidos

### Gráficos de desempenho


