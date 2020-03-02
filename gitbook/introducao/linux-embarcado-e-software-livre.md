# Linux Embarcado e Software Livre

### Kernel Linux

O Linux na verdade é o kernel, e não o Sistema Operacional. O kernel é basicamente um programa que controla todo o sistema. Ele é responsável por gerenciar as aplicações que irão rodar no sistema, interfacear o hardware e software, enfim, é um programa que controla a execução de outros programas! 

Já são tantos desenvolvedores envolvidos, que existem várias versões do kernel sendo lançadas frequentemente. No entanto, a principal, chamada de mainline, respeita o prazo de aproximadamente três meses. Portanto, a cada três meses é lançada uma versão nova do kernel Linux.

Ubuntu, Fedora, Arch, são Distribuições que integram o kernel Linux. Estas, são compostas pelo kernel Linux e um conjunto de aplicações personalizadas. Cada distribuição tem sua própria característica de aplicações. É correto afirmar que elas são distribuições GNU/Linux, e não somente Linux.

E o Linux embarcado utiliza-se do kernel Linux em conjunto com componentes open-source em sistemas embarcados.

#### Principais Características do kernel Linux

* **Portabilidade e Suporte a Hardware:** Atualmente existem mais de 30 portes de arquiteturas, isto é, ele roda em processadores x86, ARM, PPC, SPARC, Microcontroladores e etc.
* **Escalabilidade:** sua escabilidade é uma das features mais fascinantes, é o mesmo kernel rodando em supercomputadores, relógios, geladeiras e etc.
* **Confiabilidade e Estabilidade:** existem relatos de servidores rodando ininterruptos por 10, 16, 18 anos. Um deles, um servidor interno de emails, que rodava um FreeBSD num pentium 200mhz por 18 anos.
* **Modularidade:** você pode personalizar seu sistema de acordo com sua necessidade, por exemplo o Tinycore é um sistema Linux com ambiente grafico \(desktop\) e a imagem dele é de apenas 16MB. Existem versões bem enxutas tambem para microcontroladores, como o uClinux de apenas 6MB.
* **Facilidades do Open-Source:** por ser open-source exitem uma comunidade imensa para aulixar na solução de problemas, desenvolver novas soluções, ferramentas e etc. Além disso, é livre de royalties.

#### Reusabilidade de Componentes

* **Filosofia Open-Source:** a reusabilidade de sistemas Linux e componentes open-source é gigantescas, pois todos os códigos já desenvolvidos são disponibilizados para a comunidade. Incuindo drivers para chips ou sensores específicos, protocolos de comunicação, bibliotecas gráficas e etc.
* **Aceleração do desenvolvimento:** sem dúvidas este tipo de abordagem acelera o desenolvimento de sistemas, uma vez quqe diversos drivers, interfaces e componentes podem ser reutilizados ou mesmo ser diretamente acoplados de outras aplicações. Assim, muitas vezes é possível começar o desenolvimento diretamente na sua aplicação, sem perder tempo com redesenvolvimento de ferramentas e módulos.
* **Adaptabilidade para novos sistemas:** assim que um novo hardware, componente, protocolo de comunicação e etc é lançado, tão logo se torna popular e seus módulos, drivers e ferramentas são disponibilizados na comunidade.
* **Desnecessário "Escovar Bits":** o mais importante de tudo, e que resume todas as outras considerações. A idéia é parar de escovar bits, gastar horas configurando hardware, desenvolvendo API, simulando funcionamentos de SO e etc. Você tem tudo disponível agora, podendo focar no desenvolvimento da aplicação, focando no **valor agregado do seu produto/aplicação.**

#### Baixo Custo

* **Replicação ilimitada:** é possível duplicá-lo e utilizá-lo em diversos dispositivos, sem custo adicional. Você pode replica-lo, edita-lo, adapta-lo para outros hardwares sem custo.
* **Software sem custo:** se optar por utilizar software livre, tanto os módulos, como as ferramentas de desenvolvimento. Seu custo de software sera zero. Sendo necessário apenas o know-how como investimento.
* **Curva de aprendizado vs. preço:** embora a curva de aprendizado deste tipo de sistema e ferramenta será considerável. A economia com licensas de software e ferramentas pode ser totalmente convertida em treinamento para a equipe.

**Controle Total**

* **Controle dos fontes:** uma vez trabalhando com software livre, você tem acesso a todos os códigos fontes e drivers do seu sistema. Assim, caso desconfie de alguma funcionalidade ou deseja altera-la, você pode fazer sem nenhuma outra implicação. 
* **Liberade para modificações:** como mencionado, você possui o controle de todos os fontes, portanto pode otimizá-los para a sua aplicação.
* **Elimina a dependência de terceiros:** é uma boa prática quando se utiliza softwares livres. Assim, você não depende de terceiros, por exemplo com utilização de ferramentas e mudança de plataformas.

**Qualidade**

* **Suporte e Qualidade:** Existem diversos softwares open-source que são vastamente utilizados na vida real, sendo empregados em diversos sistemas como firefox, chromium, android, linux e diversos drivers e outras aplicações. Esse fato é interessante, pois quanto mais popular o projeto, mais programadores estão envolvidos, mais pessoas testando e reparando o código. Em geral, se tem uma robustez mais elevada neste tipo de sistema.

**Suporte da Comunidade**

* **Suporte da comunidade:** os softwares open-source são desenvolvidos por comunidades de desenvolvedores e usuários e como mencionado, desta forma as atualizações e a robustez costuma ser mais elevada que softwares proprietários. Além disso, quando se tem algum problema ou dúvida, há vários meios de se contatar o suporte, que em geral é feitos nessas comunidades, tornando o atendimento mais práticos e efetivo.

