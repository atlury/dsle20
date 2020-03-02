# Bootloaders em Sistemas Embarcados

### Boot em arquiteturas ARM

O processo de boot basico de um processador ARM, está exemplificado no diagrama a seguir:

![](../.gitbook/assets/image%20%2815%29.png)

De forma geral, o processador possui um código de boot gravado em uma ROM interna, tal como o caso anterior. Ao ser energizado, o processador executa o código desta ROM que é responsável por encontrar o SPL \(_Secoundary Program Loader_\). 

Apesar de ter o nome de secundário, este é na verdade o bootloader de primeiro estágio e está presente em uma memória não-volátil. Em  geral, se encontra em uma partição primária da NAND Flash, MMC, ou SD Card e normalmente é a partição boot com FAT32.

Então, o boot code encontra o SPL e carrega-o em uma memória RAM interna também do processador, normalmente uma SRAM ou IRAM. Como o tamanho da SRAM é limitado, comumente, o SPL precisa inicializar o hardware em geral, mas principalmente a memória RAM e carregar o bootloader regular, isto é, carregar o bootloader de segundo estágio, do armazenamento não-volátil para a RAM. O principal fator para os bootloaders regulares não estarem na SRAM, precisando ser carregados na RAM, é que eles costumam oferecer outras funcionalidades, tornando-se maiores.

Então, o bootloader regular carrega o kernel para a memória RAM e este passa a ter controle sobre o processador. A partir deste momento, o bootloader não tem mais função e é desalocado da RAM, tal como no caso do x86.

### Boot em ARM Microchip AT91

Para exemplificar melhor o processo de boot dos processadores embarcados, vamos avaliar outra CPU ARM. No caso, o chip em questão é o AT91 da Microchip \(ex-Atmel\), o processo de boot esta ilustrado na figura a seguir.

![](../.gitbook/assets/image%20%285%29.png)

É possível nota que o processo não é muito diferente dos já citados, ARM geral e x86. Primeiramente, o boot code da ROM interna é executado e busca pelo bootloader de primeiro estágio. Em seguida, este é carregado e executado na RAM interna de 4KB. Particularmente a Atmel gostava de chamar seus bootloaders de primeiro estágio de ATxxBootstrap, tal como os bootloaders de primeiro estágio das arquiteturas x86 baseadas em BIOS.

O bootstrap, assim como os demais,  é responsável por inicializar o hadware básico, mas principalmente a controladora de DRAM,  para poder carregar o bootloader na RAM ou DRAM e executa-lo.

Nos processadores da Atmel/Microchip o bootloader é o U-boot que é executado na RAM. O U-boot é um bootloader bem popular, com varias funcionalidades interessantes, que serão abordadas ao longo do treinamento. 

Então, por fim, o bootloader encontra o kernel e faz o carregamento dele na RAM, passando o controle da CPU para ele.

Este mesmo processo esta presente em outros chips como: processadores ARM da Texas Instruments \(por ex: ARM TI OMAP3\), processadores Freescale \(por ex: i.MX5/6\) e tantos outros. Cada um com suas peculiaridades, mas o processo é, em geral, na mesma estrutura dos apresentados nesta sessão.

### Bootloaders para Sistemas Linux Embarcado

Durante as seções anteriores, foram apresentados algums processos de boot, principalmente da arquitetura ARM, que é a adotada para este treinamento. Uma vez que estamos utilizando como plataforma embarcada a RPi3 que possui um processador ARM da Broadcom.

O bootloader de primeiro estágio é sempre relacionado a arquitetura do processador escolhido, desta forma, estamos mais interessados nos bootloaders de segundo estágio. Uma vez que estes, podem ser modificados e são uma escolha do desenvolvedor.

Existem alguns bootloaders disponiveis no mercado e nas comunidades, e diversos deles são multi-arquitetura. Contudo, os dois bootloaders regulares mais usados, em projetos embarcados, são o [U-Boot](http://denx.de/wiki/U-Boot/) e o [Barebox](https://www.barebox.org/).

O U-Boot é o bootloader mais utilizado, sendo encontrado em diversos projetos e sendo a escolha mais popular entre os desenvolvedores. Ele apresenta suporte a diversas arquiteturas incluindo ARM, Blackfin, RISC-V e x86. Esta presente no mercado a mais de 20 anos, sendo utilizado tanto como bootloader de primeiro estágio como de segundo. Além disso, tem comunidade ativa de desenvolvimento e por isso é o padrão em diversas fabricantes de SoC.

O Barebox, por sua vez, foi anunciado como o sucessor do U-Boot, no seu início ganhou uma certa atenção, desenvolvedores começaram a tocar o projeto e manter uma comunidade ativa. Contudo, com seu surgimento, o u-boot passou a ser melhorado,  provavelmente devido a concorrência e o anúncio de seu sucessor. Por isso, o barebox ficou meio que de lado e o U-Boot continua sendo o mais usado.

Assim, durante este treinamento vamos adotar o U-Boot como bootloader para o nosso sistema embarcado.

