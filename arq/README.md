---
description: >-
  Descrição dos principais componentes da arquitetura de um sistema Linux
  embarcado.
---

# Arquitetura

## Arquitetura Geral

A arquitetura geral de um sistema com Linux embarcado consiste nos seguintes elementos:

* **Hardware:** o seu produto ou aplicação.
* **Bootloader:** responsável pela inicialização básica do sistema, carregar e executar o kernel Linux.
* **Kernel Linux:** núcleo do sistema operacional, gerenciamento de memória, I/O, pilha de rede, drivers, fornece serviços para a aplicação do usuário.
* **Bibliotecas padrão C:** interface entre o kernel e as aplicações do usuário \(lembre-se o Linux é escrito em C\).
* **Bibliotecas Gerais e aplicações:** são as bibliotecas de terceiros ou in-house, necessárias para a sua aplicação.
* **Toolchain:** Conjunto de ferramentas necessários para gerar os binários para o target \(hardware\). ****

![](../.gitbook/assets/image%20%287%29.png)

A arquitetura básica de um sistema com Linux embarcado é dotada de dois componentes principais, uma máquina de desenvolvimento _host_ e uma plataforma embarcada, o _target_.

O _host_ é, em geral, um computador pessoal que é utilizado para fazer o desenvolvimento do software/aplicação. Assim, é comum que esta máquina tenha todos os recusos para o desenvolvimento, sendo necessários principalmente a presença de uma toolchain para a programação. Isto é, a presença de um conjunto de ferramentas para fazer a compilação, debugging e todos os processos envolvidos para a geração da aplicação.

Após o desenvolvimento da aplicação no _host_, esta é copiada para dentro da plataforma embarcada, o _target_. Esta aplicação, em geral, utiliza-se de outras bibliotecas próprias ou de terceiros para realizar suas funções. Além disso, para realizar a interação com outras partes do sistema, como chamadas à hardware, é necessário uma API que faça a interface entre o Kernel Linux e a aplicação. Esta API é a biblioteca padrão C.

A biblioteca C fornece mecânismo de comunicação entre a aplicação e o Kernel Linux, principalmente através de chamadas de sistema \(system calls\). Portanto, quando a aplicação deseja acessar ou utilizar algum recurso externo, como acesso a algum hardware, por exemplo. É utilizada uma função da biblioteca padrão C, que em geral abstrai uma chamada de sistema, e então interage com o Kernel. O Kernel Linux, por sua vez, realiza a interação com o device driver necessário para a obtenção do recurso solicitado pela aplicação e então retorna sua resposta via biblioteca C até a aplicação solicitante.

Além dos items já citados, um outro programa é necessário para o funcionamento do _target_, o bootloader. Este é um pequeno programa que realiza a inicialização básica do hardware e é responsável por carregar o Kernel Linux dentro da memória RAM, passando todo o controle do processador para o mesmo.

