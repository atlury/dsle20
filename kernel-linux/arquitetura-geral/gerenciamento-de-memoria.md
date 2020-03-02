# Gerenciamento de Memória

O kernel Linux, assim como a maioria dos sistemas operacionais modernos, implementa o mecânismo de memória virtual para gerenciar a memória física. O acesso à memória é realizado através de endereços virtuais, que são convertidos via hardware para endereços físicos da memória. O hardware que faz esse gerenciamento e conversão de memória virtual para física, é a MMU \(Unidade de Gerenciamento de Memória\) e conforme comentado durante o treinamento, normlamente ela é um recurso do processador.

Em geral, a MMU fornece e gerencia uma tabela de páginas para o sistema operacional e quando algum processo ou aplicação deseja acessar um endereço físico, o kernel consulta essa tabela e extrai o endereço necessário.

Via de regra, sistemas com MMU fornecem várias funcionalidades, tais como:

* Um maior endereçamento de memória para os processos;
* A famosa região de SWAP, apesar de ultimamente estar ficando menos utilizada. Pois os tamanhos de RAMs estão aumentando muito. Normalmente a SWAP é uma simulação de memória física, no disco rígido, é claro que fica um pouco mais lento \(dependente do processo de leitura/escrita do driver\) que a memória RAM normal. Mas é mais rápido do que uma troca de contexto entre memória e disco rígido. A SWAP é paginada também, então do ponto de vista do sistema ela é tratada literamente como uma memória secundária é possível recuperar e salvar páginas da SWAP.
* Oferece uma certa proteção, onde cada processo só enxerga seu espaço de endereçamento, normalmente, quando se escreve um programa em C e tenta-se utilizar instruções pouco elegantes como `go-to`, o programa tenta acessar de alguma forma uma aŕea fora de seu endereçamento e ocasiona um erro de S_egmentation Fault,_ ou seja, não é possível acessar endereços fora de seu escopo de memória.
* Apesar de ter essa proteção, ela também oferece uma flexibilidade para os programadores. Esta é a possibilidade de compartilhar a memória entre dois ou mais processos. Existem alguns mecânismos para esse tipo de manipulação, chamados de mecânismos de comunicação inter-processos \(IPC\) e com sorte, iremos usar alguns deles na prática, ao final do treinamento. Como _Queue Messages_, _Semáforos_, _Socket, Signals_ e etc.
* Arquiteturas com MMU também suportam _Memory Mapping,_ isso da possibilidade de mapear uma regiao da memória, uma ou mais páginas por exemplo entre processos. É uma função útil, assim que um processo termina de escrever em uma região e outro processo pode ter acesso á ela, é uma área visível para mais de um processo.

