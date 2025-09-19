#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;
    char mensaje[] = "Hola desde el padre!";
    char buffer[100];

    pipe(fd);    
    pid = fork();

    if (pid > 0) { 
        close(fd[0]);
        write(fd[1], mensaje, strlen(mensaje) + 1);
        close(fd[1]);
    } else {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Hijo recibió: %s\n", buffer);
        close(fd[0]);
    }
    return 0;
}