---
description: >-
  Nesta está são realizados o download da distribuição Ubuntu 16.04 e do
  software VirtualBox. Então, é criada e configurada uma máquina virtual para
  servir de Host durante o treinamento.
---

# Configuração da Máquina Virtual

### Download da Imagem Ubuntu 16.04

Primeiramente vamos realizar o [download](http://releases.ubuntu.com/16.04/) da imagem do Ubuntu 16.04  LTS. Note que há duas versões diferentes da distribuição: a Desktop e a Server. Deve-se realizar o download da versão desktop, não obstante escolhemos a arquitetura do processador da nossa máquina, **32bits**.

Alguns fatos a serem notados: a terminologia LTS se refere a distribuições _Long Term Support._ Ou seja, são distribuições que apresentam suporte extendido \(cinco anos\). Além disso, essa distribuição é a 16.04, o primeiro número se refere ao ano de lançamento e no caso específico do Ubuntu, existem versões .04 e .10, que denotam a época do ano que foram lançadas. O Ubuntu realiza lançamentos em Abril e Outubro \(04 e 10\).

Apesar desta versão ser relativiamente antiga \(2016/1\) ainda esta dentro do suporte. Esta é também, uma das distribuições mais utilizadas, ainda nos tempos de hoje, possuindo assim diversas threads para solução de problemas na comunidade e suporte a diversas ferramentas.

### Download do Virtualbox

Para facilitar a configuração do ambiente de desenvolvimento, não iremos realizar a instalação imediata do Ubuntu nas nossas máquinas através de formatação ou dual-boot. Uma solução menos drástica é a instalação de uma Máquina Virtual. Está é uma forma de realizar a instalação de um sistema operacional de forma virtual no computador. 

Com esse objetivo, vamos utilizar a VirtualBox para realizar a virtualização do Ubuntu. Ele permite a instalação e utilização de um sistema operacional dentro de outro, assim como seus respectivos softwares, como dois ou mais computadores independentes, mas compartilhando fisicamente o mesmo hardware. O VirtualBox pode ser instalado em vários sistemas operacionais hospedeiros, incluindo: Linux, macOS, Windows, Solaris e OpenSolaris.

Primeiramente devemos realizar o [download](https://www.virtualbox.org/wiki/Downloads) da VirtualBox, nesta etapa deve-se escolher qual é o sistema host da nossa máquina, qual sistema esta atualmente rodando no seu computador. Por exemplo, caso seja o Windows 64bits, clicar no link indicado para download da versão do VirtualBox para Windows.

{% hint style="success" %}
Aloque **2048MB** de memória RAM, **128MB** de memória de vídeo, **40GB** de armazenamento para a máquina virtual e **2 núcleos** do processador, essas configurações são obtidas através do painel de configuração do VirtualBox, acessado em _Setting&gt;System_ e _Setting&gt;Video._
{% endhint %}

### Configuração da VM e Instalação da Distribuição

Clique no arquivo baixado \(instalador do VirtualBox\) para executá-lo e iniciar a instalação**.** Uma vez que a instalação tenha sido iniciada clique em Next. Em seguida, você estará pronto para instalar o VirtualBox pressionando Install e por fim, quando a instalação for concluida é só finalizar o instalador através do Finish.

{% hint style="warning" %}
Pode ser que as posições ou títulos das opções/menus estejam um pouco diferentes dos comentados durante a instalação, isto varia com as versões e sistemas.
{% endhint %}

{% hint style="danger" %}
Instale preferencialmente na **Língua Inglesa**, pois foi a versão utilizada para a criação do treinamento.
{% endhint %}

Quando o VirtualBox for iniciado, clique em _New_ no canto superior esquerdo ****e em seguida em _Next_. Nesta etapa, vamos inserir as informações do sistema que desejamos instalar \(Ubuntu 16.04\). Em seguida, será necessário configurar a quantidade de memória RAM pra operação da máquina virtual e também o armazenamento.

Finalizando a configuração da máquina virtual, será necessário a instalação do Ubuntu 16.04. Para tal, basta selecionar o diretório onde a imagem foi baixada \(conforme apresentado na seção anterior\) e realizar a instalação. A instalação é simples, não requer nenhum comentário adicional, apenas seguir os passos indicados durante a instalação.

### Configuração Inicial da Máquina

Nesta etapa, será realizada a configuração básica da VM para atender as necessidades do treinamento. Primeiramente devemos realizar o download de alguns módulos e ferramentas para o desenvolvimento da aplicação embarcada. Para tal, é necessário configurar a VM para acessar a internet.

{% hint style="danger" %}
Para continuar com a configuração certifique-se que seu computador tem conexão com a Internet. 

Além disso, habilite as opções: "_Download updates while installing Ubuntu_" e "_Install third-party software for graphics and..._ " durante a instalação.
{% endhint %}

#### Estabelecendo  Comunicação com a Internet

Abra o Virtualbox com o Ubuntu 16.04 e abra o navegador Firefox. Há duas formas de fazer isso, ou acesse o menu lateral direito e clique no atalho do navegador. Ou abra o _Dash_ com o botão `Super` em seguida digite Firefox e pressione `Enter`.

{% hint style="info" %}
Pressionando a tecla `Super` do teclado, irá aparecer uma tabela de atalhos do Ubuntu 16.04.
{% endhint %}

Tente acessar algum site, o navegador deve informar que você não possui conexão com a Internet. Caso contrário, pode avançar para próxima seção.

Outra forma de verificar se há conexão com a Internet é através do ping de um domínio que esteja online na internet. Para tal, abra o terminal do Linux `Ctrl+Alt+T` \(ou digite _Terminal_ na busca da _Dash_\),  digite a seguinte linha de comando:

```text
ping brandaogbs.github.io
```

Caso a resposta seja a confirmação do enviou e recebimento dos pacotes, algo como:

```text
PING brandaogbs.github.io (185.199.109.153) 56(84) bytes of data.
64 bytes from 185.199.109.153: icmp_seq=1 ttl=61 time=11.8 ms
64 bytes from 185.199.109.153: icmp_seq=2 ttl=61 time=12.0 ms
64 bytes from 185.199.109.153: icmp_seq=3 ttl=61 time=12.2 ms
64 bytes from 185.199.109.153: icmp_seq=4 ttl=61 time=16.3 ms
64 bytes from 185.199.109.153: icmp_seq=5 ttl=61 time=13.3 ms
```

Significa que tudo ocorreu conforme o esperado e a máquina virtual esta conectada à Internet.

Caso contrário, para estabelecer a comunicação com a Internet na nossa VM, é necessário configurar o adaptador e a rede tanto no Virtualbox quanto no Ubuntu 16.04.

Então, na aba superior do Virtualbox abra o menu _Settings_ e entre na seção _Network_ no menu lateral direito. Abrindo a seção _Network_ deve aparecer algumas abas de possíveis adaptadores de rede. Clique no _Adapter1_ e em _Attached To_ selecione a opção _NAT_.

Agora no Ubuntu, acesse a _Dash_ e pesquise por _Network_ abra este aplicativo. Na seção Ethernet desligue o adaptador de rede e ligue-o novamente. Após isto, tente novamente a conexão com um site no Firefox.

#### Update e Download de Pacotes Essenciais

Para realizar o update do repositório de downloads do Ubuntu:

```text
sudo apt-get update
```

Então, baixe os seguintes pacotes

|  |  |  |  |  |  |
| :--- | :--- | :--- | :--- | :--- | :--- |
| autoconf | build-essential | gawk | texinfo | libexpat1-dev | path |
| automake | curl | git | subversion | libncurses5-dev | pkg-config |
| bc | cvs | gperf | wget | libtool-bin | putty |
| bison | flex | help2man | python-dev | minicom |  |

Caso não esteja familiarizado, no Ubuntu um pacote pode ser instalado pelo shell da seguinte maneira:

```text
sudo apt-get install nome_do_pacote
```

Para facilitar a instalação dos pacotes sugeridos acima, execute o seguinte comando:

```text
sudo apt install autoconf bison flex texinfo automake help2man gawk libtool-bin libncurses5-dev libexpat1-dev python-dev patch curl cvs git bc build-essential subversion gperf unzip pkg-config wget minicom putty
```

### Configuração de Rede Local

Para obter uma conexão entre a máquina host e a plataforma embarcada, devemos estabelecer uma conexão via SSH entre ambos, a forma mais trivial de se fazer isto é via uma rede física. Portanto, é necessário configurar um IP estático no computador e também na RPi. 

Como estamos utilizando uma máquina virtual sob um outro sistema operacional uma das formas de se fazer essa configuração é, configurar um IP estático no SO padrão Windows, macOS ou Linux e configurar a máquina virtual como conexão _NAT_ e atribuir IP dinâmico pra ela. 

Vou exemplificar como configurar um IP estático no computado com Windows 10 e Ubuntu 16.04, contudo o processo é bem similar a outro sistema operacional, faça de acordo com o seu.

{% hint style="info" %}
Essa configuração utilizando IP fixo no _host_ e **NAT** no _guest_ da VM não é obrigatório, fique a vontade para montar a sua conexão da forma que achar melhor. Na VM por exemplo, há a opção de criar o dispositivo como **bridge**, faça como achar melhor. O único requisito é que a VM tenha conexão via Ethernet com a RPi.
{% endhint %}

#### IP Estático \(Windows10\)

Acesse as configurações do adaptador de rede: _Control Panel &gt; Network and Internet &gt; Network Connection &gt; Networking_. Em seguida, crie um novo adaptador de rede ou modifique a rede _Ethernet_ existente. Botão direito na conexão _Ethernet &gt; Properties &gt; Protocolo IPV4 \(TCP/IPv4\)_. Por fim, habilite a opção de IP Fixo e atribua os seguintes parâmetros:

| Address | Netmask | Gateway |
| :--- | :--- | :--- |
| 10.1.1.101 | 255.255.255.0 | 10.1.1.1 |

Ao fazer isto, sua conexão tera apenas o IP fixo configurado, então será necessário desfazer estas modificações para retornar a sua configuração padrão. Utilize esta configuração somente quando for se comunicar com a Raspberry Pi.

#### IP Estático \(Ubuntu 16.04\)

No _Network Connections_ é possível ver duas divisões uma referente as conexões de Ethernet e outra para as WiFi. Para criar uma nova rede clique em _Add_ e em seguida escolha o tipo de conexão desejada

Para configurar a rede no Ubuntu, devemos acessar o painel de configuração de rede. Acessando a _Dash_ \(botão `Super`\) basta pesquisar pelo termo _Network_ e __abrir a o aplicativo _Network Connections._ Ou podemos utilizar o icone de conexão no canto superior direito. 

Portanto em Network Connections, clicamos em _Add e_ escolhemos na caixa de seleção a opção _Ethernet_. Escolhar um nome para a conexão, por exemplo RPi e em seguida clique na opção _IPV4 Settings_.

Nesta aba é feito a configuração dos IPs e do DHCP, portanto como desejamos obter uma rede local com a placa de desenvolvimento, vamos escolher o _Method Manual_ e então configuramos nossa rede.

| Address | Netmask | Gateway |
| :--- | :--- | :--- |
| 10.1.1.101 | 255.255.255.0 | 10.1.1.1 |

Por fim basta salvar a rede, na próxima seção iremos configurar a nossa plataforma embarcada e aonal dessa configuração, devemos obter um canal de comunicação via SSH entre nossa máquina e a RPi.

### Instalações Adicionais

Caso esteja presenciando lags ou alguma lentidão na VM, verifique se o pacote de ferramentas de drivers foi instalado corretamente. Praticamente todos os aplicativos de VM possui um pacote desse tipo, para ser instalado após a criação da VM. Ex: **Guest Additions para VirtualBox**, VMware Tools para VMware ou Parallels Tools para o Parallels.

Para instalar esta extensão no VirtualBox, basta baixar o [Extention Pack](https://www.virtualbox.org/wiki/Downloads) no site oficial do projeto. É necessário baixar a versão correta do Extention Pack de acordo com a versão do VirtualBox instalado.

Em seguida, basta instalar o arquivo baixado e então abrir o VirtualBox e incialize o Ubuntu. No menu superior do VirtualBox clique em _Devices&gt;Insert Guest Addicition CD Image._

Opcionalmente, outro aplicativo que pode ser útil é o `caffeine-indicator` que é utilizado para evitar que o sistema, no caso o Ubuntu, durma ou entre em hibernação. Para fazer download basta executar o comando, lembre-se que este aplicativo é opcional:

```text
sudo apt-get install caffeine
```

E então busque pelo aplicativo `caffeine-indicator` na _Dash_ do Ubuntu, irá inicializar um ícone de um copo de café no menu superior do Ubuntu, basta clica e ativar o aplicativo.

