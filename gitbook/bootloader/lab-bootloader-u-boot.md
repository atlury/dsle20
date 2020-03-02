# \[LAB\] Bootloader  \(U-Boot\)

### Baixando o U-Boot

Assim como nas atividades anteriores, os fontes do **U-Boot** foram previamente baixados e encontram-se no diretório `∼/dsle20/dl/bootloader`. Crie um diretório chamado `bootloader` dentro da pasta `∼/dsle20` e, em seguida, extraia o **U-boot** no diretório criado:

```bash
cd ~/dsle20/
mkdir bootloader && cd bootloader
unzip ~/dsle20/dl/bootloader/u-boot-master.zip
```

Acesse o diretório do **U-Boot** e liste as configurações pré-definidas para as diversas plataformas suportadas pelo **U-Boot**. Devido à extensão da lista de configurações, é recomendado a utilização do comando `less`. Este comando permite a visualização do conteúdo de um arquivo ou output de algum comando, por meio de páginas do tamanho da tela:

```bash
cd u-boot-master
ls configs/ | less
```

```bash
10m50_defconfig
3c120_defconfig
A10-OLinuXino-Lime_defconfig
A10s-OLinuXino-M_defconfig
A13-OLinuXino_defconfig
A13-OLinuXinoM_defconfig
A20-Olimex-SOM204-EVB_defconfig
A20-Olimex-SOM204-EVB-eMMC_defconfig
A20-Olimex-SOM-EVB_defconfig
A20-OLinuXino-Lime2_defconfig
A20-OLinuXino-Lime2-eMMC_defconfig
A20-OLinuXino-Lime_defconfig
A20-OLinuXino_MICRO_defconfig
A20-OLinuXino_MICRO-eMMC_defconfig
A33-OLinuXino_defconfig
a64-olinuxino_defconfig
adp-ae3xx_defconfig
adp-ag101p_defconfig
Ainol_AW1_defconfig
alt_defconfig
am335x_baltos_defconfig
am335x_boneblack_defconfig
am335x_boneblack_vboot_defconfig
:
```

Use as teclas _espaço_, _b_ e _q_ para exibir a próxima página, a página anterior ou encerrar a visualização, respectivamente. Uma vez que o **U-Boot** suporta diversas arquiteturas de hardware diferentes, é necessário selecionar uma delas antes de compilar o programa. Selecione a configuração `rpi_3_32b_defconfig` e compile o **U-Boot**, indicando o prefixo do cross-compilador conforme configurado anteriormente:

```bash
make rpi_3_32b_defconfig
make -j2 CROSS_COMPILE=arm-linux-
```

Verifique o arquivo criado, `u-boot.bin`, através do comando:

```bash
ls -l u-boot.bin
```

### Gravando o U-Boot

O processo de gravação do bootloader é dependente de hardware, específico para cada plataforma. Conforme visto em aula, a RPi 3 busca o bootloader e firmwares relacionados ao processo de boot na partição `boot` do cartão micro SD. Assim, dois procedimentos são necessários para gravar e ativar o **U-Boot** no processo de boot da RPi:

1. Copiar o binário `u-boot.bin` para a partição `boot` do cartão micro SD;
2. Configurar o arquivo `config.txt` para que o firmware da GPU, `start.elf`, execute o `U-Boot` no lugar do kernel Linux;

É possível copiar o arquivo `u-boot.bin` para o cartão micro SD de várias maneiras. Visto que já existe uma configuração de rede entre a máquina de desenvolvimento e a RPi, realizada em atividades anteriores, o arquivo será copiado via comando `scp`:

```bash
scp u-boot.bin pi@10.1.1.100:/home/pi/
```

Logue na RPi, via SSH, e copie o arquivo do diretório `home` para o diretório `boot` com privilégios de administrador:

```bash
ssh pi@10.1.1.100
```

```bash
sudo cp u-boot.bin /boot/
ls /boot
```

```text
bcm2708-rpi-0-w.dtb
bcm2710-rpi-cm3.dtb
bcm2708-rpi-b.dtb
bootcode.bin
bcm2708-rpi-b-plus.dtb cmdline.txt
bcm2708-rpi-cm.dtb
bcm2709-rpi-2-b.dtb
bcm2710-rpi-3-b.dtb
config . txt
COPYING.linux
fixup_cd.dat
bcm2710-rpi-3-b-plus.dtb fixup .dat
fixup_db.dat
overlays
fixup_x.dat
start_cd. elf
issue. txt
start_db. elf
kernel7.img
start . elf
kernel.img
start_x . elf
LICENCE.broadcom 
u-boot.bin
```

Feito isso, adicione a seguinte linha no final do arquivo `config.txt`:

```bash
sudo nano /boot/config. txt
[..]
dtparam=audio=on
enable_uart=1
kernel=u-boot.bin
```

