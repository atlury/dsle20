# Nativo vs. Cross-Compiling

As ferramentas de desenvolvimento que normalmente acompanham um desktop GNU/Linux são chamadas de toolchain nativo. Ou seja, são aquelas que fazem a compilação para a arquitetura da máquina _host_.

Este toolchain roda na sua máquina e compila um código para ser executado em sua máquina ou em uma máquina que possua a mesma arquitetura que a sua, normalmente uma arquitetura _x86_ nos desktops convencionais.

De forma semelhante, os processadores embarcados como ARM, MIPS, SuperH, Blackfin, Coldfire, PowerPC, SPARC e etc. Possuem também seu compilador nativo. Desta forma, é possível realizar a codificação diretamente no processador e então compilar utilizando a toolchain nativa deste processador.

Nota-se que este processo é feito internamente na plataforma _target,_ ou seja, esse processo é executado dentro da placa de desenvolvimento. Assim, é fácil perceber os problemas deste tipo de abordagem, uma vez que o _hardware_ que utilizamos em sistemas embarcados possuem recursos limitados do ponto de vista de execução. De forma geral, possuem baixa memória, baixo armazenamento, baixo processamento e etc.

Desta forma, encontramos alguns problemas ao executar a compilação nativa dentro da plataforma embarcada, tanto do ponto de vista do tempo de execução desta compilação, que pode ser um gargalo da operação, tornando-a demorada e gerando tempo ocioso para o desenvolvedor. Além disso, é normal que os sistemas embarcados apresentem um armazenamento restritivo, tornando inviável o armazenamento da toolchain, ferramentas de desenvolvimento, código fonte, arquivos de compilação, auxiliares e etc, dentro da plataforma embarcada. 

![](../.gitbook/assets/image%20%2819%29.png)

Não obstante, há um problema de logística que envolve o desenvolvimento nativo em sistemas embarcados, e este tem relação com as ferramentas de desenvolvimento. Normalmente quando realizamos o desenvolvimento de _software_ estamos utilizando programas que auxiliem na codificação, como IDEs, editores de texto, ferramentas de linkagem e indexação e até mesmo interfaces gráficas para a criação dos sistemas. Todo esse suporte esta disponível nos desktops, e a passagem de todos esses arquivos para o sistema embarcado é muitas vezes indesejável ou mesmo inviável.

Desta forma, normalmente é utilizado - e recomendado - o desenvolvimento do sistema nos desktops normais e a passagem do programa já compilado para a plataforma embarcada. Evitando assim, os problemas relacionados ao tempo de compilação, espaço de armazenamento, ferramentas de desenvolvimento e facilitando também a programação, já que é comum realizarmos diversos testes durante a codificação.

Para tal, é necessário uma toolchain que realize a compilação de um código desenvolvido na arquitetura da plataforma _host_ \(desktop\) para a arquitetura da plataforma _target_ \(sistema embarcado\). Este toolchain é chamado de _cross-compiling toolchain._ 

