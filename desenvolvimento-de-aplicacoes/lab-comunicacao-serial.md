# \[LAB\] Comunicação Serial

Nesta atividade iremos realizar a implementação de uma aplicação simples que envia dados via serial. Para a implementação iremos adotar duas abordagem: a primeira será a utilização explicita de file descriptors e a segunda será utilizando as abstrações fornecidas pela biblioteca `PIGPIO`.

### Comunicação Serial utilizando File Descriptors

```c
#define SERIAL 	"/dev/ttyS0"
#define SERIAL_BAUD 115200

int serial_fd;
```

```c
uint8_t serial_st;
serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);
```

```c
uint8_t serial_initialize(const char *p_path, int32_t *p_fd, const uint32_t speed);
```

A primeira etapa que devemos realizar é justamente tentar abrir o dispositivo \(porta serial\), tal como fizemos com os os `LED0` e `LED1`, no projeto anterior. Então utilizamos o caminho e o file descriptor passados por parâmetro.

```c
*p_fd = open(p_path, O_RDWR);

if (p_fd < 0)
{
	printf("Error: Failed to open serial %s \n\n", p_path);
	ret = 0;
}
```

Caso contrário, ou seja, o file descriptor tenha sido devidamente relacionado com um dispositivo, precisamos verificar se ele é de fato uma porta serial e caso seja, devemos configura-la de acordo com o que desejamos.

Para fazer a configuração, utilizaremos uma estrutura de dados, `config`, para adquirir e atribuir os parâmetros do dispositivos.

```c
struct termios config;
```

Como mencionado, a primeira verificação que devemos fazer é justamente avaliar se o dispositivo relacionado ao file descriptor é um interface serial. Para tal, carregamos todos os atributos do dispositivo para nossa estrutura de dados.

```c
if (tcgetattr(*p_fd, &config) < 0)
{
		printf("Error: Could not get the %s attributes!\n\n", p_path);
}
```

Então, realizamos as validações, primeiramente se o dispositivo em questão é ou não uma interface serial:

```c
if (!isatty(*p_fd))
{
    printf("Error: %s isnt pointing to a TTY device!!\n\n", p_path);
}
```

Em seguida, tentamos atribuir o baud rate especificado

```c
if (cfsetspeed(&config, (speed_t)speed) < 0)
{
    printf("Error: Couldn't set the %s baudrate!!\n\n", p_path);
}
```

Então, especificamos os outros parâmetros:

```c
config.c_cflag     &=  ~PARENB;
config.c_cflag     &=  ~CSTOPB;
config.c_cflag     &=  ~CSIZE;
config.c_cflag     |=  CS8;
config.c_cflag     &=  ~CRTSCTS;
config.c_cc[VMIN]   =  1;
config.c_cc[VTIME]  =  5;
config.c_cflag     |=  CREAD | CLOCAL;

cfmakeraw(&config);
```

E enfim, atribuimos os atributos ao dispositivo.

```c
if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
{
    printf("Error: Couldn't set the %s attributes!!\n\n", p_path);
}
```

