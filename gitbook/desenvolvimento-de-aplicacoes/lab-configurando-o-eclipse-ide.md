# \[LAB\] Configurando o Eclipse IDE

Para o treinamento vamos utilizar o [Eclipse IDE](https://www.eclipse.org/) para o desenvolvimento de algumas aplicações. Esta escolha foi feita com base na praticidade da utilização da ferramenta, visto que a maiorida dos desenvolvedores embarcados já tiveram algum tipo de contato com a ferramenta. 

Além disso, uma abordagem utilizando editores de texto fazendo as compilações por Makefiles/CMake pode ser um pouco abrupta para aqueles que não tem familiaridade, visto que a curva de aprendizado é mais complexa.

Desta forma, vamos realizar o download, configuração e integração desta ferramente para o desenvolvimento de aplicações em Sistemas Linux Embarcados.

### Instalando e iniciando o Eclipse

Instale o Eclipse CDT \(C/C++ Development Tooling\) através dos repositórios oficiais do Ubuntu:

```text
sudo apt install eclipse-cdt*
```

{% hint style="success" %}
O '`*`' no terminal Linux significa algo como _don't care_, desta forma ele seleciona todos os pacotes que contenham o começo "eclipse-cdt".
{% endhint %}

Ao terminar o processo de instalação, abra o Eclipse \(via terminal ou pelo launcher\) e configure um Workspace de sua preferência. Ex: /home/gbs/dsle20/workspace. Em seguida, clique no ícone superior direito _**Workbench**_.

### Configurando a conexão entre Eclipse e _Target_

A conexão entre o Eclipse e a RPi será realizada via SSH, por meio do plugin RSE \(_Remote System Explorer_\). Se o comando anterior, de instalação do Eclipse, foi executado corretamente, este plugin já estará instalado.

Antes de prosseguir nas configurações do Eclipse, faça a liberação de login sem senha de seu usuário/máquina no servidor SSH da RPi. Para isso, primeiro gere uma chave RSA para seu host \(Ubuntu\):

```text
ssh-keygen
```

A ferramenta irá perguntar sobre local para salvar a chave criada e senha, deixe ambos como padrão, apenas tecle `ENTER`.

```text
Generating public/private rsa key pair.
Enter file in which to save the key (/home/gbs/.ssh/id_rsa): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/gbs/.ssh/id_rsa.
Your public key has been saved in /home/gbs/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:1E1uso97KS4cQYY6bo5nU5+W7H+zFnmDFhuqJaGAfeI gbs@dsle20
The key's randomart image is:
+---[RSA 2048]----+
|       .    .    |
|      . o. +     |
|   o . o. o +    |
|  . * ..o  +o    |
|   o = .So.. *   |
|    E o o oo* o  |
|   + . + B...+ . |
|  . =   X ..*    |
|   o . o.++=.o   |
+----[SHA256]-----+

```

Em seguida, copie sua chave recém criada para a RPi, utilizando o usuário que você deseja vincular a key:

```text
ssh-copy-id gbs@10.1.1.100
```

```text
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
gbs@10.1.1.100's password: 

Number of key(s) added: 1

Now try logging into the machine, with:   "ssh 'gbs@10.1.1.100'"
and check to make sure that only the key(s) you wanted were added.
```

Por fim, adicione sua key recém-criada ao agente de autenticação SSH:

```text
ssh-add
```

```text
Identity added: /home/gbs/.ssh/id_rsa (/home/gbs/.ssh/id_rsa)
```

Este passo final vinculará a key com o usuário utilizado no passo anterior. Assim, sempre que o comando `ssh gbs@10.1.1.100` for chamado, o agente fornece tal key e remove a necessidade de digitar uma senha. Faça o teste:

```text
ssh gbs@10.1.1.100
```

Pronto. Agora retorne ao Eclipse. Abra a perspectiva do RSE em: "_Window &gt; Open Perspective &gt; Other..._". Selecione _Remote System Explorer_ e clique em OK. 

Na janela mais a esquerda, chamada _Remote Systems_, clique com o botão direto no espaço em branco e selecione: "_New &gt; Connection.._.".

Na janela _New Connection_ selecione o tipo Linux e clique em Next. Preencha com as seguintes informações:

* **Host name**: 10.1.1.100 - O endereço de IP da RPi;
* **Connection name**: RPi3 - O nome para esta conexão \(pode colocar o nome que achar melhor\);
* **Description**: Alguma descrição sobre essa conexão \(opcional\).

Clique em _Next_. Na janela superior esquerda, _Configuration_, marque a opção **ssh.files** e _Next_. 

Novamente, na janela superior esquerda, _Configuration_, marque a opção **processes.shell.linux** e _Next_. 

Em seguida, na mesma janela, marque ssh.shells, _Next_ e por último marque **ssh.terminals** e _Finish_.

A partir deste momento, será possível explorar os arquivos da RPi através do Eclipse. 

Expanda o menu _Sftp Files_ e perceba que todas as pastas do RootFS estão listadas ali. É possível copiar arquivos, editar, apagar, tudo de forma integrada com o Eclipse. Provavelmente será pedida a senha do seu usuário da RPi, apenas digite-a e o acesso aos arquivos será liberado. Caso digite errado, clique no com o botão direito no projeto e limpe as senhas.

Logo abaixo de _Sftp Files_, no menu _Shell Processes_, você possui acesso à todos os processos \(incluindo threads\) em execução no target. É possível finalizar um processo pelo Eclipse e escolher o tipo de sinal que deseja enviar \(botão direito no processo -&gt; kill -&gt; signal type\).

No canto superior direito do Eclipse, existe um ícone de atalho para a opção "_Open Perspective_", ele estará do lado do atalho para _Remote System Explorer perspective_. Clique nele e selecione a perspectiva _C/C++_.

Adicione também a _View do Remote Systems_ na perspectiva C/C++. Dessa forma você pode explorar os arquivos do target na mesma perspectiva de programação. 

Selecione o menu "_Window &gt; Show View &gt; Other..._". Em seguida, selecione "_Remote Systems &gt; Remote Systems_". A _View Remote System Details_ também é interessante. Ela exibe informações de permissão de arquivos e diretórios.

Na aba recém-adicionada _Remote Systems_, Clique no último ícone da lista com o botão direito, _Ssh Terminals_, e escolha a opção _Launch Terminal_. Note que um novo terminal SSH será aberto numa nova aba. A partir de agora é possível também acessar o terminal da RPi3 via SSH, pelo Eclipse.

### Cross-Compilando sua Primeira Aplicação

Na perspectiva C/C++, clique no menu "_File &gt; New &gt; C Project_". Em _Project type_, selecione _Hello World ANSI C Project_. 

Em _Toolchains_, selecione _Cross GCC_. Dê um nome para seu projeto em _Project name_: "_MyFirstApp_". Clique em _Next_ e, se desejar, adicione informações de autor \(suas iniciais, por exemplo\).

_Next_ novamente, _Next_ e, em _Cross compiler prefix_: **arm-linux-** e no campo _Cross compiler path_: selecione o caminho do toolchain gerado na primeira aula: **/home/gbs/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin**. Finalmente, clique em _Finish_.

Para compilar o projeto, acesse o menu _"Project &gt; Build All_ " ou `CTRL+B`. Se tudo foi configurado corretamente, algo como a seguinte mensagem será exibida na aba Console: "_15:46:14 Build Finished \(took 183ms\)_"

Para testar o binário, copie-o da pasta `Binaries`, logo abaixo da pasta do seu projeto para sua pasta `home`, na RPi, através da janela _Remote Systems_. Para fazer isso, basta clicar e segurar a pasta Binaries e arrasta-la para o Home em Remote Systems.

Note que ao tentar executar o arquivo pelo terminal SSH, será exibida uma mensagem de erro, dizendo que não é possível executar o binário:

```text
./MyFirstApp
```

```text
-sh: ./MyFirstApp: Permission denied
```

Para corrigir este problema, basta dar permissões de execução para o arquivo. Ainda no terminal SSH digite:

```text
chmod +x MyFirstApp
```

Pronto, basta rodar a aplicação:

```text
./MyFirstApp
```

```text
!!!Hello World!!!
```

### Configurando o GDB no Eclipse

Acesse o menu "_Run &gt; Debug Configurations_":

* Clique duas vezes em _C/C++ Remote Application_;
* Na aba "_Main_", no campo "_Connection_", selecione o nome \("_RPi3_"\) da conexão que você criou anteriormente no _Remote System Explorer_;
* Em "_Remote Absolute File Path for C/C++ Application_", digite o caminho do executável na RaspberryPi . Por exemplo: "**/home/gbs/MyFirstApp**";
* Na aba "_Debugger_", digite "**arm-linux-gdb**";
* Clique em "_Apply_"e depois em "_Debug_";
* Ao abrir a janela perguntando se você deseja abrir a perspectiva de "_Debug_", apenas clique em _Yes_;

### Configurando o Eclipse para Copiar seu Executável no _Target_ Automaticamente

Clique com o botão direito no seu projeto, na janela da esquerda chamada _Project Explorer_, e acesse propriedades. 

Na janela exibida, navegue em "_C/C++ Build &gt; Settings_". Clique na aba "_Build Steps_" e digite o seguinte comando no campo "_Command_"do bloco "_Post-build steps_": **scp MyFirstApp gbs@10.1.1.100:/home/gbs**

O comando acima faz com que o Eclipse copie seu binário para o _Target_, na pasta "`/home/gbs`", a cada novo _build_. Apague o arquivo via terminal SSH: 

```text
rm /home/gbs/MyFirstApp
```

e em seguida, compile o projeto novamente e verifique que o novo binário estará disponível na pasta e pronto para execução: 

```text
ls
./MyFirstApp
```

### Configurando e Linkando Bibliotecas Externas no Eclipse

Três configurações devem ser realizadas no intuito de linkar uma biblioteca a um projeto do Eclipse:

* **Definir o diretório de headers da biblioteca**: A adição deste diretório no projeto possibilita que o indexer do Eclipse reconheça as funções, definições de constantes, declarações em geral da biblioteca. Uma vez reconhecida a biblioteca, é possível utilizar o recurso autocompletar durante a programação. Para adicionar um diretório de headers a um projeto do eclipse: Clique com o botão direito no projeto desejado e selecione P_roperperties &gt; C/C++ Build &gt; Settings_. Em seguida, no Menu da direita, selecione as opções: _Cross GCC Compiler &gt; Includes_ e, finalmente, adicione o path onde se encontra os headers da biblioteca a ser incluída.
* **Definir o nome da biblioteca para linkagem durante a compilação**: Além de definir o diretório de headers, é necessário especificar ao compilador quais são as bibliotecas que devem ser linkadas com o executável do seu projeto. Para isso: Clique com o botão direito no projeto desejado e selecione _Properperties &gt; C/C++ Build &gt; Settings_. Em seguida, no Menu da direita, selecione as opções: _Cross GCC Linker &gt; Libraries_ e, finalmente, adicione o nome das bibliotecas que deseja linkar com seu projeto. Note que, em C, apesar de os executáveis de bibliotecas normalmente serem nomeados como `libNOMEDABIBLIOTECA.so`, deve- se adicionar apenas o `NOMEDABIBLITOECA`, sem o _lib_ e o _.so_. Ex: se o nome do executável da biblioteca é `libpigpio.so`, adiciona-se somente `pigpio`.
* **Definir o diretório onde se encontra o executável da biblioteca**: Além de definir quais bibliotecas deseja-se linkar com o executável, é necessário indicar no projeto, o diretório onde tal executável se encontra, caso a biblioteca seja externa ou não esteja incluída na _GLibC_. Navegue até o mesmo ponto descrito no passo anterior: Clique com o botão direito no projeto desejado e selecione _Properperties &gt; C/C++ Build &gt; Settings_. Em seguida, no Menu da direita, selecione as opções: _Cross GCC Linker &gt; Libraries_. Note que existe uma barra de rolagem lateral e, ao rolá-la para baixo, uma nova opção será exibida: _Library Search Path_:. Este é o local onde deve ser indicado o diretório contendo o executável da biblioteca a ser adicionada.

### Configurando o Path de Bibliotecas Externas no GDB

Normalmente, para debugar uma aplicação remotamente que foi compilada com alguma biblioteca externa \(não incluída na _GLIBC_\), é necessário definir o _path_ de tal biblioteca em um arquivo de configuração do GDB, chamado `.gdbinit`. Esse arquivo, na verdade, é utilizado para passar parâmetros ao _gdb_, que normalmente seriam passados via linha de comando. 

Crie um arquivo chamado `.gdbinit` e adicione a seguinte linha no arquivo:

```text
set solib-search-path /PATH/DA//BIBLITOECA
```

Salve o arquivo e adicione-o nas configurações de _Debug_ do seu projeto. Acesse o menu "_Run &gt; Debug Configurations_":

* Selecione a configuração já realizada no passo descrito na seção de _Configuração do GDB no Eclipse._
* Na aba "_Debugger_", no campo "_GDB command file_", clique no botão browse e selecione o path do arquivo `.gdbinit`;

_Obs: a\) É possível selecionar um path qualquer para o arquivo ou; b\) deixar essa opção inalterada e criar o arquivo na raiz do seu workspace atual_;

