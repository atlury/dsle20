# U-Boot vs. RPi

### Processo de Boot na RPi 3

O processo de boot da RPi é um tanto diferente do que os outros SoCs. Quando o hardware é energizado, quem assume o controle não é o CPU e sim a GPU, diferentemente dos boots abordados anteriormente. A imagem a seguir, ilustra resumidamente o processo de boot da RPi 3.

![](../.gitbook/assets/image%20%2825%29.png)

Inicialmente, o boot ROM, que é um código gravado na ROM interna do chip é executado por um pequeno núcleo RISC interno da GPU. Ele verifica se o modo de boot GPIO está ativado, se sim procura pela partição de boot no dispositivo equivalente da GPIO, caso contrário, segue uma ordem de procura definida por SD1, SD2, NAND, SPI e USB.

Enfim, ele encontra a partição de boot, monta-a e procura pelo arquivo `bootcode.bin`, que seria um bootloader de segundo estágio. Ao encontra-lo, carrega-o na cache L2 \(128K\) interna da GPU e executa-o.

O `bootcode.bin`, por sua vez, inicializa a RAM, procura o arquivo `start.elf` na partição boot. Este na verdade é o firmware da GPU, então carrega-o na RAM, agora devidamente inicializada, e executa-o. O `start.elf`, é o bootloader completo, que termina de inicializar o hardware, incluindo a CPU. Então, configura o hardware de acordo com parâmetros presentes nos arquivos `config.txt` e `cmdline.txt`**.** 

O arquivo `config.txt` pode ser visto como a interface da BIOS, onde cada opção da BIOS seria uma opção no neste arquivo. Ao passo que o arquivo `cmdline.txt` apresenta os parâmetros do kernel Linux. Existem diversas documentações trantando cada uma das opções disponível nestes arquivos, e as possíveis configurações.

Por fim, o kernel Linux é executado pela CPU na memória RAM, assumindo assim o controle completo do processador e então o bootloader deixa de existir na memória volátil.

Infelizmente esses binarios são de propriedade da Broadcom e não da Raspberry Foundation e seus códigos fontes não são divulgados. Em diversas fontes é comentado que se assinar um NDA com a Broadcom ela libera o datasheet e os principais fontes para a empresa, o que não é nosso caso no treinamento e em projetos em geral.

### Gravando U-Boot na RPi

Sendo os binários fechados e os códigos fontes não divulgados, como fazer então para carregar o U-Boot na RPi? Bem, a resposta mais simples seria não fazer nada. Contudo, existe uma maneira de se conseguir isso, para tal vamos explorar o processo de boot e inserir o nosso bootloader dentro dele, conforme apresentado na figura a seguir.

![](../.gitbook/assets/image%20%2812%29.png)

Apesar de fornecer apenas os executáveis, a Broadcom fornece uma ampla variedade de configurações por esse arquivo `config.txt` e `cmdline.txt`. O que viabiliza a utilização do processador em diversas plataformas e também flexibiliza as configurações.

Uma das configurações que é possível fazer, inclusive, é especificar a imagem do kernel para ser carregada, que nada mais é  que um executável. E é justamente nesse ponto, onde vamos "hackear" o processo de boot da RPi e inserir nosso bootloader.

Uma vez que é permitido especificar a imagem do kernel a ser executada, podemos driblar este passo, inserindo o U-Boot ao invés da imagem. Colocando o U-Boot, como se fosse o kernel, deste modo ao invés do `start.elf` carregar o kernel ele carrega e roda o U-Boot.

Inserindo esse passo a mais, conseguimos burlar o processo de boot natural da RPi, inserindo o nosso bootloader na inicialização da placa. 

Mas porque utilizar o U-Boot ao invés do bootloader padrão? Bom, o U-Boot fornece várias funcionalidades extras, como já foi apresentado durante as seções anteriores, e grande parte delas são bem úteis durante o desenvolvimento de sistemas Linux embarcado. Além disso, a nossa plataforma de estudo tem essa limitação, outras placas que vão possuir o firmware aberto, será obrigatório a instalação do U-Boot ou outro bootloader, então este processo, é de suma importância para o treinamento.

