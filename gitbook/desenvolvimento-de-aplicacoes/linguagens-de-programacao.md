# Linguagens de Programação

### Linguagem de Programação

Existem diversas formas de se desenvolver aplicações para Linux embarcado. A mais comum e usual é o desenvolvimento de aplicações em C/C++, visto que é a forma natural de se comunicar com a API do Linux.

Lembre-se o Linux, tanto seu kernel quanto módulos, são desenvolvidos em linguagem C, a biblioteca padrão do sistema é a bilbioteca C e já esta presente no sistema.

C++ é simples de se utilizar também, nestes sistemas. Algumas bibliotecas desenvolvidas em C++, dependem da biblioteca c++ e portanto, podem estar presente no seu sistema. Um exemplo comumente utilizado é o QT, principalmente para aplicações que requerem interfaces gráficas para o usuário, como IHMs. 

Esse tipo de abordagem é prática e eficiente, as bibliotecas são similares e a possibilidade de se utilizar outros paradígmas de programação como Orientação a Objetos é sem dúvida um recurso extremamente poderoso para o desenvolvimento embarcado, tornando o código elegante e de fácil manutenção através de _design patterns_.

Outro caminho que pode ser utilizado é a adoção de linguagens interpretadas ou de script. Como o sistema Linux embarcado costuma ter mais capacidade que sistemas microcontrolados, esta é sem dúvidas uma opção viável para a implementação de sistemas.

As principais características deste tipo de desenvolvimento, utilizando linguagens interpretadas, é a velocidade de desenvolvimento e as possíveis camadas de abstrações fornecidas. É especialmente útil quando se trata de aplicações web. 

Não obstante, este tipo de desenvolvimento apresenta diversas facilidades para o desenvolvedor, como estruturas de dados complexas, abstrações e mesmo paradígmas diferentes de programação.

Contudo, normalmente requerem algum interpretador para que seja possível sua execução, possui um consumo de memória mais alto e levemente mais lentas quando comparado a aplicações C/C++.

Escolhas para comuns para este tipo de desenvolvimento são: Python, JavaScript, Shell Script, Lua, Perl, Ada, Java e etc.

### Bibliotecas C vs. Bibliotecas de Alto Nível

Em geral, a biblioteca padrão C já oferece um conjuto relativamente amplo de funcionalidades:

* I/O em arquivos e dispositivos de hardware, rede, threads e sincronização, IPC.
* Manual bem amplo e bem documentado \(man ou website\);
* No entanto, como é bastante antiga e possui um grande histórico de alterações, as vezes encontrar informação de uma funcionalidade nova pode ser trabalhoso.

Além disso, as vezes pode ser interessante utilizar frameworks de alto nível, como QT ou QTK. Isto pode ser bem útil, pois:

* Eles possuem uma separação bem clara entre o core da linguagem de programação \(C++\) e a parte gráfica;
* Tradeoff: desempenho vs. facilidade de desenvolvimento.

