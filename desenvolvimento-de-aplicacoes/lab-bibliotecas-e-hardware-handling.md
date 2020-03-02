# \[LAB\] Bibliotecas e Hardware Handling

Neste projeto vamos aprofundar um pouco mais na manipulação dos hardwares e periféricos dos sistemas embarcados utilizando Linux. Vamos desenvolver uma aplicação básica que realize algumas tarefas que são comumente utilizadas em aplicações embarcadas, como: manipulação de GPIO, geração de PWM, trigggers e callbacks.

Para desenvolver aplicações em sistemas Linux embarcados, geralmente utilizamos bibliotécas _in-house_ ou de terceiros para desempenhar determinados papeis na aplicação, por exemplo, comunicação com hardware, protocolos, criptografias e etc. 

Esta é uma escolha usualmente simples, pois muitas vezes não é desejável re-implementar este tipo de função, ou está fora do escopo do projeto ou simplesmente pois existe uma gama tão grande de bibliotecas que desempenham este papel com maestria e já foram massivamente testadas e possuem um bom suporte que não convém desenvolvelas novamente. 

Para a manipulação de hardware não é diferente, existem diversas bibliotecas e APIs na comunidade para este fim. Cada uma com sua especificidade, sua aplicação, sua interface e sua linguagem de implementação, tais como: [WiringPi](http://wiringpi.com/), [PIGPIO](http://abyz.me.uk/rpi/pigpio/) e [RPi.GPIO](https://pypi.org/project/RPi.GPIO/).

Por alguns motivos em particular, vamos utilizar a biblioteca `PIGPIO` para as implementações desta atividade. Elá possui um interface em linguagem C, é suportada para todas as versões das Raspberrys e possui uma boa gama de funções, tais como: manipulação básica de GPIOs, timers, comunicação serial e etc.

### Cross-compilando e Instalando o PIGPIO no _host_

```text
cd ~/dsle20/dl
mkdir libs
cd libs
```

{% hint style="warning" %}
A compilação deve ser feita utilizando cross-compiling, uma vez que o código é feito para rodar no embarcado. Portando, altere a variável `CROSS_COMPILE` dentro do `Makefile` para receber o prefixo da ferramenta de cross compilação.
{% endhint %}

```text

wget abyz.me.uk/rpi/pigpio/pigpio.zip
unzip pigpio.zip
cd PIGPIO
make
sudo make install
```

Após a compilação observe os arquivos gerados dentro do diretório `PIGPIO`. Estamos especialmente interessados nas bibliotecas compartilhadas \(`.so`\) e nos cabeçalhos.

### Instalando o PIGPIO no _target_ \(Buildroot\)

Para instalar a `PIGPIO` podemos utilizar o Buildroot, uma vez que o Busybox tem esta biblioteca em seu repositório.

Abra o menu de configuração dos pacotes do Buildroot:

```c
cd ~/dsle20/rootfs/buildroot-2019.02.8
make menuconfig 
```

Na seção _Target packages_ entre na subseção _Hardware Handling,_ onde se encontram diversos pacotes para a manipulação e periféricos e então selecione o pacote `pigpio`. Save a configuração e recompile o nosso RootFS. Não se preocupe, o processo de compilação ignora os arquivos já compilado, desta forma o processo se torna simples e rápido. 

Então, grave a nova imagem do RootFS no cartão SD e realize a configuração novamente. Para que tenhamos acesso agora, a essa nova biblioteca no nosso sistema embarcado.

Por padrão, as bibliotecas são instaladas dentro de `/usr/lib` no nosso _target_. Não diferente, se listarmos os arquivos disponíveis dentro deste diretório encontraremos os referidos arquivos.

```c
ls -ll /usr/lib | grep *pig*

-rwxr-xr-x    1 root     root        193672 Feb  2  2020 libpigpio.so
-rwxr-xr-x    1 root     root         45108 Feb  2  2020 libpigpiod_if.so
-rwxr-xr-x    1 root     root         45108 Feb  2  2020 libpigpiod_if2.so
```

### Utilizando a `PIGPIO`:

Primeiro passo que devemos fazer é importar esta nossa biblioteca através da primitiva de pré-processamento:

```c
#include "pigpio.h"
```

Então, ao compilar o código percebemos que não é possível realizar a compilação pois o linker não encontrou a referida biblica, pois a mesma não se encontra no diretório de execução. Portanto, faz-se necessário informar tanto o caminho do diretório que deve ser incluído no PATH do compilador como o nome da biblioteca, assim:

Clique com o botão direito sobre o projeto e em _Properies &gt; C/C++ Build &gt; Settings_. 

Então, na aba central, escolhemos a subseção _Cross GCC Compiler &gt; Includes_. 

Em "_includes paths \(-l\)_" adicionamos o caminho até a biblioteca compilada: `/home/gbs/dsle20/libs/PIGPIO`.

Na subseção _Cross GCC Linker &gt; Libraries_ em _"Libraries \(-l\)_" adicionamos o nome da biblioteca: `pigpio` \(sem o prefixo _lib_ e sem a extensão _.so_\). 

Por fim, em "_Library search path \(-L\)_" adicionamos novamente o caminho para a biblioteca compilada: `/home/gbs/dsle20/libs/PIGPIO`

Finalmente após a compilação iremos copiar os binários gerados para dentro da RPi e então executar o nosso código de teste.

```c
cd exs/
sudo ./ex02

./ex02: error while loading shared libraries: libpigpio.so.1: cannot open shared object file: No such file or directory
```

Este erro é ocasionado pois o executável não conseguiu encontrar o arquivo "`libpigpio.so.1`". De fato, podemos listar as bibliotecas instaladas e procurar pela _libpigpio_ no target:

```c
ls -ll /usr/lib/ | grep libpigpio.so
-rwxr-xr-x    1 root     root        193672 Feb  2  2020 libpigpio.so
```

Ao passo que no host:

```c
gbs@core:~$ ls -ll ~/dsle20/libs/PIGPIO/ | grep libpigpio.so

lrwxrwxrwx 1 gbs  gbs      14 Jan 10 14:26 libpigpio.so -> libpigpio.so.1
-rwxrwxr-x 1 gbs  gbs  260000 Jan 10 14:26 libpigpio.so.1
```

Nota-se que há um link simbólico _libpigpio.so -&gt; libpigpio.so.1_, ou seja, no processo de compilação a biblioteca a `libpigpio.so` é substituída por `libpigpio.so.1`. Normalmente, este número no final da biblioteca indica o versionamento atual da biblioteca, é muito comum realizar este tipo de link. Porém, na versão instalada na plataforma target, não há o arquivo `*.so.1` desta forma, precisamos criar este link no target para conseguir realizar a execução corretamente.

```c
sudo ln -s /usr/lib/libpigpio.so /usr/lib/libpigpio.so.1
```

```c
$ ls -ll /usr/lib/ | grep pig
-rwxr-xr-x    1 root     root        193672 Feb  2  2020 libpigpio.so
lrwxrwxrwx    1 root     root            21 Jan  1 00:32 libpigpio.so.1 -> /usr/lib/libpigpio.so
```

Agora basta compilar o código e tudo deve funcionar como o esperado.

{% hint style="warning" %}
Toda as funções utilizadas nesta \(e nas seguintes\) prática podem ser consultadas através da documentação da biblioteca `PIGPIO` ou mesmo através do comando `man`.
{% endhint %}

### Geração de Sinal PWM utilizando a Biblioteca `PIGPIO`

Com a biblioteca devidamente instalada em ambas as plataformas podemos dar início a prática deste laboratório. 

O primeiro objetivo é gerar um sinal PWM em um dos pinos de uso geral da RPi3, de acordo com a especificação mostrada no diagrama de forma de onda abaixo, isto é, PWM de 50Hz e 50% de duty-cycle.

![Sinal PWM 50Hz@1000/500](../.gitbook/assets/image%20%2817%29.png)

Primeiramente, devemos inicializar a biblioteca PIGPIO, esta inicialização é feita através da função `gpioInitialise`.

```c
	if (gpioInitialise() < 0)
	{
		fprintf(stderr, "pigpio initialization failed\n");
		return 1;
	}
```

Depois de inicializada devemos configurar o modo de operação do pino que produzirá o sinal PWM. Nesta prática iremos utilizar o GPIO 23 \(observe o pinout da RPi para verificar a localização física do mesmo\). Para configurar o GPIO 23 como um pino de saída, basta utilizar a função `gpioSetMode`.

```c
if (gpioSetMode(23, PI_OUTPUT) != 0)
{
    printf("Error: Failed to set GPIO %d \n\n", 23);
}
```

Em seguida, utilizamos a função `gpioSetPWMfrequency` para definir a frequência de geração do pulso.

```c
int freq_ret;
freq_ret = gpioSetPWMfrequency(23, 50);

printf("Freq: %d \n\n", freq_ret);
```

Em seguida devemos definir o através da função `gpioSetPWMrange` a resolução do pulso gerado, bem como o duty-cycle do PWM através da função `gpioPWM`. O duty-cycle é definido pela razão entre o range e o parâmetro passado a função `gpioPWM`.

```c
gpioSetPWMrange(23, 1000);
```

```c
gpioPWM(23, 500);
```

Após a execução do código é necessário encerar as configurações dos pinos, similarmente como realizado no processo de inicialização.

```c
gpioTerminate();
```

### ISR e Callbacks utilizando a Biblioteca `PIGPIO`

Na segunda parte da atividade iremos realizar a configuração de uma ISR \(interrupção\) em um dos pinos. Esta interrupção será vinculada a uma função `signal_handler_io` que tem como objetivo executar uma determinada tarefa, como por exemplo a manipulação de um outro pino ou mesmo a execução de uma outra função qualquer.

Primeiramente vamos realizar a configuração de mais duas GPIOs. A GPIO 20 será configurada como uma porta de entrada e estará vinculada à ISR. Além disso, iremos inializar o GPIO 16 como saída para que a mesma seja manipulada pela callback da interrupção. 

```c
if (gpioSetMode(20, PI_INPUT) != 0)
{
    printf("Error: Failed to set GPIO %d \n\n", 20);
}

if (gpioSetMode(16, PI_OUTPUT) != 0)
{
    printf("Error: Failed to set GPIO %d \n\n", 16);
}
```

Para atrelar um GPIO a uma ISR devemos utilizar a função `gpioSetISRFunc` da biblioteca PIGPIO. Como parâmetros podemos passar a GPIO utilizada, a borda à ser detectada, um timeout e também a função \(callback\) a ser chamada quando o evento acontecer.

```c
gpioSetISRFunc(20, FALLING_EDGE, 300, signal_handler_IO);
```

Assim, devemos criar a função signal\_handler\_IO para ser utilizada como callback.

```c
void signal_handler_IO(int gpio, int level, uint32_t tick) 
{
    int gpio_val = gpioRead(16);
    gpio_val = !gpio_val;
    gpioWrite(16, gpio_val);
    printf("Interrupt Occurred! Level-> %d\t tick-> %d\n",level, tick-tick_spent);
    tick_spent = tick;
}
```

Populamos a função com alguma tarefa qualquer, neste caso, foi proposto calcular o tempo entre duas interrupções e também alterar o estado do GPIO 16, ligando-o e desligando conforme ocorrem as interrupções.

Ao executar o código podemos observar o seguinte diagrama:

![](../.gitbook/assets/image%20%2823%29.png)

A primeira forma de onda é o sinal PWM gerado pelo GPIO 23 ao passo que a segunda é a forma de onda gerada pelo GPIO 16.

Realizando um contato elétrico entre os GPIO 23 e GPIO 20, ou seja, conectando o PWM ao pino ISR é possível obter o diagrama a seguir.

![](../.gitbook/assets/image%20%2811%29.png)

Desta forma, foi possível visualizar a operação da ISR dos dois modos: timeout e detecção de borda. Estes tópicos serão abordados no projeto final.

```c
/*
 ============================================================================
 Name        : ex02.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the PIGPIO interface.
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

#include "pigpio.h"				/* PIGPIO Library Header */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */


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

/**
 * @brief The callback function attached to the GPIO pin interrupt. The bellow
 * 		  parameters are provided by the RPiGPIO Library.
 *
 * @param[in] gpio     0-53     The GPIO which has changed state.
 * @param[in] level    0-2      0 = change to low (a falling edge)
 *		                        1 = change to high (a rising edge)
 *           		            2 = no level change (interrupt timeout)
 * @param[in] tick     32 bit   The number of microseconds since boot
 *
 */
static void signal_handler_IO(
		int gpio,
		int level,
		uint32_t tick);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

uint32_t tick_spent;		/* A variable used to store the number of occurred
								ticks between each GPIO interrupt. */


//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
	tick_spent = 0;


	if (gpioInitialise() < 0) /* Such function must be called before using the
									 PIGPIO library.*/
	{
		fprintf(stderr, "pigpio initialization failed\n");
		return 1;
	}

    if (gpioSetMode(23, PI_OUTPUT) != 0)
    {
    	printf("Error: Failed to set GPIO %d \n\n", 23);
    }

    if (gpioSetMode(16, PI_OUTPUT) != 0)
    {
		printf("Error: Failed to set GPIO %d \n\n", 16);
	}

    if (gpioSetMode(20, PI_INPUT) != 0)
	{
		printf("Error: Failed to set GPIO %d \n\n", 20);
	}

    /**
     * Registers the signal_handler function to be called
     * (a callback) whenever an interrupt occurs on
     * the specified GPIO (20). The EITHER_EDGE parameter
     * specifies an interrupt for both: Rising or Falling
     * edges. The parameter 100 indicates a 100ms timeout.
     */
    gpioSetISRFunc(20, EITHER_EDGE, 300, signal_handler_IO);
    /* PS: If you want to see a result different from the timeout,
     * i.e., a detected RISING or FALLING edge, you should connect
     * the GPIO pins (BCM) 20(input)-23(pwm). Which physically are:
     * the pins 38 and 16, respectively. */


    int freq_ret;

	/* Sets a 50Hz PWM Frequency for the GPIO  23 pin.
	 * It returns the numerically closest frequency if OK.
	 * The frequency depends on other factors, please for
	 * further details check:
	 * http://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency*/
	freq_ret = gpioSetPWMfrequency(23, 50);

	printf("Freq: %d \n\n", freq_ret);

	/* Selects the duty-cycle range to be used for the GPIO.
	 * Subsequent calls to gpioPWM will use a duty-cycle
	 * between 0 (off) and range (fully on).]
	 * the range value can be: 25-40000 */
	gpioSetPWMrange(23, 1000);

	/* According to the above specified range (1000), sets a duty-cicle
	 * of 50%. */
	gpioPWM(23, 500);

	while(!kbhit()) /* While a key from the keyboard isn't pressed... */
	{

		printf("Running..\n");
		sleep(1);
	}

	/* Similar to the gpioInitialise function, this one must be called at the end of your program.*/
	gpioTerminate();


	return EXIT_SUCCESS;
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

void signal_handler_IO(int gpio, int level, uint32_t tick)
{
	/* Reads the current state of the GPIO pin 16. */
	int gpio_val = gpioRead(16);

	/* Inverts such state. */
	gpio_val = !gpio_val;

	/* Updates the gpio pin's state. */
	gpioWrite(16, gpio_val);

	/* Computes and shows the number of spent ticks between the last and the current interrupt. */
	printf("Interrupt Occurred! Level-> %d\t tick-> %d\n",level, tick-tick_spent);
	tick_spent = tick;
}

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



