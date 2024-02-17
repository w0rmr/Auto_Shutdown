#include "auto_shut.h"

data *d;

void err(int type) 
{
    if (type == OPTION)
        write(2, OPTION_ERR, strlen(OPTION_ERR));
    else if (type == ARG)
        write(2, ARG_ERR, strlen(ARG_ERR));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}



void check(int ac, char **av) 
{
    if (ac < 2) 
    {
        puts(USAGE);
        exit(EXIT_SUCCESS);
    }
    else if ((av[1] && av[1][0] != '-') || strlen(av[1]) > 2 || av[1][1] == '\0')
        err(OPTION);
    if(av[1][1] == 'h')
    {
        d->option = HELP;
        return;
    }
    else if(av[1][1] == 'l')
        d->option = LOCK;
    else if(av[1][1] == 'r')
        d->option = REB;
    else if(av[1][1] == 's')
        d->option = SHUT;
    else if(av[1][1] == 'f')
        d->option = SUS;
    else if(av[1][1] = 'o')
        d->option = LO;
    d->time = 0;
    if(!av[2] ||!strcmp(av[2],"-now") )
        d->second_option = N;
    else if (!strcmp(av[2], "-at")) 
    {
        d->second_option = AT;
        if (sscanf(av[3], "%d:%d", &d->hours, &d->minutes) != 2) 
        {
            write(2, "Invalid time format. Please use HH:MM\n", 39);
            exit(EXIT_FAILURE);
        }
    } 
    else if (!strcmp(av[2], "-X")) 
    {
        d->second_option = X;
        if (sscanf(av[3], "%d", &d->time) != 1) 
        {
            write(2, "Invalid time format. Please use integer format like 69\n", 56);
            exit(EXIT_FAILURE);
        }
        d->time *= 60;
    }
    else if(!strcmp(av[2],"-D"))
        d->second_option = DETECT;
    else
        err(OPTION);
    
}
void detect() 
{
    Display *display;
    Window root;
    XEvent ev;
    char buf[32];
    display = XOpenDisplay(NULL);
    if (!display) 
    {
        write(2,"Unable to open display\n",24);
        exit(0);
    }
    root = DefaultRootWindow(display);
    XSelectInput(display, root, KeyPressMask | PointerMotionMask);
    XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(display, root, True, PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    while (1) 
    {
        XNextEvent(display, &ev);
        if (ev.type == KeyPress)
        {
            KeySym key;
            XLookupString(&ev.xkey, buf, sizeof(buf), &key, NULL);
            if (buf[0] == 'q')
                exit(0);
            break;
        }
        else if (ev.type == MotionNotify) 
            break;
    }
    XCloseDisplay(display);
}

void sleep_tal() 
{
    while (1) 
    {
        time(&d->rawtime);
        d->timeinfo = localtime(&d->rawtime);
        if (d->timeinfo->tm_hour == d->hours && d->timeinfo->tm_min == d->minutes)
            break;
        sleep(1);
    }
}

void log_out()
{
    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();
    else if(d->second_option == DETECT)
        detect();
    if (system("pkill -KILL -u $(whoami)") == -1 )
        puts("Failed :( \nTry to run the program as root");
}

void suspend()
{
    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();
    else if(d->second_option == DETECT)
        detect();
    if ( system("systemctl suspend") == -1 )
        puts("Failed :( \nTry to run the program as root");
}

void reboot_() 
{
    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();
    else if(d->second_option == DETECT)
        detect();
    if (reboot(d->option) == -1) 
    {   
        if(d->option == SHUT)
        {
            if (system("shutdown now") == -1)
            {
                write(2,"Failed :( \nTry to run the program as root",42);
                exit(EXIT_FAILURE);
            }
        }
        else if(d->option == REB)
        {
            if (system("reboot") == -1)
            {
                write(2,"Failed :( \nTry to run the program as root",42);
                exit(EXIT_FAILURE);
            }
        }
    }
}



void lock() 
{
    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();
    else if(d->second_option == DETECT)
        detect();
    if (system("xdg-screensaver lock") == -1)
        puts("Failed :( \nTry to run the program as root");
}

int main(int ac, char **av) 
{
    d = malloc(sizeof(data));
    check(ac, av);
    switch (d->option) 
    {
        case HELP:
            puts(help);
            break;
        case SHUT:
            reboot_();
            break;
        case LOCK:
            lock();
            break;
        case REB:
            reboot_();
            break;
        case SUS:
            suspend();
            break;
        case LO:
            log_out();
            break;
        default:
            err(OPTION);
    }
    free(d);
    return 0;
}
