#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proc.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s [-l | -p <pid>]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-l") == 0) {
        list_processes();
    } else if (strcmp(argv[1], "-p") == 0) {
        if (argc < 3) {
            printf("Укажите PID после -p\n");
            return 1;
        }
        int pid = atoi(argv[2]);
        if (pid <= 0) {
            printf("Некорректный PID\n");
            return 1;
        }
        process_info(pid);
    } else {
        printf("Неизвестный аргумент: %s\n", argv[1]);
        printf("Использование: %s [-l | -p <pid>]\n", argv[0]);
        return 1;
    }

    return 0;
}