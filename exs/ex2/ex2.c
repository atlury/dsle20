  /*
 ============================================================================
 Name        : ex02.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating PIGPIO Library interface.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <fcntl.h>			/* Required by open / write system calls.     */
#include <pthread.h>			/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>			/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>			/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>			/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>			/* Terminal Input/Output interfaces.          */
#include <unistd.h>			/* Complement (flags, constants, definitions..)
				         * for the POSIX API. */

#include "pigpio.h"

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

/**
 * @brief The callback function attached to the GPIO pin interrupt. The bellow
 * 		  parameters are provided by the RPiGPIO Library.
 *
 * @param[in] gpio     0-53     The GPIO which has changed state.
 * @param[in] level    0-2      0 = change to low (a falling edge)
 *		                1 = change to high (a rising edge)
 *           		        2 = no level change (interrupt timeout)
 * @param[in] tick     32 bit   The number of microseconds since boot
 *
 */
void signal_handler_IO(int gpio, int level, uint32_t tick);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

uint32_t tick_spent;	/* A variable used to store the number of occurred
			   ticks between each GPIO interrupt. */

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
  tick_spent = 0;

  if (gpioInitialise() < 0)	/* Such function must be called before using the
				 * PIGPIO library.*/
  {
    printf("Error: pigpio initialization failed\r\n");
    return 1;
  }

  if (gpioSetMode(23, PI_OUTPUT) != 0)
  {
    printf("Error: Failed to set GPIO %d\r\n", 23);
  }

  if (gpioSetMode(16, PI_OUTPUT) != 0)
  {
    printf("Error: Failed to set GPIO %d\r\n", 16);
  }

  if (gpioSetMode(20, PI_INPUT) != 0)
  {
    printf("Error: Failed to set GPIO %d\r\n", 20);
  }

  	/**
   * Registers the signal_handler function to be called
   * (a callback) whenever an interrupt occurs on
   * the specified GPIO (20). The EITHER_EDGE parameter
   * specifies an interrupt for both: Rising or Falling
   * edges. The parameter 100 indicates a 100ms timeout.
   */
  gpioSetISRFunc(20, EITHER_EDGE, 10, signal_handler_IO);
  /* PS: If you want to see a result different from the timeout,
   * i.e., a detected RISING or FALLING edge, you should connect
   * the GPIO pins (BCM) 20(input)-23(pwm). Which physically are:
   * the pins 38 and 16, respectively. */
  
  int freq_ret;
  /* Sets a 50Hz PWM Frequency for the GPIO  23 pin.
   * It returns the numerically closest frequency if OK.
   * The frequency depends on other factors, please for
   * further details check:
   * http://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency */
  freq_ret = gpioSetPWMfrequency(23, 50);

  printf("Freq: %d", freq_ret);

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
  }

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
