# Montando o RootFS

Para a montagem do RootFS de uma partição de HDD ou Pendrive:

```text
root=/dev/sdXY
```

onde X é uma letra que dica o dispostivo, ao passo que Y é um número que indica a partição no dispositivo. 

Por exemplo, **root=/dev/sda2** significa que a segunda partição do segundo dispositivo.

Para a montagem do RootFS de uma partição de um cartão SD é similar ao HDD e pendrive, a principal diferença é o dispositivo. Para realizar a montagem em um cartão SD, faz-se:

```text
root=/dev/mmcblkXpY
```

onde o X e Y são números que marcam, respectivamente, o dispositivo e a partição. 

Um exemplo deste tipo de montagem é **root=/dev/mmcblk0p2**, ou seja, o RootFS será montado na segunda partição do primeiro dispositivo.

Caso a escolha seja montar de partição de uma memória flash:

```text
root=/dev/mtdblockX
```

onde X é um número que indica a partição na memória. 

Por exemplo, **root=/dev/mtdblock3**, indica que é a quarta partição de um chip NAND \(lembre-se o primeiro dispositivo é o 0\).

### Montando o RootFS via Rede

Desde que sua rede esteja funcionando, entre o computador _host_ e a plataforma _target_, seu RootFS pode ser um diretóriio na sua máquina de desenvolvimento, e ser exportado via NFS \(_Network File System_\).

Para tal, é necessário estabeler a comunicação entre as duas partes e além disso, é necessário a presença de um servidor NFS na máquina _host_ e um cliente NFS na plataforma _target_.

![](../.gitbook/assets/image%20%2818%29.png)

Utilizando a montagem do RootFS através da rede facilita alguns processos. A tarefa de atualizar arquivos no RootFS se torna muito simples e rápida, não necessitando executar o comando de reset.

Existe também a possibilidade de ter um RootFS maior, na realidade, bem grande. Podendo invluir ferramentas e/ou binários que não aberiam no equipamento embarcado. Isso, pois a localização destes arquivos esta no computador _host_.

Além disso, há a possibilidade de gerar toolchains nativos, apesar de cross-compilação ser mais eficiente em questão de velocidade.

Como mencionado, a máquina de desenvolvimento precisa ter um servidor NFS, para tal, devemos instalar um NFS Server.

```bash
sudo apt install nfs-kernel-server
```

Além disso, também é necessário exportar o diretório RootFS no arquivo `/etc/exports`:

```bash
∼/dsle20/RootFS_NFS/ 10.1.1.100(rw, no_root_squash, no_subtree_check)
```

onde **10.1.1.100** é o IP do cliente NFS, no caso, este é o IP que configuramos na RPi durante as práticas anteriores. Ao passo que **\(rw, no\_root\_squash, no\_subtree\_check\)** são as opções do NFS Server para esse diretório.

Para re-iniciar o NFS Server na máquina de desenvolvimento precisar executar o seguinte comando.

```bash
sudo /etc/init.d/nfs-kernel-server restart
```

Agora, na plataforma _target_, o kernel Linux deve ser compilado com as seguintes opções habilitadas:

* `CONFIG_NFS_FS=y`: Garante suporte como cliente NFS;
* `CONFIG_IP_PNP=y`: Configura o IP durante o processo de boot;
* `CONFIG_ROOT_NFS=y`: Garante suporte para o RootFS via NFS.

O kernel deve ser inicializado com os seguintes parâmetros:

* `root=/dev/nfs` \(RootFS via NFS\);
* `ip=10.1.1.100` \(IP do _target_\);
* `nfsroot=/10.1.1.1:/dsle20/RootFS_NFS/` \(Detalhes de IP e local do diretório no Server-_host_\).

### Montando o RootFS na Memória

Além disso, é possível também ter uma image de RootFS integrada na imagem do kernel, como mencionado anteriormente. Desta forma, o RootFS é carregado na memória RAM e assim como o kernel Linux.

O mecânismo utilizado para fazer este feito é chamado de `initramfs` . Lembre-se no momento em que estavamos configurando o U-Boot, através das linhas de comando, foi fornecido uma informação 

{% code title="U-Boot" %}
```bash
bootz ${kernel_addr_r} - ${fdt_addr_r}
```
{% endcode %}

Onde o parâmetro central ' `-` ' era justamente o endereço do RootFS na memória RAM, o `initramfs`. Como não utilizamos, estava com um valor nulo.

Este mecanismo é capaz de integrar um arquivo comprimido do RootFS na imagem do kernel Linux ou mesmo carregar o arquivo comprimido de forma separada, pelo bootloader.

Este paradígma possui algumas características que podem ser encaradas como vantajosas e outras como desvantagens em relação aos outros métodos.

Como vantagens é possível levantar algumas características como, um tempo de boot mais rápido, já que normalmente o tamanho do RootFS é menor. Uma eficiência mais elevada, pois as aplicações já estão na memória. Além disso, pode atuar como um passo intermediário para montar o verdadeiro e maior RootFS. Normalmente isto é utilizado em servidores e desktops. Em contra partitada, uma vez que o `initramfs` é montando na memória RAM, o armazenamento é volátil.

O conteúdo de uma imagem `initramfs` é definada nna configuração do kernel, com a opção `CONFIG_INITRAMFS_SOURCE`. Seu valor pode ser o caminho para um diretório contendo o RootFS ou o caminho para um arquivo comprimido cpio, arquivo de texto descrevendo o conteúdo do `initramfs`.

O processo de build do kernel Linux irá integrar automaticamente o conteúdo da configuração acima na imagem do kernel.

Mais informações podem ser encontradas em: [KernelDoc/ramfs-rootfs-initramfs](https://www.kernel.org/doc/Documentation/filesystems/ramfs-rootfs-initramfs.txt) e[ KernelDoc/early-userspace/README](https://www.kernel.org/doc/Documentation/early-userspace/README)

