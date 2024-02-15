#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd->h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s HH:MM\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *targetTimeStr = argv[1];
    int targetHour, targetMin;

    if (sscanf(targetTimeStr, "%d:%d", &targetHour, &targetMin) != 2) {
        fprintf(stderr, "Invalid time format. Please use HH:MM\n");
        return EXIT_FAILURE;
    }

    while (1) {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        if (timeinfo->tm_hour == targetHour && timeinfo->tm_min == targetMin) {
            printf("Hello, World!\n");
            break;
        }

        // Sleep for a short interval (e.g., 1 second) before checking the time again
        sleep(1);
    }

    return EXIT_SUCCESS;
}
