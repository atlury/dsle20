# Fontes

Os fontes das versões oficiais do kernel Linux, anda são as liberadas por Linus Torvalds. É possível baixá-las diretamente na[ página oficial do projeto](https://www.kernel.org/), eles tem um diretório público com todas os releases, ou ainda através do repositório git do próprio Linus.

Muitos fabricantes costuma fornecer suas próprias versões do kernel Linux, por exemplo a Freescale, HardKernel, entre outras.

Normalmente essas versões são focadas no suporte do hardware desses fabricante, via de regra são defasados em relação ao mainline, pois é difícil acompanhar a frequência de um release a cada três meses.

Além destas, as comunidades de desenvolvimento também fornecem suas próprias versões, as vezes voltadas a uma arquitetura específica. Por exemplo, existe o projeto ArchLinux ARM que fornece releases para diversas placas que usa ARM, muitas outras distribuições fazem isso, como Ubuntu e Debian.

Algumas outras podem ser específicas para drivers, geralmetne comunicação de rede, por exemplo uma das buzzwords da moda, o IoT.  Inclusive a Microsoft lançou seu proprio branch do Linux para IoT, na plataforma Azure.

Existem as comunidades focadas em _real-time_ como Xenomai, RTAI e etc. Normalmente são bem atrasadas em comparação com o mainline, principalmente devido ao uso específico.

```text
ls linux/
```

|  |  |  |  |
| :--- | :--- | :--- | :--- |
| arch  | block  | certs  | COPYING CREDITS |
| crypto  | Documentation |  drivers  | firmware  |
| fs |  include |  init  | ipc  |
| Makefile |  Kbuild  | mm  | Kconfig  |
| net  | kernel |  README |  lib  |
| REPORTING-BUGS  | MAINTAINERS  | samples  | scripts  |
| security  | sound  | tools  | usr  |
| virt |  |  |  |

Essa é a estrutura geral do diretório de fontes do kernel Linux.

* O diretório `arch` contém basicamente todo código das arquiteturas suportadas, é possível inspecionar através de um `ls` no diretório e visualizar as arquiteturas;
* `Documentation` oferece alguma documentação do kernel, mas normalmente é desatualizada;
* `drivers` é o maior diretório do kernel, aproximadamente 60% do tamanho total e contém os drivers do kernel Linux;
* O diretório `firmware` contém alguns firmwares para hardwares, alguns são necessários para rodar alguns drivers;
* O diretório `fs` contém os arquivos de implementação da camada de arquivos virtuais;
* `include` contém os headers;
* `init` arquivos relacionados a boot e inicialização;
* `makefile` montado para compilação e configuração;
* `kernel` são os core subsystems, como o escalonador de processos e etc;
* `ipc` codigo relacionado à comunicação IPC;
* `lib` contém bibliotecas auxiliares;
* `mm` gerenciamento de memória.

Esses são os principais diretório do kernel Linux.



