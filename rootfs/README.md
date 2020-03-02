# RootFS

### Sistemas de Arquivo

Sistemas de Arquivo são utilizados para organizar dados, normalmente entre diretórios e arquivos, em dispositivos de armazenamento \(locais ou remotos\). Esta organização de diretórios e arquivos costuma ser feita de forma hierárquica, tal como foi utilizado ao longo de todo o treinamento.

Em sistemas Unix, aplicações e usuários exergam uma hierarquia global única. Isto significa, na prática, que podem ser compostos por diferentes sistemas de arquivo.

Ou seja, é uma grande árvore enraizada `/`, e mesmo assim temos sistema de arquivos em diferentes dispositivos e partições. Para evitar problemas de incompatibilidade o sistema de arquivos enraizados \(`/`\) é montado como parte do processo de inicialização. Cada um dos outros sistemas de arquivos que você criar não será utilizável pelo sistema Linux até que esteja _montado_ em um _ponto de montagem_.

Um exemplo é o diretório `/boot`, o `/` e o `swap`, este são normalmente partições diferentes e utilizam sistemas de arquivos diferentes, normalmente. 

* `/boot` - fat
* `/` - ext4
* `swap` - swap

No conjunto atual de sistemas de arquivos montados, um ponto de montagem \(mount point\) é simplesmente um diretório no qual o sistema de arquivos em um dispositivo é inserido na árvore. 

Montagem é o processo de tornar o sistema de arquivos no dispositivo accessível. Por exemplo, é possível montar sistemas de arquivos em partições de unidade de disco rígido como `/boot`, `/tmp` ou `/home`, é possível montar o sistema de arquivos em uma unidade de disquete como `/mnt/floppy`, ou em um CD-ROM como `/media/cdrom1`. 

Como você pode ver, os pontos de montagem podem estar no diretório-raiz ou em um subdiretório bem abaixo da árvore.

Assim, um ou mais sitemas de arquivos são montados em localizações espcíficas nessa hierarquia de diretórios. Quando um sistema de arquivo é montado num diretório, o mount point, e o onteúdo do diretório irá refletir o conteúdo do dispositivo de armazenamento \(físico\). Quano o sistema de arquivo é desmontado, o mount point torna-se vazio novamente.

Essa funcionalidade permite que usuários e aplicações acessem diretórios e arquivos de forma fácil, independemente de sua localização física ou tipo de sistema de arquivo.

