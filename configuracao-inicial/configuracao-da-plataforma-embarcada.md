---
description: >-
  Nesta seção é realizada a istalação da distribuição RaspbianST, a habilitação
  da comunicação SSH e a configuração de uma conexão de rede estática entre o
  Host e o Target.
---

# Configuração da Plataforma Embarcada

## Configuração do Ambiente Embarcado

Nesta etapa vamos realizar a configuração inicial do nosso sistema embarcado. Para tal, vamos instalar um sistema operacional da comunidade do Raspberry Pi. Este é um sistema completo, e será utilizado nas primeiras atividades do treinamento. Contudo, ao longo do treinamento realizaremos a montagem e configuração de um sistema operacional para aplicações reais.

### Download do Raspian Stretch Lite

Faça o download do [Raspian-Buster Lite](https://www.raspberrypi.org/downloads/raspbian/) \(versão sem desktop\) e instale-o em um cartão microSD. Para realizar a gravação dele no cartão SD, recomenda-se a utilização do software [Etcher](https://www.balena.io/etcher/).

O Etcher é uma ferramenta gráfica multiplataforma para gravação de imagens \(sistema operacional no nosso caso\) em outras unidades. 

Primeiramente, faça o download do Raspbian-Stretch Lite e do Etcher, então instale o Etcher em seu computador e conecte o cartão microSD no mesmo. Abra o Etcher e selecione o arquivo da imagem do Raspbian \(.img ou .zip\) em seu computador. Em seguida, selecione a unidade do cartão microSD onde deve ser gravado o Raspian e aperte em _Flash!_ para iniciar a gravação da imagem no cartão.

Se estiver utilizando o Ubuntu ou outro sistema Linux, talvez seja necessário instalar o `zenity`. Mais informações sobre a gravação do microSD para diversas plataformas podem ser vistas em:

* [Windows](https://www.raspberrypi.org/documentation/installation/installing-images/windows.md)
* [Linux](https://www.raspberrypi.org/documentation/installation/installing-images/linux.md)
* [MacOS](https://www.raspberrypi.org/documentation/installation/installing-images/mac.md)
* [ChromeOS](https://www.raspberrypi.org/documentation/installation/installing-images/chromeos.md)

### Configuração de Rede e SSH

{% hint style="info" %}
Esta seção é destinada a configuração para o setup que possui um **Monitor HDMI** e um **Teclado USB**. Caso não possua esse items utilize a seção [Configuração de Rede e SSH \(headless\)](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-plataforma-embarcada#configuracao-de-rede-e-ssh-headless).
{% endhint %}

Após instalar o _Raspian-Stretch Lite,_ conecte um teclado USB e um monitor HDMI na RPi, e então ligue-a. Ela irá carregar o sistema e então as informações de login serão pedidas. Por padrão, o Raspbian possui o usuário  `pi` e a senha `raspberry`.

 Após logar no sistema, ative o servidor _ssh_. Para tal, acesse o menu de configurações da RPi, este é realizado através do comando:

```text
sudo raspi-config
```

Rode o comando acima para acessar o menu de configurações e acesse a seguinte opção:  _5 Interfacing Options_ -&gt; _P2 SSH_ -&gt; _YES._

Em seguida, atribua um IP estático para a RPi. Para isso, edite o arquivo `dhcpcd.conf`, localizado no diretório `/etc/`:

```text
sudo nano /etc/dhcpcd.conf
```

Este comando invoca o editor de texto _nano_ para a edição do arquivo. Então, procure pela linha "_Example static IP configuration_" e faça a seguinte edição:

```text
# Example static IP configuration:
#interface eth0
static ip_address=10.1.1.100/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=10.1.1.1

[..] 
```

Após editar o arquivo, salve-o pressionando `Ctrl+X`, então confirme as modificações pressionando `Y` e por último, não altere o nome do arquivo, apenas pressione `Enter`.

Esta edição possibilita a retenção de um IP estático para a RPi \(10.1.1.100\) e coloca como gateway o IP \(10.1.1.1\). Assim, será possível estabelecer uma comunicação entre a RPi e o nosso computador _host_ via _ssh._

### Configuração de Rede e SSH \(headless\)

Esta seção é destinada a configuração sem os periféricos de Monitor e Teclado USB. O processo é praticamente o mesmo da seção anterior, porém iremos fazer essas configurações diretamente no cartão SD evitando o uso dos periféricos externos.

Primeiramente grave a imagem do Raspbian Strech Lite normalmente no cartão SD, utilizando o Etcher. Após a gravação, serão criadas duas partições, a `boot` e a `rootfs`. 

Para habilitar a comunicação via SSH, abra a partição de `boot` no seu computador e crie um arquivo chamado `ssh`, utilize letras minúsculas e não adicione nenhuma extensão ao arquivo. Este arquivo sinaliza que durante o processo de boot da RPi é desejável que a comunicação SSH seja disponibilizada, equivalente ao processo da seção anterior utilizando o menu de configurações da RPi.

Em seguida, é necessário realizar a configuração da rede com IP fixo na RPi. Para tal, abra a partição `rootfs` e então econtre o arquivo `dhcpcd.conf` dentro do diretório `etc`. Talvez você precise de permissão para editar este arquivo, então entre com previlégios de administrador no caso do Windows ou no Linux, utilize o comando sudo, para ganhar previlégio.

Então, procure pela linha "_Example static IP configuration_" e faça a seguinte edição:

```text
# Example static IP configuration:
#interface eth0
static ip_address=10.1.1.100/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=10.1.1.1

[..] 
```

Pronto, basta salvar o arquivo e remover o dispositivo.

### Testando a Comunicação via __SSH

Para verificar se a configuração foi feita corretamente, tanto da máquina virtual quanto da RPi, basta conectar o conector RJ45 do cabo ethernet na RPi e no seu computador. Selecione a rede Ethernet no seu computador, de forma a se conectar com o cabo recém inserido.

Em seguida, ligue a placa a fonte de alimentação e abra o _Terminal_ no Ubuntu. Com o terminal aberto, iremos tentar realizar uma conexão entre o Ubuntu e a RPi através do programa `ssh`. Basta digitar o seguinte comando:

```text
ssh pi@10.1.1.100
```

Isto é, desejamos nos conectar via SSH a um usuário chamado **pi** no endereço 10.1.1.100. Então, basta digitar a senha do usuário, que no caso do Raspbian é por padrão a senha **raspberry.** Então deveremos ter acesso a nossa RPi.

Caso ao tentar se conectar apareça um erro tal como:

```bash
gbs@core:~$ ssh pi@10.1.1.100
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ECDSA key sent by the remote host is
SHA256:MfETDZ6CV+lZY7cjQhK57JT4nF+pcYTtjISd+iLN+nw.
Please contact your system administrator.
Add correct host key in /home/gbs/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in /home/gbs/.ssh/known_hosts:1
  remove with:
  ssh-keygen -f "/home/gbs/.ssh/known_hosts" -R 10.1.1.100
ECDSA host key for 10.1.1.100 has changed and you have requested strict checking.
Host key verification failed.

```

Significa que já há um histórico de comunicação estabelecido neste target e então basta limpar o arquivo através do comando:

```bash
  ssh-keygen -f "/home/gbs/.ssh/known_hosts" -R 10.1.1.100
```

{% hint style="warning" %}
Note que **gbs** é o meu nome de usuário, você deve adequar o comando ao seu nome de usuário. Ao longo de todo o treinamento utilizarei ele como exemplo nos comando, mas fique atento para realizar a modificação para atender ao seu sistema, o mesmo para os arquivos e diretórios.
{% endhint %}

Então basta digitar _yes_ e teremos acesso a nossa RPi.

```bash
gbs@core:~$ ssh pi@10.1.1.100
pi@10.1.1.100's password: 
Linux raspberrypi 4.19.75-v7+ #1270 SMP Tue Sep 24 18:45:11 BST 2019 armv7l

The programs included with the Debian GNU/Linux system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Debian GNU/Linux comes with ABSOLUTELY NO WARRANTY, to the extent
permitted by applicable law.
Last login: Thu Sep 26 01:25:03 2019 from 10.1.1.101

SSH is enabled and the default password for the 'pi' user has not been changed.
This is a security risk - please login as the 'pi' user and type 'passwd' to set a new password.

pi@raspberrypi:~ $ 
```

