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
    else if ((av[1] && av[1][0] != '-') || strlen(av[1]) > 2)
        err(OPTION);
    if(av[1][1] == 'h')
        d->option = HELP;
    else if(av[1][1] == 'l')
        d->option = LOCK;
    else if(av[1][1] == 'r')
        d->option = REB;
    else if(av[1][1] == 's')
        d->option = SHUT;
    if (!strcmp(av[2], "-at")) 
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

void shut_down() 
{

    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();
    printf("Shutdown!\n");
}

void reboot_() 
{
    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();

    if (reboot(RB_POWER_OFF) == -1) 
    {
        if (system("shutdown now") == -1)
            puts("Failed :( \nTry to run the program as root");
    }
}

void lock() 
{
    if (d->second_option == X)
        sleep(d->time);
    else if (d->second_option == AT)
        sleep_tal();

    if (system("xdg-screensaver lock") == -1)
        puts("Failed :( \nTry to run the program as root");
}

int main(int ac, char **av) 
{
    d = malloc(sizeof(data));
    check(ac, av);
    printf("PROGRAM\n");
    switch (d->option) 
    {
        case HELP:
            puts(help);
            break;
        case SHUT:
            shut_down();
            break;
        case LOCK:
            lock();
            break;
        case REB:
            reboot_();
            break;
        default:
            err(OPTION);
    }
    free(d);
    return 0;
}
