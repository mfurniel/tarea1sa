#include <unistd.h>
#include <signal.h>

void sig_handler(int sig) {
    if (sig == SIGALRM) {
        exit(0);
        // printf("llega senal de fin hijo\n");
    }
}

