# Utilizando Toolchains Pré-compilados

Em relação a utilização de um toolchain, existem basicamente duas formas: ou a utilização de uma toolchain já pré-compilada ou a criação de uma toolchain específica para a sua aplicação.

Na primeira opção, o uso de uma toolchain pronta, consiste no uso de uma toolchain pré-compilada normalmente fornecida pelo proprio fabricante do chip, ou empresas especializadas em toolchains para determinadas arquiteturas ou ainda algum fornecido por algum grupo de desenvolvimento da comunidade. 

Ao passo que a criação de uma toolchain de acordo com suas necessidades, é com certeza algo mais simples e específico. Para tal, existem diversas ferramentas que auxiliam no processo de montagem da toolchain e normalmente elas são usadas para o desenvolvimento de sistemas Linux embarcado.

### Toolchain pré-compilado

O uso de toolchains prontos é bem comum, desde que haja um fornecedor, e é uma das metodologias mais adotadas. Pois utilizar um toolchain pronto é fácil e rápido de configurar, e não é necessário muito conhecimento sobre o sistemas e etc. 

No entanto, este tipo de toolchain limita seu sistema, uma vez que sua aplicação fica amarrada com o as ferramentas fornecidas pelo toolchain, tirando o seu direito de escolha e restringindo suas escolhas de ferramentas. 

Por exemplo, se o fabricante fornece ferramentas como, o compilador e biblioteca C, você não tem muita opção a não ser utilizar o que ele te fornece, é até possível realizar algumas alterações, mas não há muito o que fazer. Ao invés da ferramente se adaptar as suas necessidades, sua aplicação que se adapta à ferramenta. 

Em muitos casos,  não há problema nenhum esse acoplamento, mas é sempre necessário certificar-se de que a toolchain pré-compilada atende seus requisitos, principalmente em termos de arquitetura do processador, endianness e etc.

Dentre as opções disponíveis, é possível usar algum toolchain fornecido pela propria fabricante, como a Freescale que costumam fornecer para as placas deles.

Ou ainda, é possível usar a toolchain de alguma empresa especializada como a Mentor Graphics, eles fornecem alguns toolchains para arquiteturas especificas, contudo boa parte é sobre licensa paga. 

Por fim, você pode utilizar um toolchain fornecido por comunidades de desenvolvedores, como [Linaro](https://www.linaro.org/), [Yocto](https://www.yoctoproject.org/). Outras referências podem ser encontradas em: [https://elinux.org/Toolchains](https://elinux.org/Toolchains).

### Instalando um Toolchain Pré-compilado

O processo de instalação de um toolchain pré-compilado é muito simples. Lembrando que a primeira tarefa é encontrar o toolchain para a sua plataforma de desenvolvimento, seja esse toolchain fornecido pelo fabricante, por uma comunidade ou empresa de terceiros.

Assim, a primeira etapa será a aquisição do toolchain, em geral, este tipo de código é baixado de um repositório `git` ou algo similar. Você deve realizar o download do diretório completo do toolchain em sua máquina _host_.

Após realizar o download do toolchain, é necessário incluir os executáveis no PATH da sua máquina. Para tal, utilizamos o comando `export`  no terminal. Este adiciona o diretório/local passado por parâmetro ao PATH. Assim, basta invocar o comando passando o diretório dos arquivos binários \(_\*.bin_\) como parâmetro, executando assim um _insert_ no arquivo PATH.

```bash
export PATH=/caminho/toolchain/bin:$PATH
```

Fazendo isso, o arquivo binário \(executável\) pode ser invocado diretamente no terminal, sem a necessidade de digitar o caminho inteiro até o mesmo.

Uma vez atualizada a variável de ambiente, você tem acesso direto a todas as ferramentas da toolchain que escolheu. Portanto, basta  apenas compilar seu programa C para a arquitetura desejada através de seu toolchain, e pronto. 

Por exemplo, com o seguinte comando `PREFIX-gcc`, onde o _PREFIX_  é substituido por sua arquitetura target. Normalmente este, está relacionado com a arquitetura que você deseja compilar o programa com o target, é basicamente isso que difere você compilar nativamente e cross-compilar o código.

```bash
PREFIX−gcc hellow.c −o hellow
```







