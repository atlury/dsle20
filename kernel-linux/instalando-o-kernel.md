# Instalando o Kernel

Para fazer a instalação do kernel Linux que compilamos é simples, basta chamar o comando `install` do próprio Makefile:

```text
make install
```

Este, faz a instalação no _host_ por padrão, ou seja, na máquina de desenvolvimento.

Os arquivos gerados estão disponíveis no diretório `/boot`. São gerados alguns arquivos, como:

* **vmlinuz-&lt;version&gt;**: Imagem do kernel comprimida;
* **System.map-&lt;version&gt;**: Endereços dos símbolos do kernel \(obsoleto\);
* **config-&lt;version&gt;**: Arquivo de configuração desta versão do kernel;

Além disso, é possível alterar o diretório raiz de instalação do arquivos, este é feito através da variável de `$INSTALL_DIR`:

```text
make INSTALL_DIR=<install_dir> install
```

Normalmente esse procedimento não é utilizado em sistemas embarcados. Via de regra, copia-se a imagem do kernel Linux para algum dispositivo de armazenamento, como um cartão SD.

