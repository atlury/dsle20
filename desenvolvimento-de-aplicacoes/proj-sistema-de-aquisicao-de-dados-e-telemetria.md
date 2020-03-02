# \[PROJ\] Sistema de Aquisição de Dados e Telemetria

### Proposta

Para finalizar a etapa de aplicação e também o treinamento, é proposto o projeto de um sistema embarcado para a aquisição de dados e telemetria. 

A proposta inicial para a execução deste projeto, é que o mesmo seja desenvolvido em Linguagem C em uma plataforma embarcada projetada para a aplicação. 

Além disso, é proposta uma arquitetura base para o desenvolvimento do projeto, ela consiste em três threads, sendo duas para aquisição de dados e uma para telemetria. Esta arquitetura é melhor detalhada ao longo deste roteiro.

Os dados serão obtidos de dois sistemas de uma central inercial contendo seis conjuntos de sensores e serão adquiridos pelo nossa plataforma embarcada, ao passo que a mesma deve realizar a tarefa de telemetria via comunicação serial.

Por fim, será desenvolvida uma aplicação gráfica em Qt com o propósito de realizar o monitoramento da telemetria em tempo real. Esta aplicação será desenvolvida para um sistema desktop mas pode ser portada posteriormente para o próprio sistema embarcado.

### Preparação dos Dados

Para a etapa de aquisição de dados, vamos utilizar os dados adquiridos através de dois sistemas. O primeiro é uma central inercial **MDAN**, que fornece os dados de um conjunto de três placas \(X, Y, Z\). Cada placa conta com um acelerômetro e um sensor de temperatura ligado ao seu conversor V/F. Além destes dados de cada placa, são fornecidos também a tensão instantânea de quatro alimentações.

Uma amostra dos dados enviados pelo sistema **MDAN** é apresentados na tabela a seguir:

#### Log de dados do MDAN:

| Cycle | X\_Accel | X\_Temp | X\_VF\_Temp | Y\_Accel | Y\_Temp | Y\_VF\_Temp | Z\_Accel | Z\_Temp | Z\_VF\_Temp | Volt\_R5V | Volt\_5V | Volt\_15V | Volt\_m15V | Time\_ms |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | 0.000804 | 26.145761 | 71.561798 | 0.000618 | 25.852840 | 58.380398 | -0.097774 | 25.608742 | 53.498398 | 4.769714 | 5.008932 | 15.315810 | -15.573580 | 9.998470 |
| 1 | 0.000799 | 26.145761 | 74.979202 | 0.000084 | 25.852840 | 57.892200 | -0.097762 | 25.608742 | 53.986599 | 4.769714 | 5.008932 | 15.315810 | -15.573580 | 9.998470 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |

Além do sistema **MDAN**, existe também um sistema **GYRO** composto por um conjunto de três girômetros. Este sistema fornece, assim como o **MDAN**, diversos dados entre eles a velocidade angular em cada um dos girômetros, o estado do sensor, sua temperatura e etc.

Uma amostra dos dados enviados pelo sistema **GYRO** é apresentada na tabela a seguir:

#### Log de dados do GYRO:

| Cycle | X\_Gyro\_Status | X\_Gyro\_AngVel | X\_Gyro\_Temp | X\_Gyro\_Count | X\_Gyro\_Ser | Y\_Gyro\_Status | Y\_Gyro\_AngVel | Y\_Gyro\_Temp | Y\_Gyro\_Count | Y\_Gyro\_Ser | Z\_Gyro\_Status | Z\_Gyro\_AngVel | Z\_Gyro\_Temp | Z\_Gyro\_Count | Z\_Gyro\_Ser |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | 98 | -0.000076 | 36.000000 | 1 | 4 | 99 | 0.000055 | 36.500000 | 1 | 4 | 98 | -0.000008 | 36.000000 | 1 | 4 |
| 1 | 98 | -0.000308 | 36.000000 | 2 | 4 | 99 | -0.000031 | 36.500000 | 2 | 4 | 98 | 0.000034 | 36.000000 | 2 | 4 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |

Para facilitar a prática durante o treinamento, optou-se por trabalhar com um arquivo de _log_ de dados destas duas unidades. Isto é, adquiriu-se dados de ambos os sistemas e esses dados serão utilizados para o treinamento. 

Este processo é vastamente utilizado para aplicações que não estão em processo de produção, assim como projetos mockados e etc. Como a tarefa de realizar a leitura de um arquivos binário e um arquivo de dispositivo é o mesmo, como visto durante os laboratórios, não haverá nenhum prejuizo didático na abordagem.

Então, ambos os _logs_ foram convertidos da forma apresentada para uma stream de bytes, ou seja, tranformados em arquivos binários. Desta forma, podemos emular com eficiência o processo de comunicação entre nosso sistema embarcado \(RPi\) e as placas **MDAN** e **GYRO**, representados pelos arquivos `mdanbin` e `gyrosbin`.

Para armazenar os dados de ambos os sensores foi fornecido, no código base, um conjunto de estruturas de dados:

A estrutura de dados `mdan_t` é composta por:

* Um contador que armazena o número de leituros \(ciclos\);
* Três acelerômetros, um para cada eixo \(X, Y e Z\);
* Três temperaturas, uma de cada acelerômetro \(X, Y e Z\);
* Três temperaturas, uma de cada V/F \(X, Y e Z\);
* Quatro tensões internas: DC/DC \(5V, 15V, -15V\) e Regulador 5V;
* Uma medida do tempo decorrido da última interrupção.

Ao passo que a estrutura de dados `gyros_t` é composta por:

* Um contador que armazena o número de leituros \(ciclos\);
* Três girômetros, um para cada eixo \(X, Y e Z\);
* Três temperaturas, uma de cada girômetro \(X, Y e Z\);
* Uma medida do tempo decorrido da última interrupção.

Além destas, foi criada também uma estrutura de dados `sensors_t` que representa o pacote de telemetria enviado pela RPi, isto é, um pacote devidademente estruturado contendo os dados de ambos os sensores, um cabeçalho e um CRC.

### Código Base

Para facilitar o desenvolvimento do projeto, foi fornecido um conjunto de arquivos na forma de um código base. O código foi estruturado da seguinte forma:

```text
+Sensors
|
+---+inc
|   |
|   +---+defines.h
|   |
|   +---+structs.h
|   |
|   +---+gyro_task.h
|   |
|   +---+mdan_task.h
|   |
|   +---+telemetry_task.h
|
+---+src
|   |
|   +---+Sensors.c
|   |
|   +---+gyro_task.c
|   |
|   +---+mdan_task.c
|   |
|   +---+telemetry_task.c
|
+---+logs
|   |


```

### Diagrama de Entidades e Arquitetura

![](../.gitbook/assets/image%20%288%29.png)

Para um melhor visualização recomenda-se o downloada do arquivo `sensors_class.pdf` fornecido no link abaixo.

{% file src="../.gitbook/assets/sensors\_class.pdf" %}

![](../.gitbook/assets/image%20%281%29.png)

Para um melhor visualização recomenda-se o downloads do arquivo `sensors_threads.pdf` fornecido no link abaixo.

{% file src="../.gitbook/assets/sensors\_threads.pdf" %}

