# Crosstool-ng

Neste treinamento, iremos utilizar a [Crosstool-ng](https://crosstool-ng.github.io/) para montar a nossa própria toolchain em um primeiro momento.

Ela é provavelmente a principal ferramenta open-source para geração de toolchains, foi projetada exclusivamente para geração de toolchains, diferente da [Buildroot](https://www.buildroot.org/) e [Yocto](https://www.yoctoproject.org/), por exemplo, que geram tudo desde toolchain, imagem do kernel, RootFS e etc. 

Além disso, como esperado o Crosstool-ng suporta diversas plataformas como ARM, PowerPC, x86 e outros bem como, tem a capacidade de gerar ferramentas para plataformas _bare-metal._ Por fim, o Crosstool-ng possue a interface de configuração similar a interface utilizada para configurar o kernel Linux.

### Instalando o Crosstool-ng

Como esperado a primeira etapa de instalação da ferramenta, constitui-se em baixar-la de algum repositório. Em seguida, devemos instalar a ferramenta localmente para utiliza-la. Então, depois de baixar e extrair a ferramenta realizamos sua instalação:

```bash
./configure --enable-local
make
make install
```

A instalação em um diretório local é sempre recomendada, pois é normal utilizar mais de uma arquitetura no mesmo desktop. Ou seja, você pode programar diversas arquiteturas sem que uma ferramenta interfira na outra. Para tal, basta utilizar a flag `--enable-local`, indicando que deseja instalar somente neste diretório.

Então, basta fazer a compilação automatizada através do comando `make` e então utilizar o `make install` para ajustar os binários nos diretórios correto e organizar tudo para que a ferramenta funcione.

A partir deste momento, a ferramenta já pode ser utilizada, por exemplo, é possível listar os _samples_ que ele fornece pelo comando `./ct-ng list-samples`. Estes _samples_ podem, ser uma espécie de esqueleto com as configurações básicas para uma determinada plataforma ou arquitetura.

Escolhido um exemplo da lista, basta carrega-lo através do comando `./ct-ng <sample-name>`. Depois de carregado, você vai lança a aplicação propriamente dita e personalizar.

```bash
./ct-ng list-samples
./ct-ng <sample-name>
./ct-ng menuconfig
./ct-ng build
```

### Detalhamento de alguma opções de configuração

Ao passo que estamos realizando a configuração do Crosstool-ng, podemos realizar-la de diversas formas, porém algumas opções podem ser uteis e não necessáriamente alto explicativas. Desta forma, vamos avaliar algumas opções do _menuconfig._ Algumas destas opções serão explicadas de forma mais profunda na seção seguinte durante o experimento.

Alguns comentários a respeito do Crosstool-ng: 

* Na opção **Target options**:
  * _Suffix to the architecture_: literalmente um sufixo a para indicar uma variante da arquitetura. Por exemplo: ARM -&gt; conjuntos de instruções, v7, v6 e v8. No caso do treinamento estamos interessados na RPi3, onde o sufixo é v8. É possível criar toolchains para mais de uma arquitetura, ou variação.
  * _Attemp to combine:_ É uma feature do Crosstool-ng para combinar as bibliotecas em um único diretório, é interessante por exemplo utilizando arch64. Uma vez que os toolchains usam lib, lib64 e quando se tem mais de uma arquitetura começa a ficar bagunçado o diretorio.
  * Nossa arquitetura possui MMU então vamos utiliza-la.
  * _Endianess_: _Little endian,_ isto é, bytes menos significativos primeiro.
  * Todo o sistema, toolchain, kernel e bootloader serão 32 bits. Apesar da RPi 3 suportar instruções 64 bits, pois o processador é 64 bits. Ela ainda é instável, tendo diversas ferramentas incompatíveis.
  * _Target Optimisations_: são configurações relacionadas ao GCC, é basicamente um wrapper do crosstool

### \[EM BREVE..\]

