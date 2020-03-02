# U-Boot

Como mencionado anteriormente, o U-Boot é o bootloader mais utilizado, sendo adotado por diversos fabricantes de SoC. 

O projeto é open-source e fornecido pela DENX, empresa de software alemã, através do [repositório oficial](http://www.denx.de/wiki/U-Boot). Além disso, o mesmo possui uma comunidade muito ativa de desenvolvedores e também uma vasta [documentação](http://www.denx.de/wiki/U-Boot/Documentation). 

Tanto a comunicação, como o suporte, são feitos através de uma [lista de emails](https://lists.denx.de/pipermail/u-boot/), assim como outras ferramentas open-source. Desde 2008, mantém um intervalo fixo de releases, sendo nos períodos de dois ou três meses uma nova versão é lançada, normalmente identificados com a cada \(YYYY.MM\).

### Funcionalidades

As principais funcionalidades do U-Boot podem ser listadas de forma resumida, como:

* Listar informações de hardware;
* Manipulação da RAM \(leitura, escrita, comparação, testes\);
* Manipulação de memórias FLASH \(leitura, escrita\);
* Boot via flash;
* Boot via rede \(bootp, tftp, dhcp\)
* Boot via SD/MMC ou USB;
* Suporta vários sistemas de arquivo \(fat, ext2/3, ubifs, jffs2, etc\);
* Suporta scripts e variáveis de ambiente;
* Capaz de executar código bare-metal;
* Fornece linha de comando para o usuário;
* Carrega e executa o kernel \(parametrização\).

### Configuração e Instalação

Normalmente, o fabricante fornece os fontes do U-Boot para a sua placa, quando esta utiliza o U-Boot como bootloader. No entanto, quando o fabricante não fornece os códigos, assim como no caso da RPi3, os fontes genéricos podem ser baixados via[ repositório ftp](ftp://ftp.denx.de/pub/u-boot/) ou pelo[ repositório oficial do git](https://github.com/u-boot/u-boot).

Assim como o Crosstool-ng  e quase todas as ferramentas que vamos estudar no treinamento, o U-Boot também fornece alguns arquivos de configuração pré-definidos, sendo disponibilizados pra algumas placas. Esses arquivos podem ser visualizados no diretório `configs` presente dentro do diretório da ferramenta, isto é, o diretório gerado na extração do download.

É comum que esses arquivos de configurações sejam mantidos pelo próprio fabricante, sendo ele o responsável por atualizar a árvore principal do projeto \(u-boot\) no caso.

Caso a sua plataforma que estamos utilizando tenha as configurações já definidas no arquivo de configuração, é altamente recomendado utiliza-lo. Isto, principalmente, pois o U-Boot utiliza-se de drivers para interagir com o hardware da placa embarcada, assim, utilizando o arquivo de configuração já estabelecido, será um caminho mais simples, rápido e estável.

Para carregar uma configuração, basta executar o comando `make` seguido do nome do arquivo de configuração, no caso da plataforma do nosso treinamento:

```bash
make rpi_3_32b_defconfig
```

Além disso, é necessário especificar o toolchain de cross-compilação, uma vez que estamos na plataforma _host_ e o código deve rodar na plataforma _target._ Desta forma_,_ para que ele gere um binário para a arquitetura do _target_ é necessário relacionar o compilador específico.

Para compilar o U-Boot, é preciso fornecer o cross-compilador por meio da variável de ambiente `CROSS_COMPILE`:

```bash
export CROSS_COMPILE=arm-linux−
```

Ao final do processo, após carregar a arquitetura e configurar o cross-compiling toolchain,  é só dar um `make` novamente, como saída, será gerado o binario `u-boot.bin`.

### Gravação no _target_

O processo de gravação do binário gerado para o _target,_ é normalmente dependente do hardware utilizado.

Se o _target_ permitir carregar o bootloader de uma mídia removivel por exemplo, então esse binario pode ser gravado numa mídia  deste tipo, como por exemplo: SD Card, MMC, HDD e etc. 

Porém, para _targets_ baseados em memória Flash ou _targets_ que requerem que o bootloader esteja na Flash normalmente fornecem uma ou mais das seguintes opções:

* O bootloader de primeiro estágio pode fornecer algum mecânismo de escrita na Flash;
* O processador pode fornecer um tipo de monitor de boot \(uma espécie de shell básico\) que se comunica via Serial ou USB;
* É fornecido pinos para a gravação via JTAG, como feito em outro micros que possibilitam o update de bootloader;
* Se o U-Boot já for o bootloader de segundo estágio, é possível gravar uma nova versão.

{% hint style="danger" %}
Se o U-Boot for utilizado para gravar uma norva imagem, é necessário um certo cuidado, pois caso envie um arquivo com erro ou corrompido e ele sobreescrever, não há o que fazer, a placa fica inutilizável, pois o processo de boot foi corrompido.
{% endhint %}

