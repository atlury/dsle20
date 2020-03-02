# Toolchain

O toolchain nada mais é que uma cadeia de ferramentas, ou seja, é o conjunto de ferramentas que utilizamos para a compilação.

Esse processo de compilação, tomando como base a linguagem C, segue o seguinte protocolo:

* Pré-processamento;
* Compilação;
* _Assembly;_
* _Linking._

Em um primeiro momento são realizadas as atividades de pré-processamento, ou seja,  o pré-processador analisa todas as macros e definições criadas por um usuário e codifica elas, em código de linguagem C, técnicamente falando não precisamos de um pré-processador, no entanto ele promove uma certa facilidade pro programador. Por exemplo, seu uso mais comum é a diretiva inclusão de cabeçalhos:

```c
#include <stdio.h>
```

Em C/C++ todos os símbolos, isto é, funções, variáveis e etc, devem ser declarados antes de serem definitivamente utilizados pelo programa.  Eles não precisam necessariamente serem definidos, mas a declaração deve ocorrer antes, pois o compilador precisa saber que eles existem em algum lugar, separar as declarações das definições, além de boa práticas é um uso clássico de cabeçalhos.

Nesse processo, o pré-porcessador então copia todas essas definições para o local onde vc deseja utilizá-las, além disso o pré-processador inclui algumas facilidades de compilação condicional. Um uso bem comum que encontramos em diversos headers, são os header guards, que previnem múltiplas definições quando um arquivo é incluso varias vezes. Outra função, é a possibilidade de inserir arquivos de acordo com o sistema operacional ou arquitetura de hardware por exemplo.

```c

#ifndef LIB_H
#define LIB_H

[...]

#endif //LIB_H
```

O compilador por sua vez, literalmente traduz o código de linguagem C para o Assembly de uma determinada arquitetura, realizando várias otimizações, algumas por são definidas por padrão e outras de acordo com as flags utilizadas que podem ser estabelecidas. 

O código Assembly gerado pelo compilador é então passado ao assembler, que traduz de de lingaugem Assembly para código de máquina, isto é, código binário. O arquivo resultante deste processo é  comumente chamado arquivo objeto. O assembler é quem dá um endereço de memória por exemplo para cada variável e instrução. Por fim, os arquivos objetos tanto do seu código quanto aqueles de bibliotecas, são linkados ou agregados pelo linker que finalmente produz seu código executável com tudo que ele precisa para rodar.

Quando utilizamos uma IDE, ou mesmo chamamos o `GCC` diretamente via _shell,_ não notamos que esses processos são realizados por ferramentas distintas. Isto, pois utilizamos uma toolchain que abstrai essa chamada para nós. Mas na realidade, cada um desses processos é executado de forma separada por uma ferramenta específica.

Assim, uma toolchain é composta por:

* Pré-processador;
* Compilador;
* _Assembler_;
* _Linker_.

![](../.gitbook/assets/image%20%282%29.png)





