#include"boot.h"

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
        puts(USAGE);
    else if((av[1] && av[1][0] != '-' ) || ( av[1][1] != 'h' && av[1][1] != 't'  && av[1][1] != 'r' && av[1][1] != 's' && av[1][1] != 'l') || strlen(av[1]) > 2)
        err(OPTION);
    return 0;
} 

int shut_down(char **av)
{
        int time = 0;
    if(av[2])
        time = atoi(av[2]);
    sleep(time * 60);
    printf("shutdown !?\n");
    return 0;
}

int reboot_(char **av)
{
    int time = 0;
    if(av[2])
        time = atoi(av[2]);
    sleep(time * 60);
    if(reboot(RB_POWER_OFF) == -1)
    {
        if(system("shutdown now") == -1)
            puts("failed :( \n try to run the program as root");
    }
    return 0;
}

int lock(char **av)
{
    int time = 0;
    if(av[2])
        time = atoi(av[2]);
    sleep(time * 60);
    if(system("xdg-screensaver lock") == -1)
        puts("failed :( \n try to run the program as root");

    return 0;
}

int main(int ac , char **av)
{
    check(ac,av);
    if(av[1][1] == 'h')
        puts(help);
    else if (av[1][1] == 's')
        shut_down(av);
    else if(av[1][1] == 'l')
        lock(av);
    else if(av[1][1] == 'r')
        reboot_(av);
}