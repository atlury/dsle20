# Bootloader

O bootloader é um pequeno pedaço de código que normalmente é a primeira coisa a ser executada ao ligar um computador, ou sistemas em geral. Sua principais atribuições e funções são:

* Inicializar o hardware base;
* Carregar o kernel;
* Passar o controle para a aplicação;

De uma forma mais precisa, o bootloader deve realizar a inicialização e configuração básica do hardware. Isto é, inicializar a  CPU, as GPIOs as memórias e etc. 

Em seguida, deve carregar um código de aplicação, em geral são arquivos binários em especial o kernel do sistema operacional. Este código é carrega, em geral, de uma memória não-volátil, por exemplo: um HDD, SDD, da rede, ou mesmo de um flash drive. Este é carregado para a RAM e executado.

Por fim, deve passar o controle da CPU para o programa carregado, seja ele uma aplicação ou um sistema operacional.

Assim, para entender melhor o funcionamento e a utilizade dos bootloaders, vamos apresentar os processos de boot das principais arquiteturas de processadores.

### Boot em arquitetura X86 baseado em BIOS

Processadores com arquitetura x86, normalmente possuem uma memória interna não-volatil. Esta em geral, é uma ROM com um firmware dedicado gravado nela. Este firmware é o que costumeiramente chamamos de BIOS do computador.

O diagrama a seguir, descreve as principais etapas do processo de boot de uma processador x86.

![](../.gitbook/assets/image%20%2826%29.png)

A BIOS, é responsável pela inicialização básica de hardware, e em seguida procurar, dentre as opções disponíveis de armazenamento não-volatil, normalmente disco rígidos, por um programa bem pequeno na MBR \(Master Boot Record\). 

A MBR é gravada nos primeiros 512 bytes do disco e contém informações de particionamento. Por ser uma memória extremamente pequena, realiza o carregamento do bootloader de primeiro estágio para dentro da memória RAM. Este é responsável apenas por encontrar quem é a partição ativa, através da tabela da MBR.

Então, é carregado o bootloader de segundo estágio. Este é mais completo, e consegue carregar alguns drivers para ler os tipos da partição e outras funções específicas. E então é capaz de ler a imagem do kernel e carrega-la na RAM e por fim executa-la.

Alguns exemplos de bootloaders de segundo estágio são por exemplo:

* \*\*\*\*[**GRUB** \(Grand Unified Bootloader\)](https://www.gnu.org/software/grub/): que é o padrão utilizado em algumas distribuições GNU/Linux como o próprio Ubuntu. É um dos bootloaders mais completas utilizado tanto em desktops como em servidores.
* \*\*\*\*[**Syslinux**](https://www.syslinux.org/): é um bootloader muito utilizado, principalmente em sistemas com boot de mídias removíveis e boots via rede. É por exemplo disponibilizado em distribuições como o Arch Linux.
* \*\*\*\*[**LILO** \(Linux Loader\)](https://lilo.alioth.debian.org/): era um dos bootloaders padrão, sendo adotado em distribuições como o Debian. Porém, com o crescimento do Syslinux e do GRUB/2 acabou ficando obsoleto.











