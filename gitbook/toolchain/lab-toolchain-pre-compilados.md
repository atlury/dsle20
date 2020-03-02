# \[LAB\] Toolchain Pré-compilados

## Cross-Compiling Toolchain

Os objetivos desta atividade são:

* Aprender a utilizar um toolchain pronto, isto é, fornecido pelo fabricante do SoC ou repositório padrão por exemplo;
* Compilar seu próprio toolchain utilizando a ferramenta `crosstool-ng.`

### Utilizando um toolchain pré-compilado

A Raspberry Pi Foundation fornece gratuitamente em seu [repositório oficial](https://github.com/raspberrypi), diversos componentes open-source para a Raspberry Pi. Dentre eles, estão inclusos os fontes do kernel Linux, drivers, bibliotecas e firmwares específicos, além de seu próprio toolchain, o qual será utilizadonesta atividade.

#### Instalação e Configuração

Inicialmente, abra um novo shell e crie a seguinte estrutura de diretórios dentro do diretório `dsle19`:

```bash
cd ~/dsle20
mkdir toolchains
cd toolchains
```

Em seguida, o correto seria clonar a pasta `tools` do repositório oficial da Raspberry Pi, no intuíto de obter a última versão disponível do toolchain:

```bash
git clone https://github.com/raspberrypi/tools.git
```

No entanto, a fim de garantir uma maior eficiência na execução das atividades deste treinamento, todos os arquivos necessários foram previamente baixados e encontram-se no diretório `dsle19/dl`. Portanto, substituiremos o processo de clonar o repositório `tools` pela extração do seguinte arquivo:

```bash
unzip ~/dsle20/dl/toolchains/tool.zip
```

O comando acima extrai o arquivo _tools.zip_ no diretório atual \(`dsle19/toolchains`\). Ao final do processo, verifique se o diretório `tools` foi criado, por meio do comando `ls`.

Como o toolchain fornecida pela RPi Foundation é pré-compilado, para instalá-lo basta adicionar o caminho das ferramentas \(binários\) do toolchain à variável de ambiente `$PATH`:

```bash
export PATH=$PATH:~/dsle20/toolchains/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
```

Note que tal alteração é momentânea, isto é, ao fechar o shell atual ela será perdida. Um dos meios defazer essa alteração permanente \(opcional\) é por meio da inserção do mesmo comando no final do arquivo `∼.bashrc`, que é um script shell que é executado sempre que um novo shell é iniciado.

Simples assim, toolchain instalado! Uma maneira de verificar se o _export_ do PATH funcionou é digitar `arm` no shell e pressionar a tecla TAB duas vezes. Ao fazer isso, o shell tentará auto-completar o comando `arm` de acordo com as opções de executáveis disponíveis na variável PATH. O resultado deverá ser uma lista semelhante à:

```bash
arm2hpdl
arm-linux-gnueabihf-gfortran
arm-linux-gnueabihf-addr2line
arm-linux-gnueabihf-gprof
arm-linux-gnueabihf-ar
arm-linux-gnueabihf-ld
arm-linux-gnueabihf-as
arm-linux-gnueabihf-ld.bfd
arm-linux-gnueabihf-c++
arm-linux-gnueabihf-ldd
arm-linux-gnueabihf-c++ filt
arm-linux-gnueabihf-ld.gold
[...]
```

#### Testando o toolchain

É possível testar o toolchain através da compilação de um programa bem simples, como o `helloworld.c`, em C. Inicialmente, crie a pasta `ex01` dentro do diretório de exercícios `exs` e, em seguida, crie/edite o arquivo `helloworld.c` com seu editor favorito:

```bash
cd ~/dsle2020/exs
mkdir ex01 && cd ex01
gedit helloworld.c
```

E então,

{% code title="helloworld.c" %}
```c
#include <stdio.h>

int main()
{
    printf("Hello cross-compiled world!\n");
    return 0;
}
```
{% endcode %}

Em seguida, compile o arquivo `helloworld.c` nativamente, isto é, utilizando o _gcc_:

```bash
gcc helloworld.c -o hellox86
```

Utilizando o comando `file`, verifique as informações do binário gerado:

```bash
file hellox86
```

A saída do comando deve ser algo similar à:

```bash
hellox86: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib, for GNU/Linux 2.6.32, BuildID[sha1]=ae1b783e3b504073e808de7dc21fc4e3f2c0f2cf, not stripped
```

Note que a segunda informação, _Intel 80386_ indica que o programa foi compilado para a mesma arquitetura de sua máquina, x86. Em seguida, execute-o:

```bash
chmod +x hellox86
./hellox86
Hello cross-compiled world!
```

Agora repita o processo e utilize o recém-instalado toolchain para cross-compilar o mesmo programa para a RPi. Para isso, trocamos o compilador antivo _gcc_ por _arm-linux-gnueabihf-gcc_:

```bash
arm-linux-gnueabihf-gcc helloworld.c -o helloARM
```

Novamente, verifique o programa gerado através do comando `file` e veja que desta vez a arquitetura indicada será _ARM_:

```bash
helloARM: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld- linux -armhf.so.3, for GNU/Linux 2.6.26, BuildID[sha1]=68bc6061bdbb1b80e5190760e91b687a1caebf97, not stripped
```

Não será possível executar este segundo programa na sua máquina pois o programa e a máquina possuem arquiteturas diferentes. Faça o teste. No entanto, é possível copiá-lo para a RPi e executá-lo nela.

Para tal, utilizaremos o protocolo _SSH_ para a comunicação entre a nossa plataforma _host_ \(PC\) e a nossa placa \(_target_\).

{% hint style="danger" %}
Primeiramente, devemos estabelecer uma conexão de rede entre a RPi e nosso computador. O capítulo [Configurando a Rede da RPi](/linux/rede), apresenta algumas formas de se estabelecer esta comunicação.
{% endhint %}

Copie-o para a RPi através do comando `scp` \(secure copy\). Primeiramente, confira a funcionamento do comando através de seu manual `man scp` e então:

```bash
scp helloARM pi@10.1.1.100:/home/pi/helloARM
```

Acesse-a via _SSH_ e tente executar o programa, lembre-se a senha padrão do usuário `pi` da RPi é **raspberry**.

```bash
ssh pi@10.1.1.100
```

```bash
cd
./helloARM
```

Neste ponto, conseguimos realizar a nossa primeira compilação \(cross-compile\) e também a nossa primeira execução na plataforma embarcada \(RPi\).

Este procedimento foi realizado com base em uma toolchain pronta, fornecida por terceiros. Contudo, em um contexto profissional e em aplicações reais, faz-se necessário a utilização de toolchains próprias e criadas e adequadas ao nosso sistema. Desta forma, no próximo capítulo será discutido o procedimento de criação de toolchains suas principais ferramenteas e componentes.

