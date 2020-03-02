# Kernel Space vs. User Space

Como mencionado anteriormente no treinamento, o Linux trabalha com o conceito de KS - kernel space e US - user space, essa é uma divisão bem definida. Tal divisão não é feita na memória física, o kernel faz através daquela tabela de páginas de memória que a MMU cria o kernel divide algumas páginas para rodar aplicações do usuário e outras para o kernel.

Como mencionado anteriormente no treinamento, o Linux trabalha com o conceito de KS - kernel space e US - user space, essa é uma divisão bem definida. Tal divisão não é feita na memória física, o kernel faz através daquela tabela de páginas de memória que a MMU cria o kernel divide algumas páginas para rodar aplicações do usuário e outras para o kernel.

O kernel, que roda no kernel space, roda em modo priviligiado, isto significa que ele tem acesso total aos recursos do sistema, desde de acesso a arquivos quanto à hardware, por exemplo.

O kernel, que roda no kernel space, roda em modo priviligiado, isto significa que ele tem acesso total aos recursos do sistema, desde de acesso a arquivos quanto à hardware, por exemplo.

Ao passo que as aplicações, que rodam em user space, não tem permissão para acessar tais hardwares diretamente, ou seja, elas rodam em modo restrito.

Ao passo que as aplicações, que rodam em user space, não tem permissão para acessar tais hardwares diretamente, ou seja, elas rodam em modo restrito.

### _System calls_

Portanto, há a necessidade da uma interface de comunicação entre suas aplaicações e o kernel, estas que são as denominadas chamadas de sistemas ou _system calls_. Tais como as funções apresentadas em momentos anteriores do treinamento, por exemplo: `read`, `write`, `open`, estas são todas chamadas de sistema.

Atualmente o Linux possui aproximadamente 400 chamadas de sistema, dos mais variados tipo, pode até ser que esse número já tenha aumentado no momento deste treinamento. São as chamadas de sistema que fornece suporte para operação de arquivos, criação e gerenciamento de processos e threads, comunicação entre processos, timers, operações de rede e etc. 

As rotinas já apresentadas `read`, `write`, `open` e `pthread_create`, por exemplo, são na realidade abstrações das _system calls,_ elas são desenvolvidas em linguagem C e pertecem a biblioteca C padrão.

Desta forma, quando executa-se um, por exemplo, `man` em um terminal, é apresentado os parâmetros da função, bem como um detalhamento sobre a rotina. Todo esse suporte foi criado pelos desenvolvedores da biblioteca C que o implementaram essa abstração de forma a facilitar a utilização do lado do usuário e deixar os parâmetros, principalmente, no formato desejado pelas chamadas.

Além disso, essa interface costuma ser bem estável, a cada nova versão/release do kernel, os desenvolvedores só podem adicionar novas chamadas e não remove-las \(lembram da filosofia de desenvolvimento da mainline?\), garantindo assim que as chamadas continuem robustas e sem a necessidade de refatoração por parte do usuário.







