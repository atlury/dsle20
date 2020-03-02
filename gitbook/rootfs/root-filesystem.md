# Root FileSystem

Conforme o que já foi apresentado, existe um sistema específico e este é montado na raiz principal da hierarquia, identificado por `/`. Este sistema em específico é chamado de Root Filesystem ou RootFS.

Os comandos `mount` e `umount` são programas \(executáveis\) e estão presentes em algum sistema de arquivo. Ao passo que o RootFS é o primeiro sistema de arquivo a ser montado em um sistema Linux e, portanto, não pode ser montado através de um comando `mount` convencional.

Isto decorre do fato de que quando o kernel é inicializado, ele realiza a montagem do RootFS. Lembre-se um dos parâmetros de command line passados para o kernel é justamento o **root=**. Este parâmetro especifica a localização do diretório onde será montado, pelo kernel, o RootFS.

Quando o RootFS não é devidamente definito através dos parâmetros de command line. Isto é, quando não é definido o parâmetro **root=** ou mesmo este é definido de forma errada. O sistema apresenta um erro, o famigerado Kernel Panic.

> Please append a correct "root="boot option Kernel panic - not syncing: VFS: Unable to mount root fs on unknown block\(0,0\)

### Localização

O RootFS pode ser montado de diferentes localidades, por exemplo, da particção de um HD, pendrive, cartão SD, ou memória flash NAND. É possível també, ser montado da rede, através do protocolo NFS, outra opção é também ser montado a partir da memória RAM, previamente carregada pelo bootloader.

Cada caso tem sua especificidade, cabe ao desenvolvedor do sistema escolher como iniciá-lo, como realizar as configurações e etc.





