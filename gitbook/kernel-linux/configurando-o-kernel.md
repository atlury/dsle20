# Configurando o Kernel

Como apresentado durante o treinamento, em outras seções, o kernel Linux possui uma infinidade de de drivers, protocolos de rede e itens de configuração. Desta forma, como imagina-se existem milhares de opções disponibilizadas para a configuração, permitindo incluir ou não cada um dos items disponibilizados, ou seja, incluir ou não cada uma das partes do kernel Linux.

Esse processo de configuração é realizado para que o kernel Linux, consiga ser compilado com as partes requeridas para uma determinada arquitetura. Para facilitar o processo, foram definidos conjuntos ou grupos de configuração.

 Desta forma, o conjunto de opções é montado com base em:

* Tipo do hardware \(drivers\);
* Funcionalidades desejadas \(sistema de arquivos suportados, protocolos e etc\).

### Arquitetura

Por padrão, a configuração do kernel Linux é compilada para a arquitetura nativa, ou seja, o kernel irá compilar para a mesma arquitetura que o sistema _host_. Porém, isso pode ser facilmente ajustado através da mudança da variável de ambiente ARCH. Alterando-a é possível alterar a arquitetura de compilação do kernel Linux. Portanto,

```bash
export ARCH=arm
```

Atribuindo _arm_ para a variável ARCH, estamos modificando para qual arquitetura o kernel deverá ser compilado. Em especial, neste caso, para a arquitetura _arm_. Não se esqueça, que para ver as arquiteturas disponíveis no kernel Linux, basta analisar as disponíveis no diretório padrão.

Desta forma, o kernel Linux é compilado então, utilizando-se os headers e fontes, para a arquitetura ARCH.

### _Build System_

O processo de build do kernel Linux é baseado em vários arquivos Makefile. Este processo é automatizado, cada arquivo é responsável por agrupar, organizar e compilar cada parte do kernel. Contudo, nossa interação é somente com o Makefile principal, este esta presente na raiz dos fontes.

Por exemplo,

```bash
cd linux-rpi-4.14.y
make <target>
```

A interação irá ocorrer entre todos os Makefiles internos, definindo configuração, compilação e instalação.

### Arquivos de Configurações Prévias

Assim como outras ferramentas, é difícil definir uma configuração que irá funcionar com seu hardware e RootFS. Como principal recomendação, é instruído a não começar do zero esse processo. O ideal é começar por algo já testado, previamente configurado.

Para tal, existem arquivos de configuração prévia relacionados a cada uma das arquitetura disponíveis, isto é, a cada família de processados que é suportada pelo kernel. Este arquivos estão disponíveis em `arch/<arch>/configs/`.

Além disso, é necessário carregar estes arquivos de configuração esta etapa é simples, basta realizar a execução do comando `make` sob o processador que deseja.

```bash
make cpu_defconfig
```

Por exemplo, no caso do nosso treinamento, estamos interessados em carregar as configurações disponíveis para a RPi 3. Assim, o arquivo se encontra em `arch/arm/configs/bcm2709_defconfig`, então parar carregá-lo, basta executar:

```bash
make bcm2709_defconfig
```

### Criando Arquivos de Configuração

Caso deseja-se não utilizar um arquivo de configuração já definido, como o apresentado na seção anterior. É possível realizar a criação de um novo arquivo de configuração, este pode até mesmo, ser baseado em um arquivo já existente, como também pode ser desenvolvido do zero.

Para criar o seu próprio arquivo de configuração, basta simplesmente executar o comando:

```bash
make savedefconfig
```

Isto irá gerar um arquivo simples com a configuração mínima requerida. Então, é possível editá-lo então, de acordo com seus gostos e os requisitos da sua plataforma. Em seguida, é possível então, incluí-lo na na àrvore do kernel Linux e compartilhá-lo na comunidade:

```bash
cp yourdefconfig arch/<arch>/configs/yourdefconfig
```

Claro que não é simplesmente fazer o commit do módulo e ele entrará na árvore, ele deve ser testado, aprovado e etc.

### Arquivos de Configuração

Todas as configurações que são/foram realizadas, são salvas em um arquivo `.config` no diretório raiz dos fontes.

Este arquivo, nada mais é do que um arquivo texto normal. Sua estrutura é bem simples, consiste em um conjunto de dados do tipo _chave=valor_, e é criado pelo próprio Makefile:

```bash
CONFIG_ARM=y
...
```