O parâmetro acima especifica qual imagem do kernel, o firmware `start.elf` deve carregar. Neste caso, a imagem é o próprio **U-Boot**. Após salvar as alterações no arquivo, renicie a RPi \(`sudo reboot`\).

{% hint style="warning" %}
Atenção, só reinicie a RPi se você possui uma conexão serial funcional entre ela e a máquina de desenvolvimento, pois a única interação com o menu do **U-Boot**, por enquanto, é via serial.
{% endhint %}

Por último, interrompa o processo de boot do **U-Boot** pressionando uma tecla para entrar no shell:

```text
U-Boot 2018.07-rc1 (Oct 3 2019 - 19:50:41 -0300)
DRAM: 948 MiB
RPI 3 Model B (0xa02082)
MMC: mmc@7e202000: 0, sdhci@7e300000: 1
Loading Environment from FAT... ∗∗∗ Warning - bad CRC, using default environment
Failed ( -5)
In :
serial
Out: vidconsole
Err: vidconsole
Net: No ethernet found.
starting USB...
USB0: scanning bus 0 for devices ... 3 USB Device(s) found
scanning usb for storage devices ... 0 Storage Device(s) found
Hit any key to stop autoboot: 0
U-Boot>
```

### Configurando variáveis de ambiente no U-Boot

Após obter acesso ao shell do **U-Boot**, configure algumas variáveis de ambiente básicas para manter o sistema da RPi bootável, pois por padrão, o **U-Boot** não identifica a imagem do kernel automaticamente. Inicialmente, desative o processo de _autoboot_:

{% code title="U-Boot" %}
```bash
setenv bootdelay -1
```
{% endcode %}

Futuramente, o **U-Boot** será configurado para carregar o kernel pela rede, de uma pasta de sua máquina de desenvolvimento. Portanto, configure o endereço _IP_ da RPi e máquina de desenvolvimento:

{% code title="U-Boot" %}
```bash
setenv ipaddr 10.1.1.100
setenv serverip 10.1.1.1
```
{% endcode %}

Por fim, salve as alterações realizados no disco, de tal forma que elas estejam disponíveis na próxima inicialização, e reinicie o RPi:

{% code title="U-Boot" %}
```bash
saveenv
reset
```
{% endcode %}

Após enviar o comando `saveenv`, o **U-Boot** cria um arquivo de configuração chamado `u-boot.env` que contém todas as variáveis de ambiente definidas. Após reiniciar novamente a RPi, o processo de _autoboot_ não deve ser inicializado e o controle do shell exibido logo em seguida. Para “bootar” o **Raspbian** novamente, pelo **U-Boot**, algumas configurações adicionais são necessárias. O primeiro passo, é carregar um arquivo \(imagem do kernel\) do cartão micro SD para a RAM em um endereço específico. Utilize o seguinte comando:

{% code title="U-Boot" %}
```bash
fatload mmc 0:1 ${kernel_addr_r} kernel7.img
```
{% endcode %}

O comando acima carrega um arquivo binário de um sistema de arquivos FAT \(_fatload_\). Os parâmetros são:

* **mmc**: o dispositivo de armazenamento onde se encontra o binário \(cartão SD\);
* **0**: o número do dispositivo, pois muitas vezes o seu target pode possuir mais de um dispositivo de armazenamento;
* **1**: o número da partição no dispositivo \(partições são enumeradas a partir de 1\);
* **${kernel\_addr\_r}**: o endereço inicial na RAM onde deseja-se carregar o binário, neste caso a configuração do **U-Boot** já fornece uma variável de ambiente com o endereço inicial da RAM, para carregar o kernel \(_${kernel\_addr\_r}_\);
* **kernel7.img**: o binário que se deseja carregar. Lembrando que por padrão, a partição boot do **Raspbian** fornece duas imagens: `kernel.img` e `kernel7.img`. A primeira é para as versões de hw anteriores \(RPi e RPi 2\) e a última \(`kernel7.img`\) é a imagem para as placas da RPi 3 em diante;

Algumas plataformas possuem dispositivos de hardware que não podem ser identificados dinamicamente pelo kernel. Em tais casos, é necessário um mecanismo para informar o kernel sobre dispositivos presentes no sistema. Atualmente, o mecanismo utilizado para tal função é chamado de _Device Tree_, que é uma estrutura de dados que descreve a topologia e configuração de hardware no sistema. Analisaremos esse mecanismo em breve durante o curso.

A RPI 3 é um tipo de plataforma que utiliza esse recurso e bootloader é o responsável por passar o _Device Tree_ para o kernel e, portanto, é necessário fazer o loading desse arquivo no **U-Boot**. O processo é o mesmo anterior, porém com algumas alterações nos parâmetros:

