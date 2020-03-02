# \[LAB\] Fazendo o Primeiro Boot do Sistema

Após gravar a imagem completa do SD card, abra o arquivo `config.txt`.

{% hint style="success" %}
Uma forma fácil de fazer a gravação através do Ubuntu é dar um duplo clique no sdcard.img e selecionar a opção de restaurar a imagem em um disco. Desta forma, já será aberto o aplicativo de manipulação de discos do próprio Ubuntu e basta seguir o processo.
{% endhint %}

Este arquivo esta presente na partição boot e faça as seguintes alterações:

```text
[...]
#fixes rpi3 ttyAMA0 serial console
#dtoverlay=pi3-miniuart-bt
enable_uart=1
```

isso habilitará o boot via serial \(conforme explicado nas seções anteriores\). Ao carregar seu sistema pela primeira vez, será necessário realizar algumas configurações básicas para ativar o servidor SSH e criar uma nova conta de usuário, por exemplo.

### Criando uma senha de root e nova conta de usuário

De acordo com a configuração realizada no Buildroot, somente o usuário root foi criado no sistema. Na tela de login, entre como _root_ e senha em branco. Note que o conteúdo da mensagem de boas vindas será exibido de acordo com sua configuração no Buildroot:

```text
Welcome to DSLE20
dsle20 login: root
#
```

Após logar no sistema, crie os diretórios `/home` e `/boot`. Em seguida adicione um segundo usuário no sistema:

```text
mkdir /home
mkdir /boot
adduser -h /home/gbs gbs
```

Nota: substitua o nome gbs pelo nome/nick de seu usuário desejado. Será necessário definir uma nova senha para o usuário. Aproveite e defina também uma senha para o root:

```text
Changing password for gbs
New password:
Bad password: too weak
Retype password:
passwd: password for gbs changed by root
```

Feito isso, altere o arquivo `/etc/sudoers` para dar permissões de root ao seu usuário por meio do comando `sudo`. Encontre as linhas referentes a permissões de usuário dos grupos _wheel_ e _sudo_ e remova seus respectivos comentários:

```text
nano /etc/sudoers
```

```text
[...]
## Uncomment to allow members of group wheel to execute any command## Uncomment to allow members of group wheel to execute any command
%wheel ALL=(ALL) ALL

[...]
## Uncomment to allow members of group sudo to execute any command
%sudo ALL=(ALL) ALL

[...]
```

Em seguida, crie o grupo sudo e adicione seu usuário nos grupos _dialout_, _root_, _sudo_ e _wheel_:

```text
 addgroup sudo
 nano /etc/group
```

```text
root :x:0:gbs
[...]
wheel:x:10:root, gbs
[...]
dialout :x:18:gbs
[...]
sudo:x:1003:gbs
```

Nota: é possível utilizar esse arquivo para adicionar usuários em qualquer grupo do sistema. Basta encontrar o grupo desejado e adicionar o usuário no final da linha. 

Caso já exista algum usuário definido naquele grupo \(como no caso do grupo _wheel_ acima, adicione uma vírgula, espaço e o novo usuário\).

### Configurando um Endereço IP estático

Para configurar um IP estático no novo sistema, edite o arquivo `/etc/network/interfaces` da seguinte maneira:

```text
nano /etc/network/interfaces
```

```text
[...]
auto eth0
iface eth0 inet static
    address 10.1.1.100
    netmask 255.255.255.0
    gateway 10.1.1.1
    pre-up /etc/network/nfs_check
    wait-delay 15
[...]
```

### Habilitando o SSH

Inicialmente, altere as configurações do arquivo`/etc/ssh/sshd_config`:

```text
nano /etc/ssh/sshd_config
```

```text
[...]
#LoginGraceTime 2m
PermitRootLogin yes
#StrictModes yes
#MaxAuthTries 6
#MaxSessions 10
[...]
# To disable tunneled clear text passwords, change to no here!
PasswordAuthentication yes
PermitEmptyPasswords yes
[...]
```

As configurações acima permitem 

* Logar como root via SSH; 
* Possibilita logar através de login e senha \(caso contrário somente com chaves públicas\); 
* Permite logar somente com login, sem a necessidade de digitar a senha. Este último será útil para copiar automaticamente o binário do seu programa pelo comando scp sem precisar digitar a senha.

Em seguida, altere o arquivo `/etc/shadow`. Este arquivo é responsável por armazenar informações seguras de contas de usuário. 

Os campos são separados por "`:`". O primeiro campo representa o nome de usuário, o segundo representa a senha de usuário encriptada e o terceiro, que devemos alterar, representa o número de dias que se passaram, desde a última alteração de senha para a respectiva conta de usuário. É necessário alterar esse campo de _0_ para um número qualquer \(_10_ por exemplo\) para que tal usuário possa logar na RPi via SSH:

```text
nano /etc/shadow
```

```text
root :$1$8N/irElt$uJ8THhDt.c2plt8cU336j/:10:0:99999:7:::
[...]
gbs:$1$cmF9.YCp$ATeyqkHK..4sDEq9jkbq71:10:0:99999:7:::
```

Para maiores informações sobre o arquivo shadow: [https://www.cyberciti.biz/faq/understanding-etcshadow-file/](https://www.cyberciti.biz/faq/understanding-etcshadow-file/).

Reinicie o sistema e teste o SSH, tanto com _root_ quanto seu usuário. Caso apareça alguma mensagem de warning relacionada à mudança de identificação de Host, apague o arquivo `∼/.ssh/known_hosts`:

```text
reboot
```

```text
ssh root@10.1.1.100
```

```text
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED! @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
[...]
```

```text
rm ~/.ssh/known_hosts
```

Após remover o arquivo, será pedido a autorização para gerar uma nova key para o IP 10.1.1.100. Digite _yes_ e prossiga com o login.

