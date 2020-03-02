# \[LAB\] Configurando o Ambiente de Trabalho

## Configuração Inicial

Devido ao limitado tempo de aula em função da quantidade de conteúdo a ser visto, seria inapropriado realizar o download das diversas ferramentas, códigos fontes, documentos, dentre outros, necessários para a realização das atividade práticas deste treinamento, Assim, todo o material julgado necessário para a realização das atividades foi previamente baixado e compilado em um único tarball.

O objetivo desta atividade é extrair o conteúdo desse tarball, analisá-lo e familiarizar-se com o ambiente de trabalho que será utilizado ao longo de todo o treinamento.

### Configurando o ambiente de trabalho

Faça download e extraia o arquivo `dsle20.tar.xz`:

{% code title="bash" %}
```bash
cd
wget http://brandaogbs.github.io/linux/dsle20.tar.xz
tar xvf dsle20.tar.xz
```
{% endcode %}

O comando `cd` é utilizado para a navegação entre os diretórios do Linux, executando-o sem argumentos vamos para a pasta `home` do usuário que estamos logados. O comando `wget` é utilizado para fazer o download de um diretório web, neste caso o repositório com o tarball do curso. Por fim, o comando `tar` é utilizado para a manipulação de arquivos tarball enquanto o primeiro argumento `xvf` é referente a operação de extração-verbose-arquivo, ao passo que o segundo argumento diz respeito ao arquivo tarball.

Quando houver dúvida/curiosidade sobre os comandos utilizados é possível utilizar o comando `man` no terminal do Linux, este retorna o descritivo do comando desejado. Por exemplo: `man cd`, `man wget` e `man tar`. Esta função será utilizada com frequência durante o curso.

Ao finaliza o procedimento de extração, todo o centeúdo do tarball estará disponível na recém criada pasta `dsle20`, dentro do diretório `home` do usuário logado \(_~/dsle20_\). Este diretório possui a seguinte estrutura.

```text
+dsle20
|
+---+dl
|
+---+docs
|   |
|   +---+guides
|   |
|   +---+hardware
|   |
|   +---+training
|
+---+exs
```

O diretório `dl` contém todos os componentes que foram baixados. Durante a realização dos exercícios, os comandos comuns de download \(`wget`\) e clonagem de repositório \(`git clone`\) serão substituídos pelo processo de extrair esses componentes. Cada atividade conterá as informações necessárias para realização de tal procedimento.

O diretório `docs` contém uma documentação de apoio para consulta durante o treinamento. Neste diretório, estão contidos pdfs relacionados ao hardware da RaspberryPi, tabelas de comandos do shell, vi, guia introdutório do Ubuntu e kernel Linux, por exemplo.

O diretório `training` contém a Agenda, Slides e Atividades de Laboratório \(este documento\).

O diretório `exs` será dedicado a realização dos exercícios. A fim de manter uma estrutura organizada, cada exercício será realizado dentro de seu próprio diretório .



## 



