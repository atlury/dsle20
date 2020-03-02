---
description: >-
  Configuração da máquina virtual utilizada no treinamento, bem como a
  instalação de um SO temporário na RPi3.
---

# Configuração Inicial

## Configuração do Ambiente de Desenvolvimento

O objetivo desta seção é criar e configurar um ambiente de desenvolvimento para sistemas Linux embarcados que consiga desempenhar todos os papeis necessários para o treinamento. 

Na primeira seção [Configuração da Máquina Virtual](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-maquina-virtual) é realizada a instalação e configuração da máquina virtual que será utilizada no treinamento. Ao passo que na seção [Configuração da Plataforma Embarcada](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-plataforma-embarcada) é instalado um sistema operacional temporário na placa de desenvolvimento e são realizadas as primeiras configurações do sistema. 

{% hint style="success" %}
É fortemente recomendado que você utilize um ambiente Linux para desenvolver sistemas Linux embarcado.
{% endhint %}

Primeiro, todas as ferramentas que existem por aí da comunidade open-source foram projetas para rodar em Linux. Quando existe algum porte ou versão para Windows/macOS, normalmente esse porte foi feito por algum determinado grupo de desenvolvedores e você fica sem suporte dos desenvolvedores oficiais, não recebe atualizações, correções de bugs e etc.

Além disso, lembre-se que o kernel que roda na sua aplicação  é também o que roda na sua máquina, então quando você passa por problemas durante o desenvolvimento, possivelmente a solução é válida para ambos os sistemas. De forma geral,  usando Linux você aprende Linux.

Desta forma, durante o treinamento será utilizado uma máquina virtual com a distribuição Ubuntu 16.04 como ambiente de desenvolvimento. Assim, formamos um ambiente seguro e completo para o desenvolvimento da aplicação, bem como normalizamos os possíveis problemas que podem ocorrer durante o treinamento, já que todos estaremos com o mesmo sistema, mesmos pacotes e etc.

