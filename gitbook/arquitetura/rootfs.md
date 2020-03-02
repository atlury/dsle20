# RootFS



É a partição onde o sistema está instalado. Contém todas as bibliotecas que o kernel necessita para ser executado. 

![](../.gitbook/assets/image%20%2813%29.png)

Contém todos os arquivos necessários para inicialização do sistema, inclusive bibliotecas do usuário e aplicações \(programas instalados\).

Dentro do RootFS são encontrados diversos componentes básicos, dentre estes os principais são, todas as bibliotecas do sistema, isto é, as bibliotecas utilizados pelo sistema, pelos programas instalados e mesmo as bilbiotecas de terceiros.

Além das bibliotecas built-in, são presentes dentro do RootFS também, as bibliotecas utilizadas pela aplicação, sejam essas bibliotecas _in-house_ ou bibliotecas proprietárias.

São encontrados dentro do RootFS, além dos arquivos de configuração, os arquivos de inicialização do sistema.

**Componentes básicos:**

* Bibliotecas do sistema;
* Arquivos de inicialização;
* Bibliotecas de aplicação.

O RootFS é comumente montado pelo próprio Kernel Linux, quando este entra em operação, logo após o processo de booting. Portando, não é possível, tão pouco necessário, realizar a montagem deste sistema através do comando `mount`. 

Além disso, é possível, através de passagem de parâmetros do Kernel Linux, estipular onde o RootFS será inicializado. 

Dentre as possibilidades, destacam-se algumas opções interessantes, como a montagem do RootFS juntamente a imagem do Kernel Linux, o que em geral é uma opções que acelerá o processo de boot e de operação, já que o RootFS já estará presente na memórias RAM, contudo há um conjunto de limitações para esta opção. 

Outra possibilidade, é a montagem deste sistema através do protocolo NFS, podendo montar o RootFS na máquina _host_, ao contrário de ser montado no _target_.





