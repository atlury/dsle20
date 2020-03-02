# Montando Sistemas de Arquivos

### O comando `mount` e `umount`.

Para realizar a montagem em sistemas Linux é possível executar o comando `mount`. Este permite a montagem de sistemas de arquivos.

A forma básica do comando `mount` possui dois parâmetros: o dispositivo \(ou outro recurso\) contendo o sistema de arquivos a ser montado e o ponto de montagem. 

```text
mount device mountpoint
```

Ou em uma forma um pouco mais específica

```bash
mount -t type device mountpoint
```

Onde:

* **mount**: sem argumentos exibe todos os sistemas de arquivos montados atualmente;
* **-t type**: é opcional. Identifica o tipo de sistema de arquivo \(fat, ext3, ext4, swap, etc\);
* **device**: é o dispositivo de armazenamento, local ou remoto;
* **mountpoint**: é o diretório onde os arquivos se tornarão acessíveis.

Para realizar a desmontagem de um determinado sistema de arquivo é possível utilizar o comando `umount`.

```bash
umount device or mountpoint
```

É possível indicar tanto o dispositivo quanto o ponto de montagem a ser desmontado. Ele é necessário antes de remover quqalquer dispositivo \(um pendrive por exemplo\), pois o Linux mantém um cache na memória, de todas as alterações realizadas no dispositivo \(no intuito de melhorar a performance\). 

O comando `umount` garante que todas as alterações em cache sejam realizadas antes de desmontar o dispositivo.

### Montando um Sistema de Arquivo

Primeiro, cria-se o diretório no qual o sistema será montado, neste caso vamos criar um diretório chamado `pendrive` no `/mnt`.

```bash
mkdir /mnt/pendrive
```

Em seguida, depois de inserir a mídia, monta-se o pendrive no diretório criado.

```bash
mount -f vfat /dev/sda1 /mnt/pendrive
```

A partir deste momento, o conteúdo do pendrive fica disponível no diretório `/mnt/pendrive`. Lembre-se essa é uma característica dos sistemas Linux e já foi mencionada em etapas anteriores do treinamento, refere-se ao sistema de arquivo virtual.

```bash
ls /mnt/pendrive
```

```bash
docs helloworld.c helloARM foto.png
```

Por fim, para realizar a alterção dos arquivos da cache e desmontar o pendrive.

```bash
umount /dev/sda1
```



