---
description: >-
  Descrição dos principais eventos relacionados ao surgimento do Linux e alguns
  conceitos referentes ao sistema.
---

# Introdução

## Histórico: Surgimento do Linux

{% hint style="info" %}
Este capítulo histórico foi escrito sem rigor científico, a história contada é baseado em recortes e relatos. Contudo, o real intuito desta etapa e a ambientação e a ordem de desenvolvimento do sistema.
{% endhint %}

#### 1960 - Computadores grandes, componentes discretos

No início da década de 60, computadores eram construídos a base de componentes discretos, interconectados através de fios principalmente e extremamente caros de se produzir. Os pesquisadores envolvidos precisavam justificar o alto custo e, por isso, era necessário aproveitar o computador de forma mais eficiente possível, isto é, ele não poderia ficar muito tempo ocioso \(idle\).

#### 1960 - Início de P&D em Sistemas Operacionais

Este foi provavelmente o fato que mais contribuiu para o início de pesquisa/desenvolvimento de sistemas operacionais. A ideia por trás dos sistemas operacionais era gerenciar os recursos do computador de maneira eficiente, ou seja, um SO que mantinha o computador ocupado o tempo todo \(processando\), significava economia de dinheiro!

#### 1960 - Conceito de Time-Sharing \(MIT\)

O MIT sempre manteve um histórico de cooperação com o governo americano. E no início de 60, a computação era ineficiente. Os computadores eram dedicados a um único usuário por vez. Neste cenário, foi que nasceu o conceito de time-sharing, multi- tasking, etc. A ideia era que mais de um usuário pudesse utiliza-lo ao mesmo tempo, diminuindo assim as filas de espera.

#### 1960 - Demonstração de Time- Sharing \(IBM 704\) - Prof. John McCarthy \(MIT\)

Em 1960, o professor John McCarthy do MIT propõe modificações em um dos principais computadores do centro de computação do MIT, IBM 704, e demonstra que é possível operá-lo com time-sharing. A partir desse momento, não era mais apenas um conceito.

#### 1961 - Compatible Time-Sharing System \(CTSS\) \(IBM 709\) - Prof. Fernando Corbató \(MIT\)

Prof. Fernando Corbató, diretor assistênte do MIT Computation Center, liderou um pequeno grupo e desenvolveram um novo sistema, denominado Compatible Time-Sharing System \(CTSS\), e o demonstraram funcionando num IBM 709.

#### 1963 - Projeto MAC \(Multiple Access Computing\)

Os estudos de McCarthy e Corbató continuaram em 61, 62 e 63. Então, um novo projeto foi iniciado, denominado Projetco MAC \(Multiple Access Computing\) que era destinado a unir esforços na criação/definição de um SO um pouco melhorado, avançado e juntando os feitos que cada pequeno grupo de pesquisadores de computação haviam feito na área de sistemas operacionais. O projeto era destinado à pesquisadores com interesse em Computação, Inteligência Artificial e Sistemas Operacionais.

O projeto MAC começou a fazer a chamar a atenção de muita gente. Então, surgiram diversos projetos derivados, tais como o projeto Multics. 

#### 1965 - Multics O.S. - Bell Labs e General Electric se juntam ao Projeto MAC

Então em 1965 é formada uma parceria entre Bell Labs \(Laboratório da AT & T\), GE e o grupo do Projeto MAC, para desenvolver um Sistema Operacional chamado Multics. Este sim era um SO completo, incluía sistema de arquivos por meio de estruturas de árvores, suporte à periféricos, terminais, programas por linha de comando, memória virtual compartilhada entre processos, compiladores de linguagens de programação, bibliotecas disponíveis.

#### 1969 - Bell Labs deixa o projeto Multics O.S.

Então a Bell Labs deixa o projeto, alegando que entraram no projeto no intuito de obter um SO para seus próprios membros utilizarem \(P&D\). No entanto, a deadline do SO passou e o sistemas ainda não estava pronto, haviam programadores polarizados pela ideia do fracasso. Além disso, havia muito trabalho à ser feito, ou seja, mão de obra cara sendo gasta \(Bell Labs e outras empresas tinham vários programadores envolvidos\) e por isso, decidiram por sair do projeto. No entanto, quatro engenheiros de software, dentre eles Ken Thompson e Dennis Ritchie continuaram as pesquisas em cima do sistema operacional por conta própria na Bell Labs.

#### 1970 - Ken Thompson e Dennis Ritchie desenvolvem o "Unics"

