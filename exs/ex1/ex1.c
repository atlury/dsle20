  /*
 ============================================================================
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

#define LED0      "/sys/class/leds/led0/brightness"
#define LED1      "/sys/class/leds/led1/brightness"

#define LED_ON    "1"
#define LED_OFF   "0"

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

  int led0_fd;			/* A file descriptor to manipulate the LED0.  */
  int led1_fd;			/* A file descriptor to manipulate the LED1.  */

  led0_fd = open(LED0 ,O_RDWR);	/* Opens LED0 for reading and writing.*/
  led1_fd = open(LED1 ,O_RDWR);	/* Opens LED1 for reading and writing.*/

  if (led0_fd < 0)
  {
    printf("Error: Failed to open %s\r\n", LED0);
  }

  if (led1_fd < 0)
  {
    printf("Error: Failed to open %s\r\n", LED1);
  }

  while(!kbhit()) /* While a key from the keyboard isn't pressed... */
  {

    write(led0_fd, LED_ON, sizeof(LED_ON));
    write(led1_fd, LED_OFF, sizeof(LED_OFF));

    printf("LED0 -> ON \tLED1 -> OFF\r\n");
    sleep(1);


    write(led0_fd, LED_OFF, sizeof(LED_OFF));
    write(led1_fd, LED_ON, sizeof(LED_ON));

    printf("LED0 -> OFF \tLED1 -> ON\r\n");
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
