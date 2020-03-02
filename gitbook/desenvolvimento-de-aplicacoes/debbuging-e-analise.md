# Debbuging e Análise

### Debbuging

Sem dúvidas, a ferramenta mais utilizada para o debugging de aplicações é o [GDB - _The GNU Project Debugger_](https://www.gnu.org/software/gdb/)_._ 

Ele é o debugger padrão do GNU/Linux, disponível para a maioria das arquiteturas embarcadas. Apresenta suporte para diversas linguagens como C, C++, Pascal, Objective-C, Fortran, Ada e etc.

Possui uma interface por console \(terminal\), mas também possui algumas aplicações de front-ened para facilitar a visualização, por exemplo o VisualGDB.

Além disso, possui uma integração limpa e bem eficiente como IDEs como o Eclipse.

Os comandos básicos do GDB para debbugins são:

* **break sum** - Coloca um breakpoint na entrada da função sum\(\); 
* **break helloworld.c:45** - Coloca um breakpoint na linha 45 do ar- quivo helloworld.c;
* **print variável ou print node-&gt;data\_st.temperatura** - Imprime variável ou alguma referência mais complexa;
* **continue** - Continua a execução;
* **next** - Continua para a próxima linha \(step over na função\);
* **step** - Continua para a proxima linha \(step in na função\);
* **backtrace** - Imprime a stack do programa.

Além disso, existe o caso onde é necessário o Debugging Remoto. Isto é geralmente necessário em duas situações: na primeira, normalmente o fonte da aplicação se encontram na máquina de desenvolvimento e o binário no target. Ou, o target é limitado e não possui o gdb compilado de forma nativa \(~2.4mb\).

Para estes cenários uma solução é utilizar:

* **gdb client** \(arm-linux-gdb\) é utilizado na máquina de desenvolvimento;
* **gdbserver** é utilizado no target \(~100Kb\).

