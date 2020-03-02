# Sistema Multi-Usuários

Uma das primeiras características que notamos ao começar a trabalhar com sistemas Linux, é o fato deste ser um sistema operacional multi-usuários. Isto significa que existem diferenciações entre os usuários que operam a máquina. Distinguindo o contexto de acesso a determinadas regiões ou diretórios e também certas operações dentro do sistema.

Em especial, existe o usuário _root_ este é o usuário "administrador" do sistema, possuindo acesso privilegiado sobre o sistema. Esse acesso privilegiado, consede ao usuário _root_ o poder de executar operações que necessitem de permissão elevada, tais como: criar um sistema de arquivos, montar uma partição, adicionar e remover um software, configurar rede, operar arquivos em diretórios com privilégio e etc.

Por padrão, o Ubuntu não permite que usuário _root_ faça login no sistema, essa opção é bloqueada mas pode ser alterada, contudo não é uma atitude recomendada. No entanto, em suas configurações padrão, o Ubuntu usa uma política de que o primeiro usuário criado no sistema \(normalmente aquele logo depois da instalação\), recebe a permissão de executar as operações privilegiadas do _root_, através do comando `sudo`.

Para exemplificar a utilização do comando `sudo` vamos realizar a seguinte demonstração. Ao tentar montar uma partição, através do comando `mount`.

```text
mount /dev/sda2 /mnt/disk_test
```

Recebemos a seguinte mensagem, negando a permissão do nosso usuário:

> mount: only root can do that

Ou seja, para realizar esta operação, é necessário utilizar um usuário com permissão de _root,_ portanto devemos utilizar o comando `sudo`, demonstrando que realmente queremos utilizar este comando com privilégios.

```text
sudo mount /dev/sda2 /mnt/disk_test
```

{% hint style="info" %}
No Ubuntu 16.04,  a senha de _root_ é definida durante a instalação do sistemas. Por padrão, algumas distribuições utilizam como senha a palavra _root_ ou mesmo _toor._ Este tópico será abordado em outro momento do treinamento.
{% endhint %}



