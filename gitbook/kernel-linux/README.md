# Kernel Linux

Como já mencionado o kernel é um componente do sistema operacional e não o sistema operacional em si. De forma resumida, uma distribuição Linux \(SO\) contém além do kernel Linux, um conjunto de ferramentas, aplicações e bibliotecas, tornando-se um sistema mais completo.

Assim como qualquer outra aplicação, o Linux também precisa de bibliotecas e aplicações para funcionar, isto é, para prover suas principais funcionalidades ao usuário.

Ele foi criado em 1991 pelo estudante finlandês Linus Torvalds, foi criado sem fins muito rebuscados, era apenas um hobby. O que alavancou o sistema Linux, foi o fato de o Linus ter enviado essa mensagem, disponibilizado seu código e instigando os outro desenvolvedores a melhorarem as implementações dele, disponibilizando todo o código.

A partir deste momento, eles conseguiram criar uma comunidade bem grande de desenvolvedores. Uma comunidade extremamente dinâmica, onde a cada novo código surigiam várias outras ideias e melhorias, melhorando cada vez mais o sistema. Seja esse desenvolvimento promovido pelo orgulho de ter o melhor código e mostrar que era um programador mais eficiênte, ou pela curiosidade mesmo. Mas no fim das contas, foram esses os principais motivos para a comunidade e o sistema operacional irem tão longe.

Em pouco tempo, o kernel passou a ser adotado em varios SOs frees, ou seja, aqueles sistemas operacionais que estavam em situações desconfortáveis como o próprio GNU. Atualmente, milhares de pessoas, individualmente ou através de empresas, contribuem para cada novo realese o kernel.

### Curiosidades

Normalmente o Linux lança uma nova versão a cada 70 dias, este número pode oscilar um pouco, tanto para mais quanto para menos. Por exemplo, a realease 4.13 demorou 63 dias para ser lançada. Foram aproximadamente 13.006 patches. 

Normalmente cada patch faz apenas um coisa, editar o codigo, adicionar linhas ou remove. Eles são dividos em tarefas bem pequenas e os desenvolvedores responsáveis por cada tarefa devem garantir que ao aplicar seu patch, o build do kernel continue funcionando corretamente. Esta imposição força os desenvolvedores a quebrar as modificações em tarefas bem pequenas, questões de boas práticas, assim como deve ocorrer na maioria das empresas de desenvolvimento.

Dividindo o número de patches por dias e horas, chegamos a um número de aproximadamente oito alteração por hora. Ou ainda, se olharmos da versão 4.12 para a 4.13 foram adicionadas 596,148 linhas, que dá aproximadamente 394 linhas por hora ou sete por minuto.

Além disso, o Linux tem uma política, pelo menos no desenvolvimento mainline, de somente adicionar linhas e nunca remover \(exceto por refatoração\) então desde o princípio, esta tudo desenvolvido nos fontes. Claro que um kernel não utiliza tudo isso, tanto que todos tem a opção de montar o kernel de acordo com suas necessidades, escolhendo somente os módulos e componentes desejados.





