# Kernel Linux

O kernel é carregado e iniciado pelo bootloader, assim que este foi inicializado ele desempenha o papel de iniciar o processador, as memórias e os barramentos de comunicação. Ou seja, o bootloader é responsável por carregar o kernel e este, por sua vez, é responsável por carregar o sistema propriamente dito.

Após a inicialização destes periféricos, o kernel configura a memória virtual do sistema, no caso do kernel Linux esta memoria virual é a memória swap. Em resumo, esta memória virtual é uma área reservada no disco rigido que o sistema utiliza como uma extensão da memória RAM. Desta forma, existe um mapeamento da memória virtual para a RAM e da memória virtual para o disco rígido.

Em seguida, após a configuração e mapeamento da memória virtual, o kernel inicializa todos os drivers para os dispositivos de hardware presentes no sistema, é neste momento que o kernel carrega todos os módulos e drivers do sistema, inclusivel os módulos presentes na nossa aplicação.

Por conseguinte inicializa o escalonador de tarefas. Que é responsável por administrar a ordem de execução dos programas do sistema. Ele cria uma ordem de prioridades e tempos que cada processo tem direito em relação à CPU, e faz esse gerenciamento.

Então, inicializa as threads do kernel, que são processos que auxilliam o kernel no gerenciamento do sistema, algumas dessas threads podem ser vistas rodando no nosso sistema, através do monitoramento de processos do Linux.

Por fim, é montado o sistema de arquivos principal \(rootfs\), que é a partição onde o sistema está instalado e chama o processo `init`. Que é um script de programas que deseja-se inicilizar logo em seguida ao kernel.

**Inicialização básica:**

* Processador;
* Memórias;
* Barramentos de comunicação;
* Memória virtual \(caso o processador tenha MMU\);
* Device Drivers;
* Escalonador;
* Threads do kernel;
* RootFS;
* `init`.

Além da inicialização básica do sistema, o kernel possui outras característica. Ele é responsável por gerenciar todos os processos do sistema operacional, desde processos internos do Linux até processos relacionados à aplicação. Esta tarefa é desempenhada pelo escalonador de processos. Ele também controla o acesso à RAM do sistema e também quaisquer I/O \(entrada/saida\) do sistema. Em resumo, tudo passa ou deve passar pelo kernel.

 Não obstante, no Linux existe também o conceito de Kspace e Uspace. Por exemplo, a memória de swap - memória virtual - é divida entre ks e us. 

O KS é protegido das aplicações do usuário, ou seja, é uma região de memória que não pode ser acessada através da aplicação. Esta região armazena o próprio código do kernel e uma estrutura que descreve toda a memória física. Ao passo que o US é separado pra rodar as aplicações do usuário. Qualquer programa executado pelo usuário, é armazenado no US.

A interface entre o usuário e qualquer dispositivo/componente que seja gerenciado pelo kernel, é realizado através das System Calls, portanto devem ser engatilhadas por uma entidade interna do kernel. Por exemplo se a aplicação do usuário precisa acessar um hardware, ela faz uma system call, então o kernel acessa aquele hardware e envia a resposta para a aplicação do usuário. O KERNEL SPACE é totalmente protegido e isto faz total sentido!

Neste ponto, devemos entender como são representados os periféricos e quaisquer outras entidades no sisitema Linux. Em geral, todas essas entidade de harware, como GPIOS, LEDS, periféricos de comunicação serial e etc que possuem um driver, são representados através de um arquivo no sistema, desta forma, para realizar a interação com um desses componentes é necessário realizar uma interação com um desses arquivos, e isto pode ser realizado através de chamadas de sistema. Além disso, o kernel consegue prover também, um gerenciamento dinâmico dos módulos do sistema.

**Características:**

* Gerenciamento de processos;
* Gerenciamento da RAM e I/O;
* Kernel Space vs. User Space;
* System Calls;
* Arquivos de dispositivos;
* Gerenciamento dinâmico de módulos.









