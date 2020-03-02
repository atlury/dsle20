# Hardware

## O Hardware \(target\)

O target ou hardware é onde de fato roda nossa aplicação embarda. Ele deve conter os itens apresentados na seção anterior \(exceto pela toolchain\). Mas em geral, trata-se da nossa plataforma de desenvolvimento onde vamos rodar nossa aplicação, ler sensores, enviar dados, fazer telemetria e etc.

![](../.gitbook/assets/image%20%289%29.png)

### Processadores

Atualmente o kernel Linux suporta mais de 30 arquiteturas de processadores, como: x86, x86-64, ARM, MIPS, SuperH, Blackfin, Coldfire, PowerPC, SPARC e etc. 

O Linux foi originalmente projetado para trabalhar com processadores que possuiam unidade de gerenciamento de memória \(MMU\). Não sendo projetado para microcontroladores. Contudo, o projeto uClinux foi criado para dar suporte a CPUs sem MMU, tendo algumas limitações, mas ainda assim funcional para casos específicos.

### Memória RAM e Armazenamento

Um sistema bem básico pode funcionar com 8MB de RAM, mas um sistema mais realístico necessita de pelo menos 32MB de RAM. Vai depender muito do tipo e tamanho da aplicação. 

Sistemas muito enxutos podem até rodar com 2MB de armazenamento, as vezes até menos, mas para isso é preciso limitar e enxugar muito o kernel Linux e claro que depende também do tamanho da aplicação.

Ele apresenta suporte para a maioria dos armazenamentos, como: flash NAND e NOR, disco rígido, cartões SD/MMC e eMMC e etc.

### Comunicação

O Linux suporta muitos barramentos comuns em sistemas embarcados: I2C, SPI, CAN, USB, etc. E também os principais protocolos de rede: Ethernet, Wi-Fi, Bluetooth, IPv4, IPv6, TCP, UDP, etc. 

Se o barramento ou protocolo não possuir restrições de licença, é bem provável que esteja implementado no kernel. E isso vale para hardware em geral, se não tiver nenhuma restrição de licença, o driver estará implementado no kernel Linux, pronto para ser utilizado. É por isso que quando você instala uma distruibuição em um PC, é muito comum não precisar de driver nenhum.

### Critérios de seleção

* Certifique-se de que o hardware escolhido seja suportado pelo kernel Linux e por algum dos bootloaders open-source, caso contrário será necessário fazer o porte e este é um trabalho árduo.
* Suporte nas versões oficias dos projetos \(kernel e bootloader\): maior qualidade, novas versões disponíveis.
* A diferença entre um hardware suportado na árvore oficial do kernel e outro não suportado de forma oficial, PODE trazer grandes consequências no custo e tempo de desenvolvimento!







