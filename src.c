#include"auto_shut.h"

data *d;

int err(int type)
{
    if(type == OPTION)
        write(2,OPTION_ERR,strlen(OPTION_ERR));
    else if(type == ARG)
        write(2,ARG_ERR,strlen(ARG_ERR));
    write(2,"\n",1);
    exit(1);
}

int check(int ac , char **av)
{
    if(ac < 2)
    {
        puts(USAGE);
        exit(0);
    }
    else if((av[1] && av[1][0] != '-' )  || strlen(av[1]) > 2)
        err(OPTION);
    if(av[1][1] == 'h')
        d->option = HELP;
    else if(av[1][1] == 'l')
        d->option = LOCK;
    else if(av[1][1] == 'r')
        d->option = REB;
    else if(av[1][1] == 's')
        d->option = SHUT;
    else 
        err(OPTION);
    if(!strcmp(av[2],"-at"))
    {
        d->second_option = AT;
        if (sscanf(av[3],"%d:%d",&d->hours,&d->minutes) != 2) 
        {
        write(2, "Invalid time format. Please use HH:MM\n",39);
        exit(EXIT_FAILURE);
        }
    }
    else if(!strcmp(av[2],"-X"))
    {
        d->option = X;
        if (sscanf(av[3],"%d",&d->time) != 2) 
        {
            write(2, "Invalid time format. Please use integer format like 69\n",56);
            exit(EXIT_FAILURE);
        }
    }
    exit(0);
    return 0;
} 

int shut_down(char **av)
{
    sleep(d->time * 60);
    printf("shutdown !?\n");
    return 0;
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

int reboot_(char **av)
{
    if(d->option == X)
        sleep(d->time);
    else if(d->option == AT)
        sleep_tal();
    if(reboot(RB_POWER_OFF) == -1)
    {
        if(system("shutdown now") == -1)
            puts("failed :( \n try to run the program as root");
    }
    return 0;
}

int lock(char **av)
{
    if(d->option == X)
        sleep(d->time);
    else if(d->option == AT)
        sleep_tal();
    if(system("xdg-screensaver lock") == -1)
        puts("failed :( \n try to run the program as root");

    return 0;
}

int main(int ac , char **av)
{
    d = malloc(sizeof(data));
    check(ac,av);
    if(d->option == HELP)
        puts(help);
    else if (d->option == SHUT)
        shut_down(av);
    else if(d->option == LOCK)
        lock(av);
    else if(d->option == REB)
        reboot_(av);
}