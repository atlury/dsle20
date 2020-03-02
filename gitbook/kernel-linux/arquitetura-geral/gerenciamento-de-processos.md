# Gerenciamento de Processos

Primeiramente devemos definir o que são processos do ponto de vista do kernel Linux. Podemos então, definir um processo, como um programa \(normalmente um arquivo objeto ou binário armazenado em uma mídia, como o seu cartão micro SD\) que se encontra no meio de sua execução, ou seja, é um programa em execução, ponto.

Um processo, possui um _Process ID_ único para identifica-lo perante o kernel. Este _PID_ nada mais é do que um contador, e está associado a um conjunto de recursos do sistema operaciona. Tais como, arquivos abertos, mapeamento de memória, isto é, a região da memória reservada para a execução daquele programa e etc.

{% hint style="success" %}
Para observar os processos que estão executando no Linux, e também seus _PIDs_ e outras características, podemos utilizar o comando `ps -A`, ou ainda através da aplicação`htop`.
{% endhint %}

Cada processo contém, pelo menos, uma ou mais linhas de execução, que também são chamados de _threads_. 

### Threads vs. processos

_Threads_ são treichos de código que podem ser independentemente manipulados pelo escalonador. Isto significa que podem ocorrer de forma, paralela e sequêncial. Tipicamente, as threads são partes de constituintes de processos do sistema operacional.

![](../../.gitbook/assets/image%20%2824%29.png)

A implementação de threads e processos é diferente em alguns sentidos, mas de forma geral as threads são componentes dos processos. Podem existir diversas threads de um processo e estas estarem executando de forma concorrente e compartilhando recursos como por exemplo regiões de memória. Enquanto processos distintos não compartilham desses recursos. Em particular, as threads de um processo compartilham os endereços de memória e outros recursos.

De forma resumida podemos listas as diferenças das threads e dos processos:

**Processos**:

* São tipicamente independentes;
* Tem muito mais estados e informações que uma thread;
* Possuem espaços endereçados;
* Interagem apenas através de IPC.

**Thread**:

* É um sub-código de um processo;
* Multiplas threads pode fazer parte de um processo;
* Threads de um processo compartilham de seu estado, memória e etc;
* Threads compartilham seus endereços de memória.

### Estrutura de gerenciamento

O kernel Linux gerencia o conjunto de processos através de uma estruturade de dados, mais precisamente, uma lista circular duplamente encadeada. Onde cada nó representa um processo, contendo informação como memória mapeada, proccess ID, parent process ID, isto é, o process ID de quem iniciou aquele processo. Enfim, cada nó é uma estrutura de dados que contém toda a informação relevante de um processo específico.

Cada thread possui um contador de programa, que tem a mesma função do process ID, mas ele serve para identificar a thread, uma região de stack e uma cópia dos registradores da CPU.

O kernel não faz diferenciação entre processos e threads, do ponto de vista de escalonamento e afins. Isto quer dizer  que quando um processo novo é criado no Linux, basicamente é criado um clone do processo que o criou \(fork\),  e algumas informações são modificadas pelo kernel.

### Escalonador

Para entender o funcionamento da gerência de processos no Linux, ou ainda um sistema multi-tasking, é necessário primeiramente, entender que ele é um sistema preemptivo, ou seja, ele permite troca de contexto. Ele é capaz de parar um processo no meio de sua execução \(se necessário\), e atribuir um outro para a CPU. Esta é a base para o funcionamento do sistema,  o conceito de sistema preemptivo.

O escalonador padrão do Linux, é chamado de CFS \(_Completely Fair Scheduler_\). Esse escalonador tenta modelar uma CPU multi-tasking ideal, essa ideia de CPU multi-tasking ideal, é definida como um processador que rodaria todos os processos em paralelo, dando uma porcentagem igual de tempo de CPI para cada um, ou seja, por exemplo: se tivessemos 4 processos nessa CPU, eles seriam executados em paralelo, cada um usando 25% da CPU. Nessa CPU, nenhuma tarefa receberia mais CPU que outra.

O CFS tenta modelar esse CPU hipotético, mantendo um registro de "injustiça" de cada processo em relação aos outros. Pois na prática, pensando em CPU single core, somente um único processo é executado por vez, enquanto na CPU ideial, não existe injustiça. Uma vez que, ela seria capaz de executar todo mundo ao mesmo tempo, paralelamente, dividindo o processamento igual pra cada uma.

Quando uma task é executada, faz com que o tempo que o CPU "deve" para as outras tasks seja aumentado. Além disso, o kernel oferece também, um framework de classes de escalonamento, onde cada classe permite a utilização de um escalonador diferente, como FIFO ou RR \(_Round Robin_\). Em geral quando se inicia uma thread, é fornecida a opção de selecionar o tipo de escalonador que se prefere.

Dentre as funcionalidades do kernel, existe também um escalonador, que é inclusive o responsável por gerenciar threads da classe FIFO e RR, para aplicações de _real-time_ ou seja, ele tem prioridade sobre o CFS, buscando atingir os critérios de tempo real das operações.

No entando, o Linux não pode ser considerado um RTOS, não em sua forma padrão, pois ele não é completamente determinístico, ou seja, existem alguns trechos do kernel onde a latência pode ser bem alta, em relação a latências normais e mais que isso, há trechos com latências variáveis. 

{% hint style="info" %}
Os critérios de tempo real, não envolvem velocidade de processamento e sim o cumprimento de restrições temporais e _deadlines._

Latência é o tempo que o kernel leva desde uma solicitação / interrupção para executar um processo e a execução efetiva desse processo.
{% endhint %}

Existe um conjunto de patches, conhecidos como PREEMPT\_RT que são aplicados no kernel e até melhoram esse cenário_,_ claro que depende do hardware mas em geral oferece uma latência de centenas de microssegundos.

Uma opção, para utilizar o Linux para aplicações _real-time_ é a utilização de um segundo kernel em conjunto com o Linux, como RTLinux, RTAI, Xenomai. Desta forma, sua máquina fica na verdade com dois kernels sendo executado, e o Linux funciona como um alimentador para o kernel de tempo real. Ou seja, ele apenas comanda o kernel,  é como se o kernel Linux fosse um processo do kernel de tempo real, em geral esses kernels de tempo real costumam baixar a latência para unidades de microssegundos, novamente, depende do hardware.

