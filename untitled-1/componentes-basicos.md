# Componentes Básicos

Os processos envolvidos em uma toolchain já foram discutidos, contudo, nesta etapa será apresentado os principais componentes presentes em uma toolchain.

Os componentes básicos de um toolchain, portanto, são: 

* Binutils; 
* Headers do kernel; 
* Biblioteca padrão C; 
* O compilador _gcc;_
* e opcionalmente um debugger como o _gdb._

A seguir, será explicado de forma mais completa o papel de cada um desses componentes.

![](../.gitbook/assets/image%20%2820%29.png)

## Binutils

O [Binutils \(_GNU Binary Utilities\)_](https://www.gnu.org/software/binutils/) é um conjunto de ferramentas da GNU para operações de arquivos binários. Este foi projetado para realizar a manipulação de arquivos binários em geral para uma dada arquitetura de processador.

O Binutils possui um conjunto de ferramentas internas que desempenham papeis específicos no processo de manipulação de binários. Dentre as ferramentas disponibilizadas pelo Binutils, temos:

* **`as`**: este é o _assembler_ do Binutils, ele realiza literalmente a tradução do código binários \(aquele gerado pelo processo de compilação\) para um arquivo em linguagem de máquina. Ou seja, converte _assembly_ para binário. Os arquivos gerados nesta etapa de montagem, são os arquivos com extensão _\*.o_ , também chamados de arquivos objetos.
* **`ld`**: este é o _linker_ do Binutils, ele realiza a combinação de diversos arquivos objetos ou arquivos de bibliotecas, gerados durante o processo de compilação e montagem, em um único arquivo executável \(ou em outro arquivo de biblioteca ou mesmo em outro arquivo de objetos\).  De forma resumida, ele relaciona os objetos e bibliotecas à um único arquivo.
* **`ar`, `randlib`**: este é o _archiver_ do Binutils, mas assim como outros também é um utilitário padrão do Unix. Ele é utilizado em geral para juntar grupos de arquivos em um único. Contudo, seu principal uso é na criação de bibliotecas estáticas \(_\*.a_\).
* **`objdump`**, **`readelf`**, **`size`**, **`nm`**, **`strings`**: estas são os principais utilitários do Binutils para a realização do processo de inspeção de binários. Por exemplo, o `objdump` é utilizado para realizar o dissasemble dos executáveis. Enquanto o `readelf` é utilizado para extrair as informações de um executável e comando `size` apresenta o tamanho do executável, separado por seções. O comando `nm` mostra informações dos símbolos sendo utilizados no executável, ao passo que o `strings` aparesenta todos os caracteres imprimíveis do programa.
* **`strip`**: este é o utilitário do Binutils responsável por separar as partes do não utilizadas de um binário. Por exemplo, remove as partes relacionadas e utilizados no processo de debugging.

Além desses utilitários, diversos outros são disponibilizados pelo Binutils, a lista completa pode ser acessada através do [site oficial do binutils](https://www.gnu.org/software/binutils/).

Para realizar o download do Binutils, basta realizar o clone do repositório oficial:

```text
git clone git://sourceware.org/git/binutils-gdb.git
```

## GCC

Além da Binutils, outra ferramenta presenta no toolchain é o compilador GCC \([GNU Compiler Collection](https://gcc.gnu.org/)\). Este é sem dúvidas um dos compiladores mais famosos do mundo, sendo vastamente utilizado. Em geral, estamos acostumados a fazer a compilação de códigos em Linguagem C com ele, contudo, este compilador apresentar solução para diversas outras linguagens, tais como: C, C++, JAVA, ADA, Fortran e  etc.

Não obstante, o GCC apresenta além do suporte à compilação de diversas linguagens de programação, apresenta também o suporte a diversas arquiteturas de processadores, desde processador embarcados como ARM e afins até PowerPC e x86.

É distribuído pela [Free Software Foundation](https://pt.wikipedia.org/wiki/Free_Software_Foundation) \(FSF\) sob os termos da [GNU GPL](https://pt.wikipedia.org/wiki/GNU_GPL), disponível para sistemas operacionais Unix e Linux e certos sistemas derivados como o macOS. 

Ele é software extremamente acessível em relação a usuabilidade, por exemplo: para gerar os binários de um código simple em linguagem C. Isto é, fazer o processo de compilação do _\*.c_, simplemeste chamamos o GCC e passamos as informações de operação, como o arquivo que queremos compilar e o nome do arquivo de saída.

```text
gcc arquivo.c -o saida
```

Através da simple evocação deste comando, o GCC executa todos os processos da compilação, já listados anteriormente, como pré-processamento, compilação, montagem e linkagem.

## Biblioteca Padrão C

Conforme comentado anteriormente, o kernel possui o conceito de espaço de usuário e espaço do kernel \(US e KS\) e, portanto suas aplicações não tem acesso direto à hardware. Isto significa, por exemplo, que é preciso passar pelo kernel para realizar a comunicação com algum dispositivo ou driver.

Desta forma, é faz-se necessário uma interface que possibilite a interação entre essas duas camadas, apliação e hardware. Quem fornece essa interface, é a biblioteca C, possibilitando a comunicação entre aplicações no US e o kernel.

Essa interface é na realidade uma API \(_Application Programming Interface_\) de desenvolvimento de aplicações. Em linhas gerais, cada função utilizada, quando estamos programando em C por exemplo, engatilha uma chamada de sistema que em geral cria uma thread para essa função, esta thread por sua vez, realiza a comunicação com o kernel e executa a função comandada.

Por exemplo, quando utilizamos funções comuns em C, como funções de `read`, `write` ou mesmo o `printf`, é disparada uma thread no sistema que realiza uma systemcall para o kernel Linux que em um determinado momento irá executar a função determinada. 

Estas características da API tornam o desenvolvimento de software totalmente modular e desacoplado. Uma vez que esta fornece uma abstração suficiente para que não seja necessário o desenvolvedor se preocupe com qual tarefa esta sendo escalonada no pelo kernel, ou mesmo quais são os endereços dos registradores ou a tabela de ender a serem utilizados e etc. Basta apenas evocar as funções da biblioteca padrão C, que ela realiza o trabalho 'sujo', se comunicando com o kernel de forma abstrata para o programador.

Assim, quando se deseja executar alguma função, basta chamar a função, indicando o que se deseja fazer e esta se comunica com o kernel, automaticamente, e retorna os valores para a _libc_ e então a _libc_ retorna ao usuário. 

Esse processo pode ser visualizado na figura no topo da página, onde é ilustrado a realização da leitura de um dado do disco rígido através da _libc._ Primeiramente é chamada a função, esta faz a requisição de leitura ao kernel que se comunica através de um driver com o periféricos desejado e então retorna a resposta para a _libc_ que apresenta o resultado para a aplicação. 

Como pretende-se desenvolver em um ambiente Linux embarcado, e o próprio Linux é dependente da biblioteca C, pois ela eh a API para o programador interfacear com o kernel, é natural que o toolchain também dependa de uma biblioteca C, uma vez vai gerar os executáveis para um determinador target rodando Linux.

Em suma, o mais interessante deste processo inteiro é o fato do desenvolvimento se tornar totalmente modular, seguindo o pipeline Desenvolvimento -&gt; Cross-compiling -&gt; Test no host e target.

Existem diversas bibliotecas C para uso, tanto em sistemas desktop como em sistemas embarcados, cada uma com suas próprias características e especificidades, por exemplo:c

A [_**glibc**_](https://www.gnu.org/software/libc/) **** __que é a bilbioteca C padrão do projeto GNU, ela está disponível em todas as distribuições GNU/Linux, só não está naquelas em que foi considerada grande ou com desempenho não satisfatorio, mas muito provalvemente a biblioteca que roda nesse sistema é derivada dela. Ela foi projetada para ter alta performance e alta portabilidade, sendo também extremamente eficiente em termos de manutenção e suporte, sendo atualizada sempre que uma nova versão do kernel é lançada. No entanto, por se tratar de uma biblioteca completa, pode ser restritiva para hardwares muito limitados, principalemente em relação a RAM e armazenamento em disco, o que pode ser contornado através de remoção de partes não utilizadas e edições.

* Projetada com foco em performance e portabilidade;
* Presente em todas as distribuições GNU/Linux;
* Suporte ativo da comunidade;
* Dependendo do hardware utilizado, ela pode não ser uma boa escolha devido ao consumo de RAM e espaço de disco. _****_

Ao passo que a [_**uClibc**_](https://uclibc-ng.org/), que é a uma biblioteca C projetada para sistemas embarcados pequenos. Foi desenvolvida para alta portabilidade, sendo altamente configurável e tendo seu principal foco na economia de recursos e não em performance. Por ter alta configurábilidade, diversos recursos podem ser ativados ou desativados, através de uma interface do tipo _menuconfig_ \(este tipo de configuração será abordado em outro momento do treinamento\). E tem seu principal emprego em dispositivos que visam baixo consumo, em uma arquitetura ARM pode ter até 600K, e várias funcionalidades da _glibc._

* Continuação do antigo projeto uClibc;
* Biblioteca C leve e projetada para sistemas embarcados;
* Altamente configurável;
* Comunidade de suporte ativa;
* É mais focada em economia de recursos do que performance;
* Em um arquitetura ARM pode ter 600K, e várias funcionalidades da _glibc_;

Outros exemplos de bibliotecas C para sistemas são:

* _**musl**;_
* _**eglibc**_; 
* _**dietlibc**_.

## Headers do Kernel Linux

Conforme mencionado na seção anterior, a biblioteca C fornece uma camada de abstração que serve de interface para o programador utilizar os recursos do KS através da sua aplicação US. Seja essa interação uma chamada de sistema, uma definição de constantes \(que nada mais são que flags\) ou mesmo estruturas de dados propriamente ditas. E esta interface é feita através de _wrappers_ de systems calls, de tal forma que o programador não precise "escovar bits" e tenha certa abstração ao interagir com o kernel. E portanto, a biblioteca C precisa dos headers do kernel para ser compilada.

Seus headers estão localizados principalmente nos diretórios `linux` e `asm`, mas existem outros no diretório`include` dos arquivos fontes do kernel, durante o treinamento, deveremos realizar a adição de alguns headers desses diretórios.

Para exemplificar melhor a utilização desses headers, vamos visualizar algumas estruturas fornecidas por eles e também sua localização e afins. Por exemplo, dentro desses headers é possível se obter algumas definições de system calls. Estas definições, nada mais são que os números das chamadas de sistema, um exemplo é os header `<asm/unistd.h>`.

{% code title="asm/unistd.h" %}
```c
# define __NR_exit 1
# define __NR_fork 2
# define __NR_read 3
[...]
```
{% endcode %}

No Linux cada system call é representada por um número inteiro de oito bits \(0~255\). Além disso, muitas vezes são chamadas de kernel calls, pois é exatamente o que acontece na prática, isto é, são chamadas ao kernel.

Um outro exemplo de headers do kernel são as definições de constantes, que nada mais são do que flags que abstraem conceitos para facilitar a programação. Normalmente ao solicitar acesso para qualquer dispositivo, arquivo, periférico e etc.  É preciso especificar o modo que vc deseja operar tal arquivo, por exemplo, abrir em modo de leitura, modo de edição e etc. Essas definições de constantes \(flags\) podem ser observadas no header `<asm-generic/fcntl.h>`, por exemplo:

{% code title="asm-generic/fcntl.h" %}
```c
# define O_RDONLY 00000000  // Permiss. para leitura.
# define O_WRONLY 00000001  // Permiss. para escrita.
# define O_RDWR   00000002  // Permiss. para leitura e escrita.
[...]
```
{% endcode %}

Existem também tipos de estruturas de dados definidas nos headers, muitas vezes essas estruturas são passadas como parâmetros em uma system call ou mesmo retornadas de uma syscall. A estrutura `stat` por exemplo, que compreende muito mais do que as duas variáveis que a compõe, contém o dado `st_mode`, que é o serial onde você armazena uma daquelas flags anteriores, ou seja, como o arquivo ou dispositivo foi aberto, além da `st_dev` que representa um identficador único do dispositivo onde o arquivo reside, ou que o arquivo representa, vide o header `<asm/stat.h>`.

{% code title="asm/stat.h" %}
```c
struct stat{
    unsigned long st_dev;  // ID do dispositivo que mantém o arquivo.
    unsigned long st_mode; // Modo de abertura do arquivo (flag).
}
[...]
```
{% endcode %}

