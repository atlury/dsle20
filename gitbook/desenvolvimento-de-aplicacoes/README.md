# Desenvolvimento de Aplicações

Quando trata-se de desenvolvimento de aplicações para Linux embarcado existe uma regra de outro, como já mencionado:

> Um Sistema Linux Embarcado é apenas um Sistema Linux normal, com uma limitada seleção de componentes!

Isto significa basicamente que desenvolver par aum Sistema Linux Embarcado, é a mesma coisa que desenvolver para um desktop Linux, ou seja, uma aplicação normal em Linux.

Todo o conhecimento de programação é reutilizável. Desta forma, é fácil reaproveitar sem nenhuma adaptação adicional os conceitos e práticas sobre Sistemas Operacionais, Threads, Estruturas de Dado e etc.

Além disso, outra característica que garante o desempenho enquanto se desenvolve para Linux embarcado é o fato da maioria das bibliotecas existentes para desktop, que é uma quantidade colossal, podem ser cross-compiladas para um sistema embarcado. Considerando, é claro, exclusividades de arquitetura, diferença de performance, armazenamento, memória e etc.

Este fato, da regra de ouro, é crucial para uma empresa ou para desenvolvedores. Visto que é possível começar o desenvolvimento da aplicação no seu desktop x86, antes mesmo de definir qual sera o hardware. Ou seja, muitas vezes é possível levantar todas as características que deveram ser implementadas, realizar o desenvolvimento \(logicamente em alguns pontos são necessários Mocks\) e então especificar o hardware para rodar a aplicação.

Isso poupa muito tempo, pois não é necessário ficar desenvolvendo código direto na plataforma, que geralmente demora mais por diversos fatores, além de garantir certo conforto para o desenvolvedor. Por exemplo, não há a necessidade de ficar realizando comunicações de hardware ou lendo diversos manuais antes de começar o desenvolvimento, a camada entre software e hardware é bem mais definida, diferentemente de desenvolvimento baremetal.

### 

### 

### 

