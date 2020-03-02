# Compilando o Kernel

### Definindo o Compilador

O compilador que é chamado pelo Makefile do kernel é definido no arquivo como:

```bash
$(CROSS_COMPILE)gcc
```

Desta forma, para se não definirmos esta variável, deixando-a vazia, iremos compilar nativamente o kernel Linux. Observe que se `$CROSS_COMPILE` for vázio apenas `gcc` será chamado. Contudo, desejamos compilar o kernel para uma plataforma _target_, utilizando cross-compilação. Para tal, basta atribuir a variável `$CROSS_COMPILE` com o alias do toolchain desejado, portanto:

```bash
make ARCH=arm CROSS_COMPILE=arm-linux-
```

{% hint style="info" %}
Lembre-se de deixar o " **-** " no final, pois ele será concatenado com "**gcc**". Assim, teremos por exemplo: `arm-linux-gcc`, que é de fato nosso cross-compilador. Além disso, é importante pensar que este é apenas o prefixo da ferramenta, que pode ser concatenado as outras ferramentas como _gcc_, _ar_, _ld_, _strip_ e etc.
{% endhint %}

Além disso, neste momento é possível se utilizar de ferramentais normais de compilação do gcc. Assim, é possível por exemplo, para acelerar o processo, utilizar a flag de threads na compilação. Para tal, basta executar o comando `make` seguido de `-ji`, onde `i` representa o número de threads que podem rodar em paralelo.

### Saída

Ao final do processo `make`, são geradas algumas imagem. Uma delas é a **vmlinux**, ela esta gerada no diretório raiz, no formato ELF, descomprimida mas não é utilizada para execução, pois não é inicializável, sendo utilizada mais para depuração.

Além desta, em `arch/<arch>/boot/`, são geradas outras imagem, sendo **Image** uma imagem genérica do kernel Linux, que ao contrário da **vmlinux** é inicializável e comprimida. Bem como, as imagem **bzImage** \(x86\) e **zImage** \(ARM\), que são as imagens inicializáveis do kernel, de acordo com a arquitetura, sendo a de nosso interesse a da arquitetura _target_ \(ARM\). Por fim, há uma última imagem que é a **uImage** esta é opcional, sendo uma imagem do kernel para o U-Boot.

