# Toolchain

Nesta etapa iremos abordar as características e conceitos sobre a Toolchain. De forma geral, esta faz parte da máquina de desenvolvimento \(notebook, desktop e etc\), que também chamamos de host. Mas há também a possibilidade da toolchain estar dentro do próprio target, é algo bem menos comum, mas é uma alternativa.

![](../.gitbook/assets/image%20%286%29.png)

Basicamente, o toolchain é o conjunto de ferramentas necessárias para desenvolver seu produto, seja ele um software ou um sistema completo.

Quando instalamos um sistema e este acompanha um certo toolchain para gerar código \(como o Linux por exemplo\), ou instalamos um toolchain por conta própria, este toolchain irá gerar código para a mesma arquitetura da máquina em que ele foi instalado. Por exemplo, se instalamos uma toolchain no nosso processador x86, esta gera binários para nossa própria arquitetura. Assim, recebendo o nome de toolchain nativo, já que gera códigos para sua arquitetura nativa.

No entanto, normalmente em sistemas embarcados não é interessante utilizar um toolchain nativo, por diversos motivos. Por exemplo, seu target pode ter limitações de memória e espaço, a velocidade de compilação no target é muito mais lenta devido a limitação de processamento e etc.

Desta forma, é recomendado a utilização de um cross-compiling toolchain. Este por sua vez, realiza a compilação para outra arquitetura, ou seja, no cenário do nosso computador x86 conseguiriamos gerar código para uma outra plataforma, por exemplo ARM.

![](../.gitbook/assets/image%20%2816%29.png)

Basicamento o toolchain é composto por um compilador, assembler e linker. Como por exemplo, o compilador _gcc,_ o assembler e linker da _binutils, a_ biblioteca padrão C, como a _glibc, uclib_ ou alguma de suas variações, os headers do kernel e etc. 

Enfim, essa é uma idéia geral, no decorrer do treinamento iremos explorar cada um desses tópicos mais profundamente, não somente na teoria mas também na prática.

