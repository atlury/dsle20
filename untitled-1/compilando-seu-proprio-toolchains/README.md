# Compilando seu próprio Toolchains

Sem dúvidas dentre as soluções esta é a mais flexível e adaptável para o desenvolvimento embarcado. Você tem a possibilidade de adaptar as ferramentas de acordo com suas necessidades, fazendo combinação de diversas ferramentas, adicionar tudo que precisa para o desenvolvimento e compilar sua própria toolchain.

Gerar uma toolchain do zero é uma tarefas extremamente árdua e dolorosa, pode demorar dias ou mesmo semanas para a construção de uma toolchain do zero, principalmente pela demanda de conhecimentos específicos e pesquisa.

São muitos detalhes, componentes para compilar de forma manual, configurar de maneira ideal e principalmente entender como cada uma dessas partes funcional e como se conectam.

O processo de criação de uma toolchain manualmente é extremamente delicado e demorado, exigindo muito conhecimento sobre os compiladores e ferramentas que serão adotados. Estudos profundos sobre as configurações de cada uma das ferramentas, documentações extensas e densas, mecânimos como de ponto flutuante e etc. De fato, é uma tarefa para uma classe específica de desenvolvedores.

Contudo, há uma abordagem menos abrupta para a criação do próprio toolchain, as **ferramentas de automatização para criação de toolchain.**

### **Ferramentas de automatização**

Estas são ferramentas que auxiliam na criação das nossas toolchains sem a necessidade de pesquisar, configurar, compilar e linkar manualmente cada ferramenta. Esse processo é encapsulado através de uma abstração automatizada que cria, através de menuconfigs, makefiles e outros arquivos de configuração, uma toolchain com as nossas configurações para uso específico da nossa demanda.

Assim, não há a necessidade de se preocupar com cada um dos detalhes de compatibilidade, versão de ferramenta e etc. As automatizações, fornecem a verificação de dependência dos componentes, caso seja necessário a aplicação de algum patch específico em determinada versão esse processo é feito automaticamente pela ferramenta, bastando apenas selecionar qual a versão desejada.

Essas ferramentas automatizadas permitem a criação de toolchain totalmente flexíveis, ao contrário das pré-compiladas. Em geral, é fornecida uma interface que possibilita a seleção de componentes e ferramentas em diversas versões, permitindo que você monte a toolchain da forma mais otimizada para a sua demanda. Então, você monta a toolchain do seu jeito e no final a ferramenta se encarrega do processo de configuração \(de acordo com suas escolhas\), compilação, linkagem, compatibilidade e dependências.

Outro ponto positivo deste tipo de ferramenta, é que elas oferecem correções para bugs conhecidos de incompatibilidade. Por exemplo, um problemas específico do componente X  na arquitetura Y. Isto, pois elas geralmente possuem comunidades bem ativa, então sempre que algum bug é reportado, os desenvolvedores já se encarregam de resolve-lo.

Basicamente, essas ferramentas são baseadas em shell scripts ou makefiles, elas fazem a busca automática do componentes que foram selecionados, algumas vezes até realizam o download, extraem e configuram o makefile daquele determinado componente e os compila.

### Ferramentas populares

Como de costume, existem várias ferramentas disponíveis parar geração de toolchains e essas são umas das mais populares, todas elas possuem uma comunidade bem ativa de desenvolvedores e suporte constante.

A principal diferença entre elas, esta nos pacotes e arquiteturas suportadas para a criação da toolchain.

* [Crosstool-ng](https://crosstool-ng.github.io/): Suporta diversas bibliotecas, como: `glicb`, `uClib` e `musl`. E diversas arquiteturas de processador ecomponentes, e tem uma interface no estilo menuconfig.
* [PTXdist](https://www.ptxdist.org/): É uma ferramenta nova, que tem ganhado muito espaço, mas ainda não esta totalmente completa, por exemplo não tem suporte a bibliotecas `musl`.
* [Yocto](https://www.yoctoproject.org/) \(_system build_\): o Yocto na verdade adotou a [Open Embedded](http://www.openembedded.org/) que tinha uma ferramenta exclusiva de geração de toolchain, e então acobou progredindo e virou um _system build_ completo.
* [Buildroot](https://buildroot.org) \(_system build_\): É uma das ferramentas mais utilizadas e tem uma comunidade muito ativa, devido a popularização do uso, o projeto foi incrementado e passou a ser um _system build_ completo.

{% hint style="success" %}
_System build_ é uma outra classe ferramentas que possibilitam gerar não somente o toolchain, mas também o RootFS, kernel, bootloader e etc.
{% endhint %}

Neste treinamento daremos uma atenção maior a duas ferramentas, a _Crosstool-ng_ e ao _Buildroot._

\_\_

