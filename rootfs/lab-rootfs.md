# \[LAB\] RootFS

Apesar de não ter sido apresentado ainda, utilizares a ferramenta de _System Build_ chamada **Buildroot** para esta prática. O motivo de se utilizar este tipo de ferramenta ainda será explicado no treinamento. 

Nesta atividade será gerado um sistema de arquivos simples \(RootFS\) baseado no BusyBox, porém como mencionado, utilizaremos a ferramenta Buildroot.

### Baixando o Buildroot

A página oficial do projeto é [https://buildroot.org/](https://buildroot.org/) e seu repositório oficial é [https://github.com/buildroot/buildroot](https://github.com/buildroot/buildroot). É possível baixá-lo dos dois lugares. 

A versão utilizada no curso é uma das últimas, sendo uma versão estável, e encontra-se no diretório `∼/dsle20/dl/rootfs/buildroot-2019.02.8.tar.gz`. Crie o diretório `∼/dsle20/rootfs` e extraia o Buildroot neste diretório:

```text
cd
cd dsle20
mkdir rootfs
cd rootfs
tar xvf ~/dsle20/dl/rootfs/buildroot-2019.02.8.tar.gz
```

### Configurando e Compilando o RootFS

Novamente, o sistema de configuração do Buildroot é idêntico às ferramentas anteriores. Todas as configurações realizadas são salvas em um arquivo `.config` no diretório principal. Para listar as opções de placas/plataformas disponíveis, execute o seguinte comando:

```text
cd buildroot-2019.02.8
make list-defconfigs
```

```text
Built-in configs:
aarch64_efi_defconfig               - Build for aarch64_efi
acmesystems_aria_g25_128mb_defconfig - Build for acmesystems_aria_g25_128mb
acmesystems_aria_g25_256mb_defconfig - Build for acmesystems_aria_g25_256mb
acmesystems_arietta_g25_128mb_defconfig - Build for acmesystems_arietta_g25_128mb
...
```

Após analisar com calma os arquivos, perceba que o da Raspberry Pi 3 B é o `raspberrypi3_defconfig`. Faça o load deste arquivo da mesma maneira como anteriormente:

```text
make raspberrypi3_defconfig
```

Como já possuímos: Toolchain, Bootloader e Kernel configurados, precisamos passar tais informações ao Buildroot para que essas ferramentas não sejam baixadas novamente. Inicie o aplicativo `menuconfig` e faça as seguintes alterações, cautelosamente:

```text
make menuconfig
```

#### Menu: _Toolchain options_

No menu Toolchain options, iremos realizar praticamente as mesmas configurações do nosso toolchain:

* **Toolchain Type**: External toolchain; 
* **Toolchain**: Custom Toolchain; 
*  **Toolchain origin**: Pre-isntalled toolchain; 
* **Toolchain path \(ATENÇÃO\)**: Digite o path completo do seu toolchain, não utilize o path relativo `∼/`. 
  * Ex:`/home/gbs/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/`

{% hint style="success" %}
Uma dica, durante esse tipo de processo é necessário utilizar o caminho absoluto dos arquivos/diretórios. Para facilitar e evitar typos é interessante abrir outro terminal \(`ctrl+t`\) e navegar até o diretório e em seguinda execute o comando `pwd`. Ele retornará o caminho absoluto até a localização que você esta, então basta copiar e colar no outro terminal.
{% endhint %}



* **External toolchain gcc version**: 6.x; 
* **External toolchain kernel headers series**: 4.10.x; 
* **External toolchain C library**: glibc/eglibc; 
* **Toolchain has C++ Support**:  _selecionar;_ 
* _**Copy gdb server to the Target**:_  selecionar;

#### Menu: _System Configuration_

* **System hostname**: Pode colocar o nome que desejar; 
* **System banner**: Idem. Será a mensagem de boas-vindas assim que o terminal é exibido; 
* **Init system**: BusyBox; 
* **/dev management**: Dynamic using devtmpfs only; 
* **Enable root login with password**: \* selecione. _Nota_: _ao criar este RootFs, somente o usuário root estará disponível;_

#### Menu_: Kernel_

* **Kernel Version**: Custom version; 
* **Kernel version \(2a opção logo abaixo\)**: 4.14.y. Esta é a mesma versão dos fontes baixados do repositório da RPi; 
* **Linux Kernel Tools**: 
  * **cpupower**: algumas ferramentas que permitem gerenciar o desempenho / consumo da cpu no kernel;
  *  **gpio**: ferramentas para manipulação de gpio; 
  * **perf**: ferramenta utilizada para profilling do sistema;

#### Menu: _Target Packages_

O menu _Target packages_ é responsável por fornecer a maioria das aplicações de usuário. Por enquanto, selecionaremos algumas básicas. No entanto, caso necessitemos durante o desenvolvimento de softwares, podemos adicionar alguma aplicação específica no futuro:

* **Audio and Video Applications**: bluez-alsa, hcitop; 
* **Compressors and Decompressors**: bzip2, zip; 
* **Debugging, profilling and benchmark**: gdb-&gt;full debuger, memstat, rt-tests;
* **Development Tools**: binutils, git, make, tree; 
* **Filesystems and Flash Utilitie**s: sshfs, ntfs-3g;
* **Hardware handling**
  * **Firmware**: rpi-bt-firmware, rpi-firmware, Install DTB overlays, rpi-wifi-firmware; 
  * **Interpreter languages and scripting**: php, python; 
* **Libraries-&gt;Hardware Handling**: bcm2835, WiringPi; 
* **Netwok Applications**: bluez-utils 5.x, dhcpcd, lightttpd, openssh, wpa\_supplicant, wpa\_cli binary; 
* **Shell and utilities**: sudo; 
* **System Tools**: htop;
* **Text edtior and viewers**: nano;

Perceba o quanto de personalização, entre drivers, ferramentas, softwares, é possível selecionar ou não, no intuito de customizar um sistema Linux embarcado.

#### Menu: _Filesystem Image_

* **Exact Size**: 1g \(opcional o tamanho\). 

Infelizmente o buildroot não estima o menor tamanho possível da imagem final do Rootfs. Até porque, considerando sistemas embarcados, a ideia é sempre utilizar o máximo do espaço disponível que a placa oferece. Assim, sinta-se à vontade para selecionar o tamanho final da sua imagem do RootFS. Se der algum erro no final da compilação, dizendo que a imagem não cabe no tamanho selecionado, não se preocupe. Apenas abra o menuconfig novamente, aumente o tamanho e recompile. A menos que você dê um clean, o buildroot não irá apagar tudo que já foi compilado.

Certifique-se de que não haja nenhum Bootloader selecionado no menu Bootloader. Pois já compilamos o U-Boot. Saia e SALVE as configurações. 

{% hint style="warning" %}
**ATENÇÃO**: antes de compilar, ainda é necessário definir o local dos fontes do kernel \(que você já baixou\). Crie e edite o arquivo `local.mk`
{% endhint %}

```text
nano local.mk
```

Insira a seguinte linha, lembre-se de utilizar o caminho absoluto

```text
LINUX_OVERRIDE_SRCDIR=/home/gbs/dsle20/kernel/linux-rpi-4.14.y
```

 indicando o path para os fontes do kernel. 

_Note que é necessário utilizar o caminho completo e altere o nome de usuário \(**gbs**\) de acordo com seu usuário._ 

Por fim, compile as imagens:

```text
make -j4
```

Assim que a compilação terminar, verifique os arquivos gerados dentro da pasta `output/image`:

* **bcm2710-rpi-3-b.dtb**: Device Tree compilado para a RPi 3 Model B; 
* **bcm2710-rpi-3-b-plus.dtb**: Device Tree compilado para a RPi 3 Model B Plus; 
* **bcm2710-rpi-cm3.dtb**: Device Tree compilado para a RPi Compute Module \(ComputeModule\); 
* **boot.vfat**: Partição de boot com todos os arquivos necessários para bootar o sistema recém-criado; 
* **rootfs.ext2**: Partição de montagem do RootFS; Contém todos os arquivos, programas, bibliotecas que o kernel Linux precisa para executar, bem como as aplicações e ferramentas extras selecionadas; 
* **rootfs.ext4**: Cópia da partição acima, no entanto esta utiliza o sistema de arquivos _ext4_;
* **rpi-firmware**: Pasta com todos os binários e arquivos de configuração necessários para bootar a RPi; 
* **sdcard.img**: Imagem pronta com todos arquivos gerados pelo Buildroot. Contém ambas partições, boot e rootfs. Pronta para gravar num cartão SD ou pendrive ou HD;
* **zImage**: Imagem compilada do kernel Linux;

_Obs: Caso o U-Boot fosse selecionado antes do processo de build, nessa mesma pasta existiria um arquivo `u-boot.bin`, imagem do U-B_oot.





\_\_