É dito que dois engenheiros de software da Bell Labs, K. Thompson e Dennis Ritchie costumavam jogar Space Travel como passatempo enquanto estavam no projeto Multics OS. Então, quando a Bell Labs decide sair do projeto, em 69, esses engenheiros não possuiam mais acesso ao Multics e consequentemente nem ao Space Travel. E por isso, eles decidem desenvolver seu próprio SO, apenas pra rodar o jogo, algo bem simples em relação ao Multics, que é inclusive o motivo do trocadilho Unics.

#### 1971 - Publicação na ACM SIGOPS \(Special Interest Group in Operating Systems\) - Best Paper Award

Apesar de ser baseado em um passatempo, com o tempo e ajuda de outros programadores, inclusive de Cambridge, eles notaram que o SO era realmente bom e decidiram apresenta-lo numa conferência deverás renomada de Sistemas Operacionais da ACM, SIGOPS. A apresentação deles foi extremamente bem recebida, cuminando no premio de melhor paper.

#### 1971 - Dennis Ritchie escreve a linguagem NB/C

A primeira versão do Unics havia sido desenvolvida em B, uma linguagem desenvolvida por Ken Thompson, homenagem a sua esposa Bonnie. No intuito de adicionar algumas features \(PF\), Dennis Ritchie começa a escrever uma nova linguagem, NB, que seria um update da B. Sendo a base da linguagem C utilizada hoje de desenvolvimento de Dennis Ritchie.

#### 1973 - Dennis Ritchie reescreve o Unix em C

Em 1973, o Unics, agora chamado de Unix, é reescrito em linguagem C pelo próprio Dennis Ritchie e a AT&T começa a utiliza-lo na empresa, se apropriando do projeto.

Esta é uma das principais etapas da evolução do Linux, uma vez que ao reescrever em C o Unix, foi implementado de forma totalmente modular, o que não acontecia na época. Os SOs eram desenvolvidos de forma específica, mas esta nova abordagem trouxe diversas vantagens e características para o Unix, como compatibilidade, portabilidade e modulariedade.

#### 1983 - Richard Stallman lança o projeto GNU \(GNU’s not Unix\)

De 1973 à 1983 muitas versões do Unix são lançadas, várias distribuições, como BSD , Xenix \(da Apple\) e etc. Mas todas sob algum licenciamento com a Bell Labs, pois ela era proprietaria do Unix. Então, Richard Stallman, que era pesquisador do MIT, ~~fica frustrado~~ e decide lançar o projeto GNU, que significa GNU is not UNIX! 

Sua ideia era criar um SO Unix completo e gratuito. Com melhorias feitas pelos proprios integrantes do projeto GNU, e compartilhar com quem quisesse olhar ou utilizar.

#### 1985 - Richard Stallman cria a Free Software Foundation \(FSF\)

Em 1985 então, Stallman e os integrantes do projeto GNU criam a Free Software Fundation. Uma corporação sem fins lucrativos que busca promover softwares gratuitos sem restrições à cópia, redistribuição e modificação do mesmo. E é através dessa filosofia que surge a licença GPL. 

"free" software significa liberdade.

**Licença GNU GPL - GNU General Public License**

* Usar o software para qualquer finalidade 
* Modificar o software de acordo com suas necessidades 
* Compartilhar o software com qualquer um 
* Compartilhar as alterações feitas no software

#### 1991 - Linus Torvalds compartilha a seguinte frase

> “I’m doing a \(free\) operating system \(just a hobby, won’t be big and professional like gnu\) for 386\(486\) AT clones. This has been brewing since april, and is starting to get ready. I’d like any feedback on things people like/dislike in minix, as my OS resembles it somewhat \(same physi- cal layout of the file-system \(due to practical reasons\) among other things\).”

Quando Linus divulga essa frase, que seria apenas um hobby, vários desenvolvedores ficam interessados em ajudá-lo no desenvolvimento do SO, que passa a ser chamado de Linux.

#### 1992 - Linux e GNU se unem \(Linux + GPL\)

Finalmente em 1992 é quando a mágica acontece. Linux e GNU se integram na intenção de criar um SO completo. E com essa parceria, o Linux adota a licença GPL. A partir daqui, diversos desenvolvedores do mundo todo começam a se juntar a Linux Foundation e o projeto começa a prosperar.

#### Hoje em dia

Quase três décadas se passaram e os mais variados dispositivos rodam Linux atualmente. Desde rifles e navios de guerra à automóveis, geladeiras e televisores. Estes são apenas alguns exemplos, são inúmeros dispositivos! Todos com firmware baseado em Linux.

### 













