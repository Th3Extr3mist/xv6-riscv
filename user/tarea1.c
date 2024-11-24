#include "kernel/types.h"
#include "user/user.h"

int
main(void) {
    int ppid = getppid();
    printf("El PPID del proceso padre es: %d\n", ppid);

    int pid = getpid();
    printf("PID actual: %d\n", pid);

    int ancestro1 = getancestor(0);
    printf("Ancestro 0 (hijo): %d\n", ancestro1);

    int ancestro2 = getancestor(1);
    printf("Ancestro 1 (padre): %d\n", ancestro2);

    int ancestro3 = getancestor(2);
    printf("Ancestro 2 (abuelo): %d\n", ancestro3);

    int invalido = getancestor(10);
    printf("Ancestro inválido: %d\n", invalido);

    exit(0);
}
