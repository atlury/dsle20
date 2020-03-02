# Arquitetura Geral

A figura a seguir, apresenta uma visão geral do kernel Linux. Basicamente, é ele quem gerencia todo o hardware do sistema e as comunicações entre as partes, uma vez que o usuário não possui acesso direto à nenhum componente.

![](../../.gitbook/assets/image%20%2821%29.png)

Além disso, ele gerencia recursos como CPU, Memória, I/O, HD, qualquer dispositivo de hardware conectado ou built-in do sistemas. Ele gerencia isso através de um conjunto de APIs bem portáteis, que são independentes da arquitetura e do hardware, lembra-se que no início do treinamento foi comentado que uma das grandes contribuições do Ritchie foi portar o UNIX pra linguagem C e deixá-lo modular, e este princípio é mantido até os dias de hoje e isto torma tudo mais simples e abstraído.

Outras responsabilidades do kernel, é por exemplo, fazer o tratamento de acesso concorrente de hardware de diferentes aplicações. Normalmente um dispotivo como uma porta serial, interface de rede é utilizada por mais de uma aplicação, é responsabilidade do kernel fazer essa "multiplexação" de componentes.

Usualmente tem-se uma chamada de sistema da aplicação, então o kernel atende-a ou insere a mesma na fila de execução, gerencia o hardware, como leitura da porta serial por exemplo. Então, o hardware notifica o kernel que o dado pode ser lido e o kernel exporta o dado para aplicação. Ou uma interrupção também de hardware, quando algum evento ocorre, o hardware gera uma notificação para o kernel e o mesmo realiza o tratamento.

