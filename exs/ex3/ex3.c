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

#include <fcntl.h>		/* Required by open / write system calls.     */
#include <pthread.h>		/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>		/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>		/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>		/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>		/* Terminal Input/Output interfaces.          */
#include <unistd.h>		/* Complement (flags, constants, definitions..)
				 * for the POSIX API. */

//#include "pigpio.h"		/* PIGPIO Library header. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define SERIAL 	    "/dev/ttyS0"
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

  int serial_fd;

  uint8_t serial_st;
  
  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);

  if (serial_st == 0)
  {
    printf("Error: Failed to open serial %s\r\n", SERIAL);
  }

  while(!kbhit())
  {
    write(serial_fd, "Running..\r\n", sizeof("Running..\r\n"));
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
    printf("Error: Failed to open serial %s \r\n", p_path);
    ret = 0;
  }
  else
  {
    printf("Serial (%s) opened!\r\n", p_path);
    
    /** The structure to set and get the device parameters. */
    struct termios config;

    /** Get the current configuration of the serial interface. */
    if (tcgetattr(*p_fd, &config) < 0)
    {
      printf("Error: Could not get the %s attributes!\r\n", p_path);
    }
    else
    {
      printf("Serial (%s) attributes read..\r\n", p_path);

      /** Check if the fd is pointing to a TTY device or not. */
      if (!isatty(*p_fd))
      {
        printf("Error: isnt pointing to a TTY device\r\n");
      }
      else
      {
        printf("%s is a TTY device. Continuing..\r\n", p_path);
	/** Setting the baudrate. */
        if (cfsetspeed(&config, (speed_t)speed) < 0)
        {
          printf("Error: Couldn't set the %s baudrate\r\n", p_path);
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

          if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
          {
            printf("Error: Couldn't set the %s attributes.\r\n", p_path);
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

