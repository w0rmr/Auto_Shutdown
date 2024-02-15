#ifndef AUTO_SHUT_H
#define AUTO_SHUT_H

#include <stdio.h>
#include "unistd.h"
#include "sys/reboot.h"
#include "string.h"
#include "stdlib.h"
#include <time.h>


#define USAGE "<usage> auto_shutdown \"option\" \"args\" \n auto_shutdown -h for help" 
#define OPTION 1
#define ARG 2
#define OPTION_ERR "Err:\n invalid option !"
#define ARG_ERR "Err:\n invalid arg !"
#define HELP 0
#define SHUT 1
#define LOCK 2
#define REB 3
#define AT 1
#define X 2
#define N 3
#define help "\
Usage: myshutdown [OPTION] [TIME]\n\
\n\
Options:\n\
  -h, --help        Display this help message and exit\n\
  -s, --shutdown    Schedule a system shutdown after the specified time\n\
  -l, --lock        Lock the screen\n\
  -r, --reboot      Schedule a system reboot after the specified time\n\
\n\
  Specifed TIME format:\n\
  \n\
  Specify the time in minutes or use the following format:\n\
  \"-now\" for immediate action,\n\
  \"-X\" for X minutes from now,\n\
  \"-at\" for a specific time on the 24-hour clock (e.g., \"18:30\").\n\
\n\
Examples:\n\
  myshutdown -s -X 30      # Shutdown the system in 30 minutes\n\
  myshutdown -r -at 18:00  # Schedule a system reboot at 18:00\n\
  myshutdown -l            # Lock the screen now \"the default therd option is -now\"\n\
  myshutdown -h        # Display this help message\n\
\n\
Note: Administrative privileges may be required for shutdown and reboot operations.\n"
typedef struct data {
  int time;
  int option;
  int second_option;
  int hours;
  int minutes;
  time_t rawtime;
  struct tm *timeinfo;
} data;
#endif