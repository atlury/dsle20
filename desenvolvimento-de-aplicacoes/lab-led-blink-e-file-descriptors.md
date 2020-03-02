# \[LAB\] Led Blink e File Descriptors

A partir deste laboratório iremos dar início a etapa de aplicação em sistemas embarcados.  Assim, nesta prática iniciaremos através da manipulação de hardware e os conceitos básicos de file descriptors.

Nesta primeira prática iremos entender o funcionamento dos file descriptors e utilizá-los para realizar o acionamento dos LEDs built-in da RPi3.

### LEDs Internos da RPi 3

A Raspberry Pi 3 Model B/B+ possui dois LEDs internos que são utilizadaos para funções internas da placa. Um deles é um LED na cor verde e é utilizado para explicitar as atividades do cartão SD do dispositivo. Ao passo, que o segundo, LED vermelho, indica a alimentação do circuito de potência da placa. Ambos podem ser visto na imagem abaixo.

![](../.gitbook/assets/image%20%2814%29.png)

| LED | Cor | Localização | Função |
| :--- | :--- | :--- | :--- |
| OK/ACT | Verde | `/sys/class/leds/led0/brightness` | Atividade do Cartão SD |
| PWR | Vermelho | `/sys/class/leds/led1/brightness` | Alimentação |

###  Acionamento via dos Arquivos de Dispositivo

Como explicado durante o treinamento, os dispositivos, em geral, são representados por arquivos no Linux. Não diferente, os dois LEDs built-in da RPi3 são representados através deste tipo de arquivo.

O acesso a esses dispositivos são feitos através do arquivo de dispositivo que representa cada um deles. Por exemplo, caso deseje ler o valor do LED0 \(verde\) basta executar o comando `cat` no diretório especificado.

```bash
cat /sys/class/leds/led0/brightness 
```

O mesmo pode ser feito para o vermelho:

```bash
cat /sys/class/leds/led1/brightness 
```

Note que o valor retornado pelo `cat`, caso o Led em questão esteja ligado, é _255_ \(ou outro valor diferente de 0\), ao passo que o valor do Led desligado é igual a _0._ Ou seja, é possível notar o comportamento binário dos Led, de tal forma que: _0_ é desligado e qualquer outro valor é ligado.

Com base nisso, é possível especular que para acionar um dos Leds, basta escrever _1_ ou _0_ nos respectivos arquivos. Assim, para acionar o Led verde, basta escrever _1_ no arquivo `/sys/class/leds/led0/brightness`. 

```bash
echo 1 | sudo tee /sys/class/leds/led0/brightness
```

Ao passo que para apagar o Led, deve-se escrever _0._

```bash
echo 0 | sudo tee /sys/class/leds/led0/brightness
```

O mesmo para o Led vermelho, bastando apenas substituir o arquivo `/sys/class/leds/led0/brightness` por `/sys/class/leds/led1/brightness`.

Até este momento, foi possível interagir de formar manual com os dispositivos. Contudo, em um sistema embarcado real este tipo de operação não é usual, sendo necessário a manipulação desses dispositivos via programação. Para esse tipo de manipulação em sistema Linux utilizamos os _File Descriptors_.

### File Descriptors

Um _file descriptor_, ou também chamado de _file handler_, é um número que unicamente identifica um arquivo aberto no sistema operacional. Ele descreve um recurso de dados, e como esse recurso pode ser acessado.

Quando um programa pede para abrir um arquivo \(ou outros recurso, como um _socket_ ou um _pipe_\) o kernel Linux garante o acesso ao recurso, cria uma entrada na tabela global de arquivos e fornece a localização desta entrada ao software.

O descriptor é identificado por um número inteiro não-negativo único, tal como, 0, 13 ou 37. Existe pelo menos um file descriptor para cada arquivo aberto no sistema. 

Para mais informações sobre File Descriptors é recomendado a leitura das discussões propóstas em: [https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms](https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms)

Mas, em linha gerais:

* File descriptors são número inteiros não-negativos únicos que são associados a arquivos abertos no sistema;
* São alocados de forma sequencial;
* Utilizamos eles para manipular arquivos via biblioteca padrão C;
* Para um processo em particular seus file descriptors podem ser vistos em: `/proc/$pid/fd`.

Em linguagem C, usualmente representamos um file descriptor como um `int`:

```c
int led0_fd;
int led1_fd;
```

Para realizar a associação dos nossos file descriptors com os arquivos de dispositivos utilizamos a função padrão `open`:

