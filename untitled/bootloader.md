# Bootloader

O bootloader tem como função principal fazer o carregamento de uma aplicação, que normalmente é o kernel do sistema. No nosso caso, o bootloader deve realizar o carregamento do Kernel Linux. 

Este carregamento, é feito de uma memória não volátil. Em seguida, após o carregamento, a aplicação deve ser inicializada segundo os parâmetros do kernel.

**Funções básica do bootloader:**

* Iniciação básica do hardware;
* Carregar uma aplicação \(kernel Linux\) de uma memória não volátil;
* Executar a aplicação.

Bem como outros softwares e firmwares o bootloader apresenta outras funções complementares que foram adicionadas ao longo dos anos, para facilitar usos específicos e aplicações diferentes. Desta forma, o bootloader apresenta um conjunto de funcionalidades extras. Estas funcionalidades variam deste um terminal de comandos para navegação e diagnóstico dos discos e partições, passagem de parâmetros fixos ou temporários para o bootloader e até mesmo a mudança do caminho de busca do kernel, podendo ser uma imagem da rede, por exemplo.

**Funções extras do bootloader:**

* Passagem de parâmetros para o kernel;
* Explorador de arquivos;
* Boot via rede, flash, sd e etc;
* Diagnóstico de hardware.

Os principais bootloader para aplicações x86 são o LILO, Grub e o Syslinux, ao passo que para os sistemas embarcados, em especial para a arquitetura ARM, são o U-Boot, Barebox e o Redoot.

