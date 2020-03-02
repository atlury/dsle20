# \[LAB\] Configurando a Comunicação Serial

## Configurando a Comunicação Serial com a RPi 3

Por padrão, a Raspberry Pi possui duas built-in _UARTs_, uma comum _\(PL011\)_ e outra _mini UART_. Essa última, é limitada e carece de alguns recursos básicos como break detection, bit de paridade, dentre outros. Alem disso, a _mini UART_ possui uma FIFO menor quando comparada à _PL011_ e sua baudrate é linkada ao clock da GPU, ou seja, a taxa de transmissão da _mini UART_ varia de acordo com a oscilação do clock da GPU.

O módulo BT \(bluetooth\) da RPi 3 necessita de uma UART para funcionar e, por padrão, o BT da RPi 3 é conectado à UART _PL011_, tornando-a inutilizável para o usuário. No entanto, o firmware da GPU permite que o usuário escolha uma dentre as três opções:

* Desabilitar o módulo BT;
* Utilizar o módulo BT com a _mini UART_;
* Utilizar o módulo BT com a UART _PL011_;

A princípio, a utilização da _mini UART_ para redirecionamento de console é suficiente, pois além da interação entre usuário e target via shell possuir um fluxo de dados baixo, existe a possibilidade de realizar a comunicação via rede \(SSH\). Portanto, será necessário apenas ativar o redirecionamento do console para a _mini UART_. Para tal, acesse a RPi via SSH e adicione as seguintes linhas no final do arquivo `config.txt`:

```bash
ssh pi@10.1.1.100
```

```bash
sudo nano /boot/config.txt
[..]
dtparam=audio=on
enable_uart=1
```

{% hint style="info" %}
Para salvar as alterações feitas em um arquivo com o nano, utilize as teclas `CTRL+X, Y`, `Enter`.
{% endhint %}

Para maiores informações, consulte a [documentação da UART](https://www.raspberrypi.org/documentation/configuration/uart.md) no site da RPi. Após realizar a configuração acima, desligue a Raspberry Pi,

```bash
sudo poweroff
```

e faça a conexão entre o adaptador USB-Serial \(TTL\) e a placa. Certifique-se de escolher a opção/jumper 3.3v caso o adaptador permita. Por padrão, a RPi roteia os pinos `GPIO14` e `GPIO15` como _TX_ e _RX_ da serial principal \(aquela que não está sendo utilizada pelo módulo BT\), respectivamente.

![](../.gitbook/assets/image%20%2827%29.png)

Esses GPIOS estão mapeados nos _pinos 08 e 10_, respectivamente, do conector geral de 40 pinos. Os _pinos 01 e 02_ de tal conector são aqueles fisicamente próximos da borda oposta às entradas USB. O _pino 01_ é o pino mais interno e o _pino 02_ é o mais externo, próximo da borda lateral. As figuras a seguir exibem a descrição completa do conector de 40 pinos e indicação dos pinos fisicamente. Após analisar as figuras, faça as três conexões, _TX_, _RX_ e _GND_, entre seu adaptador e a RPi3.

![](../.gitbook/assets/image%20%2810%29.png)

### Configurando Acesso ao USB no Ubuntu

Para acessar a Serial no Ubuntu com o usuário padrão \(você\), dois procedimentos são necessários: Primeiramente deve-se criar o grupo `dialout`, pois por padrão a serial pertencerá a este e grupo e, o grupo ainda não foi criado e nem você pertence a ele:

```text
sudo groupadd dialout
```

  
O comando acima cria o grupo `dialout` no sistema. Então, é preciso adicionar você como um usuário deste grupo, ou seja, para que você tenha acesso à qualquer arquivo/dispositivo pertencente ao grupo:

```text
sudo gpasswd -a nome_do_seu_usuario dialout
```

O comando acima adiciona o usuário _nome\_de\_usuario_ ao grupo `dialout`. Para maiores informações sobre grupos e usuários:  [https://wiki.archlinux.org/index.php/users\_and\_groups](https://wiki.archlinux.org/index.php/users_and_groups)

Normalmente, existe uma opção para chavear um dispositivo de hardware entre o _host_ \(seu computador\) e _guest_ \(máquina virtual\). Verifique na sua aplicação da VirtualBox as opções ficam no menu _Devices&gt;USB._ Encontre o dispositivo que você deseja colocar na máquina virtual e selecione.

### Testando a Comunicação Serial

Conecte o adaptador serial na máquina de desenvolvimento e rode o comando `dmesg` no terminal. A saída será algo parecido com:

```bash
dmseg
```

```text
[5331.599292] usb 1-3: new full-speed USB device number 9 using xhci_hcd
[5331.740103] usb 1-3: New USB device found, idVendor=1a86, idProduct=7523
[5331.740106] usb 1-3: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[5331.740107] usb 1-3: Product: USB2.0-Serial
[5331.740607] ch341 1-3:1.0: ch341-uart converter detected
[5331.740888] usb 1-3: ch341-uart converter now attached to ttyUSB0
```

Procure pelo nome do arquivo criado pelo driver para manipular o dispositivo conectado. No caso acima, o nome do arquivo é `ttyUSB0`. Normalmente dispositivos seriais são mapeados como `ttyUSB0`, `ttyS0`, ou algo similar, e são criados dentro do diretório de dispositivos do Linux `/dev`. Não se preocupe com detalhes a respeito de drivers e arquivos de dispositivo neste momento, essas informações serão vistas mais adiantes no treinamento.

Após identificar seu dispositivo, abra o **putty** e o configure da seguinte maneira:

* _Connection type:_ Serial;
* _Serial line:_ Nome do seu dispositivo. No exemplo acima: `/dev/ttyUSB0`;
* _Speed:_ Este é o baudrate da conexão serial. Configure-o para: _115200_;

{% hint style="info" %}
Clique em _Default Settings_ e em seguida _Save_, de modo a salvar as configurações feitas e não precisar repeti-las sempre que iniciar o **putty**.
{% endhint %}

Clique em _Open_ para iniciar uma nova conexão e, se tudo foi configurado corretamente, ao ligar a RPi 3, um console deverá ser exibido na janela do **putty**. Caso tenha ocorrido algum erro, peça ajuda ao instrutor.