{% hint style="info" %}
Para mais informações sobre as funções utilizadas, basta ler a documentação disponível no `man` digitando o comando `man func`. Por exemplo, `man open`, `man tee`, `man echo` e etc.
{% endhint %}

```c
#define LED0 "/sys/class/leds/led0/brightness"
#define LED1 "/sys/class/leds/led1/brightness"

led0_fd = open(LED0, O_RDWR);
led1_fd = open(LED1, O_RDWR);
```

Repare que como o interesse é realizar tanto leituras quanto escritas utilizamos a flag de "_read and write_", além disso para facilitar foram criados duas definições `LED0` e `LED1`, para armazenar os caminhos para os dispositivos.

Para verificar se os file descriptors foram devidamente associados, podemos observar e validar o retorno da função `open`. Isto é, como o file descriptor é sempre um número positivo, basta verificar se o retorno da função é de fato um valor positivo, caso não seja, significa que o file descriptor deste arquivo não foi relacionado através da função `open`.

```c
if (led0_fd < 0)
{
	printf(" Error: Failed to open %s \n\n", LED0);
}

if (led1_fd < 0)
{
	printf(" Error: Failed to open %s \n\n", LED1);
}
```

Para escrever valores nesses arquivos utilizamos a função pradrão `write`, passando os  file descriptors e os valores.

```c
#define LED_ON 	"1"
#define LED_OFF	"0"

write(led0_fd, LED_ON, sizeof(LED_ON));
write(led1_fd, LED_OFF, sizeof(LED_OFF));
```

Assim, acionamos o Led verde e desligamos o Led vermelho, escrevendo "_1_" e "_0_" em seus respectivos arquivos.

Por fim, é sempre necessário fechar esses file descriptors, indicando que não há mais necessidade de suas referências, fazemos isto através da função `close`.

```c
close(led0_fd);
close(led1_fd);
```

### Código de Led Blink com File Descriptors

```c
 /*============================================================================
 Name        : ex01.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the file descriptors.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <fcntl.h>				/* Required by open / write system calls.     */
#include <pthread.h>			/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>				/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>				/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>				/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>			/* Terminal Input/Output interfaces.          */
#include <unistd.h>				/* Complement (flags, constants, definitions..)
									for the POSIX API. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define LED0	"/sys/class/leds/led0/brightness" // Green Led
#define LED1	"/sys/class/leds/led1/brightness" // Red Led

#define LED_ON 	"1"
#define LED_OFF	"0"

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A function to verify if any key was pressed on terminal.
 *
 * @return TRUE     If a key was pressed.
 * @return FALSE    Otherwise.
 */
static int kbhit(void);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================


//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{

	int led0_fd; 			/* A file descriptor to manipulate the LED0. */
	int led1_fd; 			/* A file descriptor to manipulate the LED1. */

	led0_fd = open(LED0, O_RDWR); /* Opens LED0 for reading and writing*/
	led1_fd = open(LED1, O_RDWR); /* Opens LED1 for reading and writing*/

	if (led0_fd < 0)
	{
		printf(" Error: Failed to open %s \n\n", LED0);
	}

	if (led1_fd < 0)
	{
		printf(" Error: Failed to open %s \n\n", LED1);
	}

	while(!kbhit()) /* While a key from the keyboard isn't pressed... */
	{
		write(led0_fd, LED_ON, sizeof(LED_ON));
		write(led1_fd, LED_OFF, sizeof(LED_OFF));

		printf("LED0 -> ON, LED1 -> OFF\n");
		sleep(1);

		write(led0_fd, LED_OFF, sizeof(LED_OFF));
		write(led1_fd, LED_ON, sizeof(LED_ON));

		printf("LED0 -> OFF, LED1 -> ON\n");
		sleep(1);
	}

	close(led0_fd);
	close(led1_fd);

	return EXIT_SUCCESS;
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

static int kbhit(void)
{
    struct termios oldt, newt;

    int ch;
    int oldf;

    /** Gets the attributes from the standard input file descriptor. */
    tcgetattr(STDIN_FILENO, &oldt);

    /** Enables raw input. (unprocessed). */
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    /** Sets the new attributes. */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /** Gets the file access mode and status flags. */
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    /** Sets the same above read values + the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    /** Checks if there is a char on the standard terminal. (nonblock). */
    ch = getchar();

    /** Make changes now, without waiting for data to complete. */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    /** Removes the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    /** If any key was hitted, return true. And puts back the pressed key onto
     *  the terminal. */
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
```





