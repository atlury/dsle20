# \[LAB\] Compilando seu próprio Toolchain

## Compilando seu próprio toolchain

A [_Crosstool-ng_](https://crosstool-ng.github.io/) é provavelmente a principal ferramenta open-source para customização de toolchains. Suporta diversas arquiteturas diferentes, é capaz de gerar código bare-metal e possui uma interface baseada no _menuconfig_.

Nesta atividade, a ferramenta _Crosstool-ng_ será utilizada para criar um toolchain customizado para a RPi. Este toolchain será utilizado para todas as atividades posteriores como compilação do bootloader, kernel, bibliotecas e aplicações.

#### Instalação e Configuração

Abra um novo shell e navegue até a pasta `∼/dsle20/toolchains`. Em seguida, descompacte o arquivo `∼/dsle20/dl/toolchains/crosstool-ng-1.23.0.tar.xz` no diretório atual e navegue até o novo diretório:

```bash
cd ~/dsle20/toolchains/
tar xvf ~/dsle20/dl/toolchains/crosstool-ng-1.23.0.tar.xz
cd crosstool-ng-1.23.0/
```

Após a descompactação, configure o _crosstool-ng_ para ser instalado localmente, isto é, no mesmo diretório em que se encontra o script de configuração. Então, execute os comandos `make` e `make install` para realizar a instalação:

```bash
./configure --enable-local
make
make install
```

Se tudo correu bem e nenhuma mensagem de erro foi exibida, o _crosstool-ng_ pode ser executado a partir do diretório atual. O seguinte comando exibe as informações de ajuda da ferramenta:

```bash
./ct-ng help
```

O _Crosstool-ng_ permite criar um ou mais toolchains para arquiteturas diferentes e, por isso, fornece um conjunto de configurações pré-definidas para arquiteturas mais comuns. É possível listá-las por meio do seguinte comando:

```bash
./ct-ng list-samples
```

Note que, dentre as configurações, existe uma pré-definida para a RPi 3: `armv8-rpi3-linux-gnueabihf`. Neste treinamento, essa configuração será usada como base para a criação do toolchain. Para tal,carregue-a por meio do comando abaixo:

```bash
./ct-ng armv8-rpi3-linux-gnueabihf
```

Uma vez feito o _loading_ da configuração, abra o menu de configurações do _crosstool-nt_ e faça alguns ajustes:

```bash
./ct-ng menuconfig
```

{% hint style="warning" %}
Nesta etapa você deverá realiza a configuração através do _menuconfig_ portanto, muita atenção pois é um procedimento que requer cuidado, pois a configuração errada de algum módulo ou componente pode não ser evidente agora e causar problemas durante a fase de desenvolvimento.
{% endhint %}

#### Configuração da CrossTool

1. Opção **Path and misc options**:
   * **Number of parallel jobs**: \(2\) - Obs: Essa opção define a quantidade de threads de execução, que por sua vez diminui o tempo de compilação do toolchain.
   * **Maximum log level to see**: \(DEBUG\) - Obs: Essa opção exibe informações a respeito do procedimento de build em tempo real. Assim, caso ocorra algum erro durante a compilação do toolchain, esse erro será exibido no shell.
   * **CT\_PREFIX**: Obs: Este é o diretório de instalação do toolchain. 

     Altere-o **de**: ${CT\_PREFIX:-${HOME}/x-tools}... 

     **para**: ${CT\_PREFIX:-${HOME}/dsle20/toolchains/x-tools}...
2. Opção **Toolchain options**:
   * **Tuple's alias**: \(arm-linux\) - Obs: Desta maneira, o _crosstool-ng_ irá gerar o compilador como `arm-linux-gcc`, por exemplo. Caso contrário ele gera um nome extenso como: `armv8-rpi3-linux- gnueabihf-gcc`.
3. Opção **Debug facilities**:
   * **gdb**: \(ativo\) - Obs: Ative o `gdb`, pois será o debugger utilizado no restante do treinamento. Além disso, assegure-se de que as seguintes opções foram selecionadas:
     * Cross-gdb;
     * build a static cross gdb;
     * gdbserver

Salve suas alterações, saia do _menuconfig_ e inicie o processo de compilação do toolchain:

```bash
./ct-ng build
```

Ao final do processo, conforme configurado em _CT\_PREFIX_, os binários do toolchain gerado estarão disponíveis no diretório: `∼/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin/`. Dê um comando `ls` no diretório e verifique as ferramentas geradas.

#### Configuração do PATH

Como este toolchain será utilizado nas próximas atividades do treinamento, é necessário adicionar seus executáveis à variável de ambiente `$PATH`. Abra o arquivo `∼/.bashrc` com seu editor favorito:

```bash
gedit ~/.bashrc
```

Em seguida, adicione a seguinte linha no final do arquivo:

```bash
export PATH=$PATH:~/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin/
```

Salve e feche o arquivo. Então basta carregar a configuração e, em seguida, realizar um pequeno teste para verificar se os binários foram adicionados corretamente à variável `$PATH`:

```bash
source ~/.bashrc
arm-linux-gcc --version
```

A saída deve ser algo semelhante à:

```bash
arm-linux-gcc (crosstool-NG crosstool-ng-1.23.0) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

#### Testando o toolchain

Recompile o programa da atividade 01, `helloworld.c`, em C com o novo toolchain gerado. Inicialmente, crie a pasta `ex02` dentro do diretório de exercícios `exs` e, em seguida, copie o arquivo `helloworld.c` da pasta `ex01` para a pasta `ex02`:

```bash
cd ~/dsle20/exs
mkdir ex02
cp ex01/helloworld.c ex02
```

Navegue até a pasta `ex02` e compile o programa `helloworld.c` utilizando o _gcc_ do toolchain recém-criado:

```bash
cd ex02
arm-linux-gcc helloworld.c -o helloARMctng
```

Novamente, verifique o programa gerado através do comando `file` e veja que, as informações exibidas como arquitetura e versão do kernel, estarão de acordo com as opções selecionadas no _crosstool-ng_:

```bash
file helloARMctng
```

```bash
helloARMctng: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-
linux -armhf.so.3, for GNU/Linux 4.10.8, not stripped
```

Se desejar, repita o teste de rodar o executável na RPi 3. Primeiramente copie através do `scp` para a plataforma embarcada.

```bash
scp helloARMctng pi@10.1.1.100:/home/pi/helloARMctng
```

Então, acesse-a e execute o código recém enviado:

```bash
ssh pi@10.1.1.100
cd
./helloARMctng
```