{% hint style="warning" %}
Caso esteja utilizando a RPi 3B+ substitua o device tree utilizado pelo device tree `bcm2710-rpi-3-b-plus.dtb`, ao longo do treinamento.
{% endhint %}

{% code title="U-Boot" %}
```bash
fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b.dtb
```
{% endcode %}

* **mmc**: o dispositivo de armazenamento onde se encontra o binário \(cartão SD\);
* **0**: o número do dispositivo, pois muitas vezes o seu target pode possuir mais de um dispositivo de armazenamento;
* **1**: o número da partição no dispositivo \(partições são enumeradas a partir de 1\);
* **${fdt\_addr\_r}**: o endereço inicial na RAM onde deseja-se carregar o binário, neste caso a configuração do **U-Boot** já fornece uma variável de ambiente com o endereço inicial da RAM, para carregar o _Flattened Device Tree_ \(_${fdt\_addr\_r}_\);
* **bcm2710-rpi-3-b.dtb**: arquivo compilado do Device Tree \(_dtb_\) referente à RPi 3 B;

Estes são basicamente os únicos arquivos necessários para realizar o boot do Raspbian via **U-Boot**. Entretanto, além dos arquivos, ainda é necessário configurar alguns parâmetros do kernel. Configure a variável de ambiente `bootargs`, responsável por armazenar parâmetros para serem passados ao kernel:

{% code title="U-Boot" %}
```bash
setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
```
{% endcode %}

* **8250.nr\_uarts=1**: número de portas seriais para serem registradas \(utilizadas\);
* **root=/dev/mmcblk0p2**: path para a localização do **RootFS** \(_Root FileSystem_\);
* **rootwait**: espera \(indefinidamente\) a inicialização dispositivo onde o **RootFS** está localizado. _mmcblk0_ refere-se ao micro SD e _p2_ à partição número 2, visto que a primeira é a partição de `boot`;
* **console=ttyS0,115200**: redireciona um console para a porta serial `ttyS0` \(_mini UART_ da RPi 3\), e seu respectivo baudrate;

Finalmente, com as configurações acima realizadas, “basta” dar o comando de boot:

{% code title="U-Boot" %}
```bash
bootz ${kernel_addr_r} - ${fdt_addr_r}
```
{% endcode %}

onde:

* **kernel\_addr\_r**: é o endereço na RAM onde está carregada a imagem do kernel;
* **-**: seria o endereço na RAM da imagem _initrd_, que é uma imagem do **RootFS**. É possível carrega-lo na RAM, assim como kernel e _Device Tree_. No entanto, no momento a RPi não possui nenhuma imagem desse tipo. Ela será gerada em atividades futuras. Este parâmetro é opcional;
* **fdt\_addr\_r** é o endereço na RAM onde está carregado o compilado do _Device Tree_;

Se os comandos acima foram executados corretamente, você deverá enxergar o loading do kernel pela serial.

### Criando um script de inicialização no U-Boot

O **U-Boot** possui uma funcionalidade que permite que o usuário crie scripts contendo sequência de comandos, como os executados acima. Na sua máquina de desenvolvimento, navegue até o diretório do U-Boot e crie o seguinte arquivo:

```bash
cd ~/dsle20/bootloader/u-boot-master
gedit rpi3scr.txt
```

Digite \(copie\) todos os comandos novamente no arquivo aberto e em seguida salve-o:

```bash
fatload mmc 0:1 ${kernel_addr_r} kernel7.img
fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b.dtb
setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
bootz ${kernel_addr_r} - ${fdt_addr_r}
```

Em seguida, dentro da pasta tools no diretório do U-Boot, existe uma ferramenta chamada mkimage capaz de criar imagens do **U-Boot**, **kernel**, **RootFS** e inclusive scripts para o **U-Boot**. Digite o seguinte comando:

```bash
tools/mkimage -A arm -O linux -T script -d rpi3scr.txt boot.scr
```

onde os argumentos representam: arquitetura do executável \(_-A_\), sistema operacional \(_-O_\), tipo da imagem \(_-T_\), arquivo de entrada com os comandos digitados no gedit \(_-d_\) e arquivo de saída \(`boot.src`\), que é uma imagem do script.

Após a execução do comando, copie o arquivo `boot.scr` para o diretório `boot` da RPi via `scp`. Se tudo foi realizado corretamente, reinicie a RPi e digite o comando `boot` no shell do **U-Boot**. 

É possível ativar o _autoboot_ através da modificação da variável de ambiente _bootdelay_, que representa o delay em segundos antes de iniciar o boot pelo script `boot.scr`. Se desejar, altera-a, salve as variáveis de ambiente no cartão SD \(`saveen`\) e reinicie o **U-Boot**.

