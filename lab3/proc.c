#include <stdio.h>
#include <stdlib.h>
#include <libproc.h>
#include <unistd.h>
#include "proc.h"

void list_processes() {
    int bufsize = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0); // Получаем размер буфера
    if (bufsize <= 0) {
        printf("Ошибка получения списка процессов\n");
        return;
    }

    pid_t *pids = malloc(bufsize);
    if (!pids) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    bufsize = proc_listpids(PROC_ALL_PIDS, 0, pids, bufsize); // Заполняем массив PID-ов
    if (bufsize <= 0) {
        free(pids);
        printf("Ошибка получения списка процессов\n");
        return;
    }

    int num_pids = bufsize / sizeof(pid_t);
    for (int i = 0; i < num_pids; i++) {
        char name[PROC_PIDPATHINFO_MAXSIZE];
        if (proc_name(pids[i], name, sizeof(name)) > 0) {
            printf("PID: %d, Name: %s\n", pids[i], name);
        }
    }

    free(pids);
}

void process_info(int pid) {
    struct proc_bsdinfo proc;
    int ret = proc_pidinfo(pid, PROC_PIDTBSDINFO, 0, &proc, PROC_PIDTBSDINFO_SIZE);

    if (ret <= 0) {
        printf("Процесс с PID %d не найден или ошибка\n", pid);
        return;
    }

    char name[PROC_PIDPATHINFO_MAXSIZE];
    proc_name(pid, name, sizeof(name));

    printf("PID: %d\n", pid);
    printf("Name: %s\n", name);
    printf("Parent PID: %d\n", proc.pbi_ppid);
    printf("State: %d\n", proc.pbi_status);
    printf("UID: %d\n", proc.pbi_uid);
    printf("GID: %d\n", proc.pbi_gid);
}