```c
uint8_t serial_initialize(const char *p_path, int32_t *p_fd, const uint32_t speed)
{
	uint8_t ret;

  /** Tries to open the serial device (p_path).
    *  O_RDWR:     Request read and write permissions. */
	*p_fd = open(p_path, O_RDWR);

	if (p_fd < 0)
	{
		printf("Error: Failed to open serial %s \n\n", p_path);
		ret = 0;
	}
	else
	{
		printf("Serial (%s) opened!!\n\n", p_path);

		/** The structure to set and get the device parameters. */
		struct termios config;

		/** Get the current configuration of the serial interface. */
		if (tcgetattr(*p_fd, &config) < 0)
		{
			printf("Error: Could not get the %s attributes!\n\n", p_path);
		}
		else
		{
			printf("Serial (%s) attributes read.. \n\n", p_path);

			/** Check if the fd is pointing to a TTY device or not. */
			if (!isatty(*p_fd))
			{
				printf("Error: %s isnt pointing to a TTY device!!\n\n", p_path);
			}
			else
			{
				printf("%s is a tty device. Continuing...\n\n", p_path);

				/** Setting the baudrate. */
				if (cfsetspeed(&config, (speed_t)speed) < 0)
				{
					printf("Error: Couldn't set the %s baudrate!!\n\n", p_path);
				}
				else
				{
					/** No parity. */
					config.c_cflag     &=  ~PARENB;
					/** One stop bit. */
					config.c_cflag     &=  ~CSTOPB;
					/** Zeroes the char size mask. */
					config.c_cflag     &=  ~CSIZE;
					/** Sets data size = 8 bits. */
					config.c_cflag     |=  CS8;
					/** Disables HW flow control. */
					config.c_cflag     &=  ~CRTSCTS;
					/** Minimum number of characters for read. */
					config.c_cc[VMIN]   =  1;
					/** Timeout in deciseconds for read. (0.5s) */
					config.c_cc[VTIME]  =  5;
					/** Enables READ and ignores control lines. */
					config.c_cflag     |=  CREAD | CLOCAL;

					/** Set the terminal to "raw mode". */
					cfmakeraw(&config);

			    /** Flushes the serial dev and sets the new attributes. */
    			if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
    			{
    				printf("Error: Couldn't set the %s attributes!!\n\n", p_path);
    			}
    			else
    			{
    				ret = 1;
    			}
				}
			}
		}
	}
	return ret;
}
```

```c
uint8_t serial_st; 
serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);

if (serial_st == 0)
{
    printf("Error: Failed to open serial %s \n\n", SERIAL);
}
```

```text
write(serial_fd, "Running.. Serial is easy\r\n", sizeof("Running.. Serial is easy\r\n"));
```

```
close(serial_fd);
```

```c
/*
 ============================================================================
 Name        : ex03.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the serial communication.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <fcntl.h>				/* Required by open / write system calls.     */
#include <pthread.h>			/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>				/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>				/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>				/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>			/* Terminal Input/Output interfaces.          */
#include <unistd.h>				/* Complement (flags, constants, definitions..)
									for the POSIX API. */

#include "pigpio.h"				/* PIGPIO Library header. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define SERIAL 	"/dev/ttyS0"
#define SERIAL_BAUD 115200

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
 * @brief Initializes the p_path serial device. Opens the serial device and
 * 		  sets minimal attributes to get it working.
 *
 * @param[in] p_path    The serial device path.
 * @param[out] p_fd     A file descriptor to link to the serial device above.
 * @param[in] speed     The serial BAUDRATE.
 *
 * @return  1   If the serial device was initialized.
 * @return  0   If an error has occurred.
 */
uint8_t serial_initialize(
  const char *p_path,
  int32_t *p_fd,
  const uint32_t speed);


//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
  int serial_fd;			/* A file descriptor to manipulate the SERIAL.*/
  uint8_t serial_st;		/* A status for the serial_initialize func.   */

  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);

  if (serial_st == 0)
  {
    printf("Error: Failed to open serial %s \r\n", SERIAL);
  }

  while(!kbhit())	/* While a key from the keyboard isn't pressed... */
  {
    write(serial_fd, "Running.. Serial is easy\r\n", sizeof("Running.. Serial is easy\r\n"));
  }

  close(serial_fd);

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

uint8_t serial_initialize(
  const char *p_path,
  int32_t *p_fd,
  const uint32_t speed)
{

  uint8_t ret;

  /** Tries to open the serial device (p_path).
   *  O_RDWR:     Request read and write permissions. */
  *p_fd = open(p_path, O_RDWR);

  if (p_fd < 0)
  {
    printf("Error: Failed to open serial %s \n\n", p_path);
    ret = 0;
  }
  else
  {
    printf("Serial (%s) opened!!\n\n", p_path);

    /** The structure to set and get the device parameters. */
    struct termios config;

    /** Get the current configuration of the serial interface. */
    if (tcgetattr(*p_fd, &config) < 0)
    {
      printf("Error: Could not get the %s attributes!\n\n", p_path);
    }
    else
    {
      printf("Serial (%s) attributes read.. \n\n", p_path);

      /** Check if the fd is pointing to a TTY device or not. */
      if (!isatty(*p_fd))
      {
        printf("Error: %s isnt pointing to a TTY device!!\n\n", p_path);
      }
      else
      {
        printf("%s is a tty device. Continuing...\n\n", p_path);

        /** Setting the baudrate. */
        if (cfsetspeed(&config, (speed_t)speed) < 0)
        {
          printf("Error: Couldn't set the %s baudrate!!\n\n", p_path);
        }
        else
        {
          /** No parity. */
          config.c_cflag     &=  ~PARENB;
          /** One stop bit. */
          config.c_cflag     &=  ~CSTOPB;
          /** Zeroes the char size mask. */
          config.c_cflag     &=  ~CSIZE;
          /** Sets data size = 8 bits. */
          config.c_cflag     |=  CS8;
          /** Disables HW flow control. */
          config.c_cflag     &=  ~CRTSCTS;
          /** Minimum number of characters for read. */
          config.c_cc[VMIN]   =  1;
          /** Timeout in deciseconds for read. (0.5s) */
          config.c_cc[VTIME]  =  5;
          /** Enables READ and ignores control lines. */
          config.c_cflag     |=  CREAD | CLOCAL;

          /** Set the terminal to "raw mode". */
          cfmakeraw(&config);

          /** Flushes the serial dev and sets the new attributes. */
          if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
          {
            printf("Error: Couldn't set the %s attributes!!\n\n",
              p_path);
          }
          else
          {
            ret = 1;
          }
        }
      }
    }
  }
  return ret;
}
```

