#ifndef AUTO_SHUT_H
#define AUTO_SHUT_H

#include <stdio.h>
#include "unistd.h"
#include "sys/reboot.h"
#include "string.h"
#include "stdlib.h"
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


#define USAGE "<usage> auto_shutdown \"option\" \"args\" \n auto_shutdown -h for help" 
#define OPTION 1
#define ARG 2
#define OPTION_ERR "Err:\n invalid option !"
#define ARG_ERR "Err:\n invalid arg !"
#define HELP 0
#define SHUT RB_POWER_OFF
#define LOCK 2
#define SUS RB_SW_SUSPEND
#define LO 10
#define REB RB_AUTOBOOT
#define AT 1
#define X 2
#define N 3
#define DETECT 4 
#define help "\
Usage: auto_shut [OPTION] [TIME]\n\
\n\
Options:\n\
  -h, --help        Display this help message and exit\n\
  -s, --shutdown    Schedule a system shutdown after the specified time\n\
  -l, --lock        Lock the screen\n\
  -r, --reboot      Schedule a system reboot after the specified time\n\
  -o, --log out     log out after specified time\n\
  -f  --suspend     suspend after specified time\n\
\n\
  Specifed TIME format:\n\
  \n\
  Specify the time in minutes or use the following format:\n\
  \"-now\" for immediate action,\n\
  \"-X\" for X minutes from now,\n\
  \"-at\" for a specific time on the 24-hour clock (e.g., \"18:30\").\n\
  Mouse and keys detection \n\
    -D\n\
\n\
Examples:\n\
  auto_shut -s -X 30      # Shutdown the system in 30 minutes\n\
  auto_shut -r -at 18:00  # Schedule a system reboot at 18:00\n\
  auto_shut -l            # Lock the screen now \"the default therd option is -now\"\n\
  auto_shut -l  -D        # Lock the screen if a key press or mouse movement is detected (press q to cancel) \"\n\
  auto_shut -h            # Display this help message\n\
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
