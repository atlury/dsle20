# Sistema de Arquivos Virtuais

Uma das funcionalidades mais atrativas do kernel Linux é seu sistema de arquivos virtuais. Através deste, o kernel disponibiliza informações do próprio kernel e sistema através de arquivos virtuais.

Arquivos virtuais permitem que aplicações “enxerguem” diretórios e arquivos que não existem fisicamente, tanto as aplicações quanto o usuário conseguem enxergar diretórios e arquivos que na verdade não existem fisicamente num disco rígido por exemplo. Esse tipo de arquivo é criado e atualizado _on the fly,_ ou seja, assim que uma requisição é feita. Apesar do usuário e aplicação poderem enxergá-los o tempo todo no sistema.

Quem implementa essa funcionalidade é uma camada chamada de  VFS \(_Virtual FileSystem_\). Ela possibilita que funções de acesso como `read,` `write`, `open` e `close`, por exemplo, sejam utilizadas em arquivos virtuais. Para melhor exemplificar essa funcionalidade segue os seguintes exemplos.

* **Exemplo 1**: Copiando um arquivo físico em um dispositivo de armazenamento \(pendrive\).

Para copiar um arquivo no Linux, utilizamos o comando `cp` seguido do arquivo/diretório a ser copiado e o endereço para onde desejamos copia-lo.

```bash
cp /dsle2020/teste.txt /mnt/pendrive
```

Nota que o arquivo teste.txt que esta fisicamente presente dentro do RootFS ou dentro do cartão SD será copiado de `/dsle2020/` para `/mnt/pendrive/` mesmo esse diretório `pendrive/` sendo o pendrive propriamente dito, físico. 

O kernel simplesmente copia o arquivo para o pendrive \(físico\), note que o conteúdo da pasta pendrive não existe no seu sistema apesar de enxerga-la. Mas a ideia é, sua árvore de diretótios tem a pasta `/mnt` na raíz, então monta-se seu pendrive nessa pasta e quando rodar o comando para listar os arquivos,  `ls`, nessa pasta. Você verá e conseguirá acessar todo o conteúdo do pendrive, mas na verdade não existe nada no seu disco rigido, não existe uma cópia do pendrive no disco, está tudo no pendrive e quando você faz a copia do arquivo o mesmo acontece ele vai direto para o pendrive.

* **Exemplo 2**: Listando informações de memória em uso pelo sistema.

Para listar informações de um arquivo, por exemplo, podemos executar o comando `cat`. Não obstante, existe um diretório específico do Linux, chamado `/proc/` que quando desmontado, não possui nenhum arquivo \(caso abra o cartão SD no seu computador, por exemplo\). Este diretório contém um diretório para cada processo em execução, mais especificamente um diretório virtual.

Além disso, é possível listar o arquivo `meminfo`, que exibe informações de memório em uso, mas novamente, fisicamente no cartão SD, não tem nada.

```bash
cat /proc/meminfo
```

* **Exemplo 3**: Escrevendo na porta serial.

O último exemplo, é escrever uma _string_ ou caracteres na porta serial. O diretorio `/dev/` contém arquivos para todos os dispositivos ativos / ou conectados ao sistema. Situação similar a anterior, caso você conecte ao seu computador e inspecione a pasta ela estará vazia. 

O Linux popula esse diretório em tempo de execução, mas enfim, um dos arquivos que existe dentro desse diretório representa sua porta serial. Quando você escreve algum arquivo nele, o kernel faz o direcionamento ao hardware físico pra você, simples assim, se tem driver funcional você verá um dispositivo no seu computador.

```bash
echo “teste” > /dev/ttyS0
```