### Comunicação Serial utilizando a Bilbioteca `PIGPIO`

Similarmente com a prática anterior é possível abstrair o uso do file descriptors através de encapsulamentos que já realizam essa tarefa mecânica para nós. Desta forma, vamos realizar o mesmo exercício utilizando as implementações fornecidas pela biblioteca PIGPIO.

Primeiramente devemos definir o nosso file descriptor para a manipulação do dispositivo serial.

```c
  int serial_fd;      /* A file descriptor to manipulate the SERIAL.*/
```

Então inicializamos as funções da bilbioteca PIGPIO:

```c
  if (gpioInitialise() < 0)
  {
    printf("PIGPIO init error\n");
  }
```

Em seguida, devemos atrelar o nosso file descriptor com o arquivo de dispositivo que queremos utilizar por meio da função `serOpen`:

```c
  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_fd = serOpen(SERIAL, SERIAL_BAUD, 0);

  if (serial_fd < 0)
  {
    printf("Failed to open SERIAL\r\n");
  }
```

Por fim, basta utilizar a função `serWrite` passando o nosso file descriptor e a mensagem a ser enviada:

```c
    if (serWrite(serial_fd, (char *)"Running.. Serial is easy\r\n",
                 sizeof("Running.. Serial is easy\r\n")) != 0)
    {
      printf("Error: Failed to send message.\r\n");
    }
```

Se tudo ocorrer bem a mensagem será enviada através da porta serial `ttyS0`.

```c
/*
 ============================================================================
 Name        : ex03b.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the serial communication.
 ============================================================================
 */
//==============================================================================
//                              USED INTERFACES
//==============================================================================

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <fcntl.h>        /* Required by open / write system calls.     */
#include <pthread.h>      /* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>       /* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>        /* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>       /* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>      /* Terminal Input/Output interfaces.          */
#include <unistd.h>       /* Complement (flags, constants, definitions..)
                  for the POSIX API. */

#include "pigpio.h"       /* PIGPIO Library header. */
//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define SERIAL      "/dev/ttyS0"
#define SERIAL_BAUD 115200

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

  int serial_fd;      /* A file descriptor to manipulate the SERIAL.*/

  if (gpioInitialise() < 0)
  {
    printf("PIGPIO init error\n");
  }

  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_fd = serOpen(SERIAL, SERIAL_BAUD, 0);

  if (serial_fd < 0)
  {
    printf("Failed to open SERIAL\r\n");
  }


  while(!kbhit())
  {
    sleep(1);

    if (serWrite(serial_fd, (char *)"Running.. Serial is easy\r\n",
                 sizeof("Running.. Serial is easy\r\n")) != 0)
    {
      printf("Error: Failed to send message.\r\n");
    }
  }

  /* Similar to the gpioInitialise function, this one must be called at the end of
   * your program.*/
  gpioTerminate();

	return EXIT_SUCCESS;
}

//==============================================================================s
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