O processo de configuração é um proesso delicado, ainda mais crítico devido as dependência. Isto é, as opções selecionadas devem carregar suas próprias dependências e isto é um tanto quanto difícil de ser fazer manualmente. Para tal, existem formas para facilitar a configuração, através de interfaces de textou ou gráficas:

* `make menuconfig` -&gt; interface de texto;
* `make nconfig` -&gt; interface de texto;
* `make gconfig` -&gt; interface gráfica;
* `make xconfig` -&gt; interface gráfica.

Todas essas interfaces editam o mesmo arquivo, `.config`, desta forma tanto o resultado de ambos os processos tende a ser idêntico, como viabiliza trocar de uma interface para outra ao longo do processo. Pois editam o mesmo arquivo e exibem o mesmo conjunto de opções.

### Arquivo Final

Após realizar a configuração, o arquivo final gerado é um binário único. Portanto, a imagem do kernel Linux que foi construída é resultado de um processo de compilação, linkagem de arquivos-objetos correspondentes às funcionalidades habilitadas é um **binário único**.

Este arquivo vai ser carregado pelo bootloader no processo final de seu ciclo, no caso da RPi do treinamento, será carregado após a inserção do U-Boot no processo. E esse kernel é carregado para dentro da memória RAM, ao passo que o bootloader é desmontado. Em seguida, quando o kernel é inicializado, ou seja, quando o mesmo começa a sua execução, todas as ferramentas e funcionalidade tornam-se disponíveis.

Mas como o esperado, é possível realizar compilar essas funcionalidades de maneira dinâmica e de maneira estática. Em outras palavras, é um código compilado como qualquer outro, sua linkagem pode ser dinâmica ou estática.

Através da linkagem dinâmica suas funcionalidades são tratadas como módulos, são normalmente referenciadas como _modules._ Os módulos são armazenados no RootFS como arquivos e são carregados dinamicamente, em tempo de execução.

Ao passo que da maneira estática, as funcionalidades são linkadas de forma estática à imagem do kernel.

### Opções de Configuração

Algumas das opções fornecidas esperam entradas booleanas, ou são habilitadas ou não são habilitadas. Desta forma, tomando como exemplo o processo através do `make menuconfig`, temos:

* \[\*\] Funcionalidade 1 \(habilitada\)
* \[  \] Funcionalidade 2 \(desabilitada\)

Basicamente, a funcionalidade que carrega a marcação **\[\*\]** é incluida no kernel ou caso seja colchetes vázios \(no menuconfig\) a funcionalidade é removida do kernel.

Além disso, existe opções que esperam operações de três estados. 

* &lt;   &gt; Funcionalidade 1 \(desabilitada\)
* &lt; \* &gt; Funcionalidade 2 \(habilitada como _built-in_\)
* &lt;M&gt; Funcionalidade 3 \(habilitada como módulo\)

Um estado que remove a funcionalidade do kernel, um estado que incluí de forma _built-in_ a funcionalidade no kernel e uma última que inclui no kernel como módulo.

Por fim, algumas opções necessitam que seja especificado algum comportamento, como tamanho de buffer, número de bytes, caminho relativo de algo e etc. Assim, são esperados tipos diferentes de entrada, como inteiros, strings e hexadecimais.

### Opções com Dependência

Como mencionado anteriormente existe algumas opções do kernel Linux que possuem dependências de outros módulos. Por exemplo:

O driver de um dispositivo I2C que é disponibilizado requer que o suporte ao barramento I2C seja habilitado no kernel. Desta forma, ao carregar a funcionalidade I2C é necessári o que sua dependência, barramento habilitado, seja satisfeita. Essa tarefa é feita automaticamente caso esteja utilizando as ferramentas automatizadas, porém ser for de forma manual, você deve garantir o mesmo.

Outro exemplo é o framework de porta serial \(serial core\) é habilitado automaticamente quando um driver de UART é habilitado.

### Validação de Configuração

Suponha que o arquivo .config foi alterado manualmente ou mesmo que você deseja utilizar a configuração em outra versão do kernel Linux. É necessário fazer uma validação para garantir a consistência das configurações escolhidas. 

```bash
make oldconfig
```

Para tal, é fornecido uma ferramenta que caso haja alterações a serem feitas, como por exemplo, selecionar um parâmetro específico que não existia na versão anterior do kernel é solicitado que você insira esses parâmetros, por exemplo. Este processo é totalmente diferente do `menuconfig` onde é inserido valores padrões para parâmetros não definidos ou novos.

Portanto, este deve ser chamado sempre que o arquivo `.config` for alterado manualmente ou os fontes do kernel forem atualizados e deseja-se utilizar a mesma configuração.





