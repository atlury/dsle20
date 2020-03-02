# Parâmetros Command Line

Conforme apresentado na prática de Bootloader, em especial a etapa de montagem do U-Boot, é possível também passar parâmetro de inicialização do kernel Linux sem a necessidade de recompilá-lo.

Revisitando este conceito, temos que os parâmetros são passados através de uma string que define vários argumentos para o kernel Linux:

* **root=**: indica o caminho do RootFS;
* **console=**: redirecionamento do terminal para algum periférico;
* **rootwait**: espera indefinidademente a inicialização do dispositivo onde o RootFS esta armazenado.

Além disso, pode ser definido, ainda no U-Boot a variável **bootargs.**  Bem como pode ser definido dentro do próprio Device Tree, quando a plataforma utilizar-se de um.

Outra maneira de ser definido é durante a configuração do kernel, através da variável CONFIG\_CMDLINE. Contudo, como esperado a imagém do kernel possuirá estes argumentos internamente.

Por fim, há um caso específico da RPi 3 que é o arquivo `cmdline.txt`, que permite ser definido. Para mais informações basta consultar a página dos [parâmetros do kernel](https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html).

